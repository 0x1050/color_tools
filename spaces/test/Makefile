SHELL = /bin/sh

OBJS = space_driver.cpp ../lib/spaces.h ../lib/spaces.cpp
CC = g++
CFLAGS = -g -Werror -O0 -std=c++11

space_driver : ${OBJ}
	${CC} ${CFLAGS} -o $@ ${OBJS}

test : space_driver
	./space_driver < colors/dcolors > colors.json
	node html.js colors.json > colors.html
	rm colors.json
	xdg-open out.html
	sleep 1
	rm out.html

clean :
	rm -rf space_driver out.html
