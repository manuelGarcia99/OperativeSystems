#A Simple Example Makefile for soshell
# 
# Alvo: Dependencias
# tab Action 1
# tab Action 2
#
#Variaveis: Compiler, compiler flags, libraries to link, name of of object files
#
CC=cc
FLAGS=-c -Wall
LIBS=-lm -pthread 
OBS=main.o execute.o parse.o calc.o bits.o isjpg.o redirects.o pipes.o aviso.o socp.o
#Alvo por defeito é o primeiro 
all :  soshell
 
main.o : shell.h main.c
	$(CC) $(FLAGS) main.c
execute.o : shell.h execute.c
	$(CC) $(FLAGS) execute.c
parse.o : shell.h parse.c
	$(CC) $(FLAGS) parse.c
calc.o : shell.h calc.c
	$(CC) $(FLAGS) calc.c
bits.o : shell.h bits.c
	$(CC) $(FLAGS) bits.c	
isjpg.o : shell.h isjpg.c
	$(CC) $(FLAGS) isjpg.c	
redirects.o : shell.h redirects.c
	$(CC) $(FLAGS) redirects.c
pipes.o : shell.h pipes.c
	$(CC) $(FLAGS) pipes.c
aviso.o: shell.h aviso.c
	$(CC) $(FLAGS) aviso.c
socp.o: shell.h socp.c
	$(CC) $(FLAGS) socp.c
soshell : $(OBS)
	$(CC) -o soshell  $(OBS) $(LIBS)


