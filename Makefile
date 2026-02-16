CXX = g++
CXXFLAGS = -Wall

scheduler: main.cpp fcfs.cpp roundrobin.cpp priority.cpp sjf.cpp srtf.cpp hrrn.cpp ljf.cpp lrtf.cpp mlfq.cpp
	$(CXX) $(CXXFLAGS) -o scheduler main.cpp fcfs.cpp roundrobin.cpp priority.cpp sjf.cpp srtf.cpp hrrn.cpp ljf.cpp lrtf.cpp mlfq.cpp

clean:
	rm -f scheduler
