rpn: main.cpp
	clang++ -std=c++11 -Wall main.cpp -o main

clean:
	rm -f *~ *.o a.out main
