INCLUDE = -I/usr/include/
LIBDIR  = -L/usr/X11R6/lib 

COMPILERFLAGS = -Wall
CC = gcc
CFLAGS = $(COMPILERFLAGS) $(INCLUDE)
LIBRARIES = -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm 
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

all : $(OBJECTS)
	$(CC) $(CFLAGS) -o animation $(OBJECTS) $(LIBDIR) $(LIBRARIES)  

# to clean up:
clean:
	rm -f ./animation;
	rm -f *.o

# to compile all .c

%.o: %.c
	$(CC) -c -o $@ $<
