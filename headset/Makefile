CC=gcc
CFLAGS=lstdc++
LIBS=-lGLU -lGL -lglut

objects = main.o fbWrite.o 

main: $(objects)
	$(CC)  -o main $(objects) -$(CFLAGS) $(LIBS) 
	

.PHONY:clean

clean:
	rm -f *.o 
cleanAll:
	rm -f *.o test main

