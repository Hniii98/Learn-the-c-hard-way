#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// #define MAX_DATA 512
// #define MAX_ROWS 100



struct Address
{
	int id;
	int set;  // bool simulator
	//char name[MAX_DATA];
	//char email[MAX_DATA];
	char *name;
	char *email;
};

struct Database
{
	int max_data;
	int max_rows;
	//struct Address rows[MAX_ROWS];
	struct Address *rows;
};

struct Connection
{
	FILE *file; // ptr to file
	struct Database *db; // ptr to buffer
};

void Database_close(struct Connection *conn); // 前向声明，不然die()函数会报错

void die(const char *message, struct Connection *conn)
{
	if(errno) // errno initial value = 0
	{
		perror(message);
	}
	else
	{
		printf("ERROR: %s\n", message);
	 }
	if(conn) Database_close(conn);
	exit(1);
}

void Address_print(struct Address *addr)
{
	printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
{
	//int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
	//if(rc != 1) die("Failed to load database", conn);
	rewind(conn->file);
	fread(&conn->db->max_data, sizeof(int), 1, conn->file); // fread中file的位置会随着读取到的字节移动
	fread(&conn->db->max_rows, sizeof(int), 1, conn->file);
	
	conn->db->rows = malloc(sizeof(struct Address) * conn->db->max_rows);

	int i = 0;
	for(i = 0; i < conn->db->max_rows; i++)
	{
		fread(&conn->db->rows[i].id, sizeof(int), 1, conn->file);
		fread(&conn->db->rows[i].set, sizeof(int), 1, conn->file);
		
		conn->db->rows[i].name = malloc(sizeof(char) * conn->db->max_data);
		conn->db->rows[i].email = malloc(sizeof(char) * conn->db->max_data);

		fread(conn->db->rows[i].name, sizeof(char), conn->db->max_data, conn->file);
		fread(conn->db->rows[i].email, sizeof(char),  conn->db->max_data, conn->file);
	}
}

struct Connection *Database_open(const char *filename, char mode, int max_data, int max_rows)
{
	struct Connection *conn = malloc(sizeof(struct Connection));
	if(!conn) die("Memory error", conn);

	conn->db = malloc(sizeof(struct Database));
	if(!conn->db) die("Memory error", conn);

	if(mode == 'c')
	{
		conn->file = fopen(filename, "w"); // 如果文件存在，则将其内容清空。如果文件不存在，创建该文件
		
		conn->db->rows = malloc(sizeof(struct Address) * conn->db->max_rows);
		if(!conn->db->rows) die("Memory error", conn);

		int i = 0;
		for(i = 0; i < max_rows; i++)
		{	
			conn->db->rows[i].name = malloc(sizeof(char) * max_data);
			conn->db->rows[i].email = malloc(sizeof(char) * max_data);
			if(!conn->db->rows[i].name || !conn->db->rows[i].email)
					die("Memory error", conn);
		}
	}
	else
	{
		conn->file = fopen(filename, "r+"); // 以读写方式打开文件，文件必须存在

		if(conn->file)
		{
			Database_load(conn);
		}
	}

	if(!conn->file)	die("Failed to open the file", conn);

	return conn;
}

void Database_close(struct Connection *conn)
{
	if(conn)
	{
		if(conn->file) fclose(conn->file);
		if(conn->db)
		{
			if(conn->db->rows)
			{
				int i = 0;
				for(i = 0; i < conn->db->max_rows; i++)
				{
					free(conn->db->rows[i].name);
					free(conn->db->rows[i].email);
				}
				free(conn->db->rows); // free 
			}
			free(conn->db); // free database
		}
		free(conn); // free connection
	}

}

void Database_write(struct Connection *conn)
{
	rewind(conn->file); // set ptr to the start of file (cover the exist content) 
						// euqals to  fseek(file, 0, SEEK_END); finnal pos = SEEK_END + 0 
						// fseek(FILE *stream, long offset, int whence)
						
	// int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file); // sizeof a Database, how many Database
																	   // db指向栈上存储的Database, file指向创建的.dat文件
	//if(rc != 1) die("Failed to write database.", conn);

	fwrite(conn->db, sizeof(struct Database), 1, conn->file);
	
	int i = 0;
	for(i = 0; i < conn->db->max_rows; i++)
	{
		fwrite(&conn->db->rows[i].id, sizeof(int), 1, conn->file);
		fwrite(&conn->db->rows[i].set, sizeof(int), 1, conn->file);
		fwrite(conn->db->rows[i].name, sizeof(char), conn->db->max_data, conn->file);
		fwrite(conn->db->rows[i].email, sizeof(char), conn->db->max_data, conn->file);
	}

	int rc = fflush(conn->file); // 确保文件立即写入
	if(rc == -1) die("Cannot flush database", conn);
}

void Database_create(struct Connection *conn)
{
	int i = 0;

	for(i = 0; i < conn->db->max_rows; i++)
	{
		conn->db->rows[i].id = i;
		conn->db->rows[i].set = 0;
		conn->db->rows[i].name = NULL;
		conn->db->rows[i].email = NULL;
	}
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
	struct Address *addr = &conn->db->rows[id];
	if(addr->set) die("Already set, delete it first", conn);

	addr->set = 1;

	char *res = strncpy(addr->name, name, conn->db->max_data);
	if(!res) die("Name copy failed", conn);

	res = strncpy(addr->email, email, conn->db->max_data); // strncpy可以指定大小，防止缓冲区溢出
	if(!res) die("Email copy failed", conn);
}

void Database_get(struct Connection *conn, int id)
{
	struct Address *addr = &conn->db->rows[id];

	if(addr->set) Address_print(addr);
	else die("ID is not set", conn);
}

void Database_delete(struct Connection *conn, int id)
{
	struct Address addr = {.id = id, .set = 0};
	conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn)
{
	int i = 0;
	struct Database *db = conn->db;

	for(i = 0; i < conn->db->max_rows; i++)
	{
		struct Address *cur = &db->rows[i];

		if(cur->set) Address_print(cur);
	
	}
}

int main(int argc, char *argv[])
{
	if(argc < 3) die("USAGE: Lab17 <dbfile> <action> [action params]", NULL);

	char *filename = argv[1];
	char action = argv[2][0]; // second parameter's first char eg. /lab17 db.dat c ->  action = 'c'
	
	int max_data = 512; // default value
	int max_rows = 100; // default value
	if(action == 'c')
	{
		printf("Enter the value of max_data:");
		scanf("%d", &max_data);
		printf("Enter the value of max_rows:");
		scanf("%d", &max_rows);
	}
	
	struct Connection *conn = Database_open(filename, action, max_data, max_rows); 

	int id = 0;
	if(argc > 3) id = atoi(argv[3]);
	if(action != 'c' && id >= max_rows) die("There's not that many records.", conn);

	switch(action)
	{
		case 'c': //c 清除原内容，只写；其他的为读写，不清除原内容
			Database_create(conn);  
			Database_write(conn);
			break;

		case 'g':
			if(argc != 4) die("Need an id to get", conn);

			Database_get(conn, id);
			break;

		case 's':
			if(argc != 6) die("Need id, name, email to set", conn);

			Database_set(conn, id, argv[4], argv[5]);
			Database_write(conn);
			break;

		case 'd':
			if(argc != 4) die("Need id to delete", conn);

			Database_delete(conn, id);
			Database_write(conn);
			break;

		case 'l':
			Database_list(conn);
			break;
		
		default:
			die("Invalid action, only: c = create, g = get, s = set, d = del, l = list", conn);
	}
	
	Database_close(conn);

	return 0;
}
