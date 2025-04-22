set -e
./lab17v2 db.dat  c
./lab17v2 db.dat s 1 zed zed@zedshaw.com
./lab17v2 db.dat s 2 frank frank@zedshaw.com
./lab17v2 db.dat s 3 joe joe@zedshaw.com

./lab17v2 db.dat l
./lab17v2 db.dat d 3
./lab17v2 db.dat l

./lab17v2 db.dat g 2

./lab17v2 db.dat f zed


