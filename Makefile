CXX = g++
CXXFLAGS = -Wall

scheduler: main.cpp fcfs.cpp roundrobin.cpp priority.cpp
	$(CXX) $(CXXFLAGS) -o scheduler main.cpp fcfs.cpp roundrobin.cpp priority.cpp

clean:
	rm -f scheduler
