test:test.cc
	g++ -o $@ $^ -std=c++17 -lpthread
	
.PHONY:clean
clean:
	rm -f test