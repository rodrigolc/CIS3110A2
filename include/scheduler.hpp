/* scheduler.hpp

    Student: Rodrigo Lopes de Carvalho
    Student ID: 0905095

    Header file for the Scheduler struct and SchedulerType enum.

    This is the main class used, and implements most functions needed.


*/

#include "process.hpp"
#include "event.hpp"
#include <queue>


#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

enum SchedulerType {FCFS,RR};

struct Scheduler{
    std::deque<Process*> processes;
    std::deque<Thread*> threads;

    EventQueue event_queue;

    std::deque<Thread*> ready_threads;
    std::deque<Thread*> blocked_threads;
    int time;
    int cpu_utilization;
    Thread* current_thread;
    Thread* last_thread;

    int thread_switch;
    int process_switch;
    bool verbose;
    bool detailed;
    int quantum;
    SchedulerType type;

    void add_event(Event event);
    void pop_event();
    Event next_event();
    void add_thread(Thread* thread);
    void add_process(Process* process);


    void run();
    void fill_queue();
    void print_stats();

    void thread_arrive(Thread* thread);
    void thread_run(Thread* thread);
    void thread_block(Thread* thread);
    void thread_unblock(Thread* thread);
    void thread_end_quantum(Thread* thread);
    void thread_terminate(Thread* thread);


    void print_change(int pid, int tid,State old_state, State new_state);
    Scheduler();
};


#endif //SCHEDULER_HPP
