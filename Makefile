CXX = g++
CXXFLAGS = -Wall

scheduler: main.cpp fcfs.cpp roundrobin.cpp priority.cpp sjf.cpp srtf.cpp
	$(CXX) $(CXXFLAGS) -o scheduler main.cpp fcfs.cpp roundrobin.cpp priority.cpp sjf.cpp srtf.cpp

clean:
	rm -f scheduler
