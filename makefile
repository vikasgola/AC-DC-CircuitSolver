start:
	g++ ./code/Assignment2.cpp -std=c++11 -o a 
	g++ ./code/solver.cpp -std=c++11 -o b
	./a 
	./b

	
clean:
	rm in.txt.svg a b results.txt in.txt.dup

run:
	./a 
	./b
