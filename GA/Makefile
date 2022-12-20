all: main.cpp
	g++ -o main main.cpp -Ofast -std=c++11

clean:
	rm -f main

run: all
	./main 101 1000 10 < ../input.txt >output.txt
test: all
	./main 4 10 10 < ../test.in >test.out