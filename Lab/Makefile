CFLAGS =-Wall -g
CC =  gcc
SRC_FILES = src/

# 自动检测所有 lab[数字].c 文件，并去掉扩展名
TARGETS = $(notdir $(patsubst %.c,%,$(wildcard $(SRC_FILES)/lab[0-9]*.c)))

.PHONY: all clean

all:$(TARGETS) 

lab% : src/lab%.c
	$(CC) $(CFLAGS) -o $@ $<


clean:
	rm -f $(TARGETS) *.o


