main: main.o 
	g++ -o main main.o
tests: tests.o 
	g++ -o tests tests.o 
main.o: main.cpp 

tests.o:tests.cpp 

clean:
	rm -f *o
