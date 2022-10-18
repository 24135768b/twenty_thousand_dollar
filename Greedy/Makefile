all: main.cpp
	g++ -o main main.cpp -Ofast

clean:
	rm -f main

run: all
	./main < ../input.txt >output.txt
test: all
	./main < ../test.in >test.out