A2 Report
=========

Student: Rodrigo Lopes de Carvalho
Student ID: 0905095

Scheduling Simulation
---------------------

Two scheduling algorithms are implemented: FCFS and Round Robin.


###FCFS

First Come First Serve. Threads are maintained in a queue, and whichever is in the front, will run until it ends or blocks on I/O

###Round Robin (RR)

Each thread will have a fixed amount of time to run, and then another will take its place. This tries to ensure fairness, and minimize response time.



Answers
-------

1. Does your simulator include switch overhead for the first ready state to running state transition? Explain.  
    Yes. Since there's an overhead related to creating a thread, I opted for also delaying the run for the first thread. The overhead is the same as switching to another thread in the same process.

2. Does your simulator include switch overhead if a thread moves from ready state to running state and the CPU is idle? Explain.  
    Yes. Since another thread might have been running a few moments before, there will be an overhead. The overhead will depend on whether the last thread in the CPU was owned by the same process or not.  
3. Does your simulator include switch overhead if a thread moves from
running state to blocked state and the ready queue is empty? Explain.  
    No. In that case, it will not have an overhead, since there is no need for a switch.  
4. Does your simulation include switch overhead if a thread is interrupted (due to a time slice) and either the ready queue is empty or the thread has the highest priority? Explain.  
    No. In that case, it will not have an overhead, since there is no need for a switch.  



Does your simulator include switch overhead for the first ready state to
running state transition? Explain.
ii. Does your simulator include switch overhead if a thread moves from ready
state to running state and the CPU is idle? Explain.
iii. Does your simulator include switch overhead if a thread moves from
running state to blocked state and the ready queue is empty? Explain.
iv. Does your simulation include switch overhead if a thread is interrupted
(due to a time slice) and either the ready queue is empty or the thread has
the highest priority? Explain.
