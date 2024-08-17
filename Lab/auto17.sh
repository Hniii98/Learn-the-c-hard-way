set -e
./lab17 db.dat  c
./lab17 db.dat s 1 zed zed@zedshaw.com
./lab17 db.dat s 2 frank frank@zedshaw.com
./lab17 db.dat s 3 joe joe@zedshaw.com

./lab17 db.dat l
./lab17 db.dat d 3
./lab17 db.dat l

./lab17 db.dat g 2

./lab17 db.dat f zed


