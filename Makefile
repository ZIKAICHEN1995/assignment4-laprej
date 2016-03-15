all: cla

cla: cla.c
	clang -g -Wall cla.c -o cla
