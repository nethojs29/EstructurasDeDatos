# Nombre del ejecutable
APP=Vectores

# Compilador que se utilizará
CC=g++

# Opciones de compilación
CFLAGS=-c -g

# ¿Qué debe correr cuando ejecutes el comando "make"?
all: prog

# "prog" depende de "main.o" y "Matrices.o" (deberán ser ejecutadas antes)
#   cuando "main.o" y "Matrices.o" terminen se correrá el comando:
#       g++ main.o Matrices.o -o matrices
prog: main.o Vector.o
	$(CC) main.o Vector.o -o $(APP)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

Vector.o: Vector.cpp
	$(CC) $(CFLAGS) Vector.cpp

# ¿Qué debe correr cuando se ejecute el comando "make clean"?
cleanall:
	rm -rf *.o $(APP)

clean:
	rm -rf *.o

