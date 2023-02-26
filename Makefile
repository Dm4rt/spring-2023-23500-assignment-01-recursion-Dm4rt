main: knights.o 
	g++ -o main knights.o
tests: tests.o 
	g++ -o tests tests.o 
knights.o: knights.cpp 
	g++ -c knights.cpp 

tests.o:tests.cpp knights.cpp 
	g++ -c tests.cpp knights.cpp 

clean:
	rm -f *o
