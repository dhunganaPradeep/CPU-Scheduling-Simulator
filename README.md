# CPU Scheduling Simulator

A console app that simulates how an OS schedules processes.It covers three algorithms - FCFS, Round Robin and Priority Scheduling. You pick one from the menu, enter burst times and it shows you the waiting time, turnaround time and a timeline chart.

## How to build and run

You need g++ installed. Then just:

```bash
g++ -Wall -o scheduler main.cpp fcfs.cpp roundrobin.cpp priority.cpp
./scheduler
```

Or if you have make:

```bash
make
./scheduler
```

OUTPUT :

```
=========================================
      CPU Scheduling Simulator
=========================================

--- Menu ---
1. FCFS (First Come First Serve)
2. Round Robin
3. Priority Scheduling
4. Exit

Enter choice:
```
---

## The Algorithms

| Algorithm | Pros | Cons |
|---|---|---|
| FCFS | Simple, easy to implement | Long processes block short ones |
| Round Robin | Fair, everyone gets a turn | Depends on quantum size a lot |
| Priority | Important stuff runs first | Low priority processes can starve |
| SJF | Minimum average waiting time | Hard to know burst time in real life |
| SRTF | Even better than SJF | Lots of switching (overhead) |

### 1. FCFS (First Come First Serve)

This is the simplest one. Processes run in the order they arrive. Whoever comes first gets the CPU first.

Working :
- First process starts immediately so its waiting time is 0
- For every next process, its waiting time = previous waiting time + previous burst time
- Turnaround time = waiting time + burst time

```
say we have 3 processes with burst times 5, 3, 8

P1 arrives first, runs for 5 units
P2 waits for P1 to finish (wt=5), then runs for 3
P3 waits for P1+P2 (wt=8), then runs for 8
```

The timeline looks like:

```
 ---------- ------ ----------------
|    P1    |  P2  |       P3       |
 ---------- ------ ----------------
0          5      8               16
```

```
P   WT   TAT
1    0    5
2    5    8
3    8   16
```

```mermaid
flowchart LR
    A[P1 arrives] --> B[P1 runs 0-5]
    B --> C[P2 runs 5-8]
    C --> D[P3 runs 8-16]
```

---

### 2. Round Robin

Each process gets a fixed time slice called quantum. If its not done in that time it goes back to the end of the queue and the next process gets a turn. This keeps going until everyone is done.

How it works:
- Copy burst times into a remaining array
- Go through each process, let it run for quantum or whatever is left
- If remaining time > quantum, subtract quantum and move on
- If remaining time <= quantum, process is done, calculate waiting time
- Keep looping until all remaining times are 0

```
processes with burst 5, 3, 8 and quantum = 2

Round 1: P1 runs 2, P2 runs 2, P3 runs 2
Round 2: P1 runs 2, P2 runs 1 (done), P3 runs 2
Round 3: P1 runs 1 (done), P3 runs 2
Round 4: P3 runs 2 (done)
```

Timeline:

```
 ---- ---- ---- ---- -- ---- -- ---- ----
| P1 | P2 | P3 | P1 |P2| P3 |P1| P3 | P3 |
 ---- ---- ---- ---- -- ---- -- ---- ----
0    2    4    6    8  9   11 12   14   16
```

```mermaid
flowchart LR
    A[P1 q=2] --> B[P2 q=2]
    B --> C[P3 q=2]
    C --> D[P1 q=2]
    D --> E[P2 q=1 done]
    E --> F[P3 q=2]
    F --> G[P1 q=1 done]
    G --> H[P3 q=2]
    H --> I[P3 q=2 done]
```

---

### 3. SJF (Shortest Job First)

This algorithm picks the process with the shortest burst time first. In this app, it's non-preemptive, meaning once a process starts, it finishes.

How it works:
- Sort all processes based on their burst time (we use bubble sort)
- Run them in that sorted order
- Since they all arrive at time 0 right now, it's very easy: just pick the smallest one first

```mermaid
flowchart LR
    A[Start] --> B[Sort by BT]
    B --> C[Run P with smallest BT]
    C --> D[Run P with next smallest]
```

---

### 4. SRTF (Shortest Remaining Time First)

This is the preemptive version of SJF. At every time tick, the OS checks if there is any other process with a shorter remaining time than the current one.

How it works:
- Keep track of remaining burst time for everyone
- At each step, pick the one with the smallest remaining time
- Run for 1 unit and check again
- (Note: Because everyone arrives at t=0, it will look like SJF for now, but the code is ready for preemption if arrival times are added!)

```mermaid
flowchart TD
    A[Every time tick] --> B{Shortest remaining?}
    B --> C[Run for 1 unit]
    C --> A
```

---

### 5. Priority Scheduling

Each process has a priority number. Lower number = higher priority. We sort the processes by priority and then its basically FCFS on the sorted list.

How it works:
- Copy everything into temp arrays
- Bubble sort by priority (swap process id and burst time along with it) using bubble sort by priority (ascending = lower number means higher priority) easy that's why its not fast tho 
- After sorting, calculate wt and tat same as FCFS


Note : I used bubble sort for simplicity, but the time complexity is O(n²). The performance can be improved by replacing it with a more efficient sorting method like quick sort or merge sort.

```
processes with burst 5, 3, 8 and priorities 2, 1, 3

after sorting by priority:
P2 (pri=1) -> P1 (pri=2) -> P3 (pri=3)

P2 runs first for 3 units
P1 runs next for 5 units
P3 runs last for 8 units
```

Timeline:

```
 ------ ---------- ----------------
|  P2  |    P1    |       P3       |
 ------ ---------- ----------------
0      3          8               16
```

```mermaid
flowchart TD
    A[All processes arrive] --> B{Sort by priority}
    B --> C[P2 pri=1 runs first]
    C --> D[P1 pri=2 runs second]
    D --> E[P3 pri=3 runs last]
```
---

## File structure

```
CPU Scheduler/
  main.cpp         - menu, input, main loop
  fcfs.h           - fcfs function declaration
  fcfs.cpp         - fcfs algorithm
  roundrobin.h     - round robin declaration
  roundrobin.cpp   - round robin algorithm
  priority.h       - priority scheduling declaration
  priority.cpp     - priority scheduling algorithm
  sjf.h            - sjf declaration
  sjf.cpp          - sjf algorithm
  srtf.h           - srtf declaration
  srtf.cpp         - srtf algorithm
  Makefile         - build file
```

---

## Why no vectors, structs, sort, etc

Im still learning C++ and right now im comfortable with arrays and basic loops. I know vectors and STL sort exist and they would make some things shorter but I want to understand how things work at a lower level first before using shortcuts. Same with structs - I could group process data together but for now separate arrays do the job fine.

Will probably refactor later when I get better at C++.

---

## Contributing

If you wanna improve this or add more algorithms (like SJF or SRTF), feel free to fork it and open a PR. Some things that could be added:

- Shortest Job First (SJF)
- Shortest Remaining Time First (SRTF)
- Arrival times (right now all processes arrive at time 0)
- Better input validation
- Reading from a file instead of typing everything

Just keep the code simple and readable. No need to over-engineer it.

---

## License

Do whatever you want with it.
