/* scheduler.cpp

    Student: Rodrigo Lopes de Carvalho
    Student ID: 0905095

    Implementation for the Scheduler class.
    Contains most of the code for event handling.

    see Scheduler::run() for more details
*/

#include "scheduler.hpp"

void Scheduler::add_event(Event event){
    this->event_queue.push(event);
}

void Scheduler::pop_event(){
    this->event_queue.pop();
}

Event Scheduler::next_event(){
    return this->event_queue.top();
}

void Scheduler::add_thread(Thread* thread)
{
    this->threads.push_back(thread);
}

void Scheduler::add_process(Process* process)
{
    this->processes.push_back(process);
}


Scheduler::Scheduler(){
    this->threads = std::deque<Thread*>();
    this->processes = std::deque<Process*>();
    this->ready_threads = std::deque<Thread*>();
    this->blocked_threads = std::deque<Thread*>();
    this->event_queue = EventQueue();
    this->time = 0;
    this->current_thread = nullptr;
    this->last_thread = nullptr;
    this->cpu_utilization = 0;
    this->verbose = false;
    this->detailed = false;
    this->quantum = 0;
    this->type = FCFS;

}

void Scheduler::fill_queue(){
    for(auto thread : this->threads)
    {
        Event event;
        event.thread = thread;
        event.type = THREAD_ARRIVE;
        event.time = thread->arrival_time;
        this->add_event(event);
    }
}



void Scheduler::run(){

    while(!this->event_queue.empty()){
        Event event = this->next_event();
        this->pop_event();
        this->time = event.time;
        switch(event.type){
            case THREAD_ARRIVE:
                this->thread_arrive(event.thread);
            break;

            case THREAD_RUN:
                this->thread_run(event.thread);
            break;

            case THREAD_BLOCK:
                this->thread_block(event.thread);
            break;

            case THREAD_UNBLOCK:
                this->thread_unblock(event.thread);
            break;

            case THREAD_END_QUANTUM:
                this->thread_end_quantum(event.thread);
            break;

            case THREAD_TERMINATE:
                this->thread_terminate(event.thread);
            break;

        }
        if(this->current_thread == nullptr) //CPU is IDLE
        {
            if(this->ready_threads.size() > 0){
                //set timer to run
                event.thread = this->ready_threads.front();
                if(this->last_thread == nullptr) //there was no last thread
                { //don't know what TODO

                    event.time = this->time + this->thread_switch;
                    this->cpu_utilization += this->thread_switch;
                }
                else if(this->last_thread->process->id == event.thread->process->id) // same process
                {

                    event.time = this->time + this->thread_switch;
                    this->cpu_utilization += this->thread_switch;
                }
                else{ //not the same process

                    event.time = this->time + this->process_switch;
                    this->cpu_utilization += this->process_switch;
                }
                event.type = THREAD_RUN;
                this->add_event(event);
                this->current_thread = event.thread;
            }
        }
    }
}

void Scheduler::thread_arrive(Thread* thread){

    if(this->verbose)
        this->print_change(thread->process->id,thread->id,thread->state,READY);

    thread->time_remaining = thread->cpu_times.front();
    thread->cpu_times.pop_front();
    thread->state = READY;
    this->ready_threads.push_back(thread);
}

void Scheduler::thread_run(Thread* thread){

    if(this->verbose)
        this->print_change(thread->process->id,thread->id,thread->state,RUNNING);

    Event event;
    event.thread = thread;

    thread->state = RUNNING;
    ready_threads.erase(std::remove(std::begin(ready_threads),std::end(ready_threads),thread),std::end(ready_threads));

    if(this->type == FCFS || thread->time_remaining <= this->quantum){
        if(thread->cpu_times.size() > 0){ //still got things to do
            event.type = THREAD_BLOCK;
        }
        else
        {
            event.type = THREAD_TERMINATE;
        }
        event.time = this->time + thread->time_remaining;

    }else if( this->type == RR){
        event.type = THREAD_END_QUANTUM;
        event.time = this->time + this->quantum;
    }
    this->add_event(event);

}

void Scheduler::thread_block(Thread* thread){

    if(this->verbose)
        this->print_change(thread->process->id,thread->id,thread->state,BLOCKED);

    this->current_thread = nullptr;
    this->last_thread = thread;

    thread->state = BLOCKED;
    thread->service_time += thread->time_remaining;
    this->cpu_utilization += thread->time_remaining;

    thread->time_remaining = thread->io_times.front();


    Event event;
    event.thread = thread;
    event.type = THREAD_UNBLOCK;
    event.time = this->time + thread->io_times.front();
    thread->io_times.pop_front();

    this->add_event(event);

}

void Scheduler::thread_unblock(Thread* thread){

    if(this->verbose)
        this->print_change(thread->process->id,thread->id,thread->state,READY);

    thread->block_time += thread->time_remaining;
    thread->time_remaining = thread->cpu_times.front();
    thread->cpu_times.pop_front();
    thread->state = READY;
    this->ready_threads.push_back(thread);

}

void Scheduler::thread_end_quantum(Thread* thread){

    if(this->verbose)
        this->print_change(thread->process->id,thread->id,thread->state,READY);

    this->current_thread = nullptr;
    this->last_thread = thread;

    thread->state = READY;
    thread->service_time += this->quantum;
    thread->time_remaining -= this->quantum;
    this->cpu_utilization += this->quantum;
    this->ready_threads.push_back(thread);

}
void Scheduler::thread_terminate(Thread* thread){

    if(this->verbose)
        this->print_change(thread->process->id,thread->id,thread->state,TERMINATED);

    this->current_thread = nullptr;
    this->last_thread = thread;

    thread->state = TERMINATED;
    thread->service_time += thread->time_remaining;
    this->cpu_utilization += thread->time_remaining;
    thread->time_remaining = 0;
    thread->end_time = this->time;

}


void Scheduler::print_change(int pid, int tid,State old_state, State new_state )
{
    char os[20];
    char ns[20];
    switch(old_state){
        case NEW:
            strcpy(os,"new");
        break;
        case READY:
            strcpy(os,"ready");
        break;
        case RUNNING:
            strcpy(os,"running");
        break;
        case BLOCKED:
            strcpy(os,"blocked");
        break;
        case TERMINATED:
            strcpy(os,"terminated");
        break;
    }

    switch(new_state){
        case NEW:
            strcpy(ns,"new");
        break;
        case READY:
            strcpy(ns,"ready");
        break;
        case RUNNING:
            strcpy(ns,"running");
        break;
        case BLOCKED:
            strcpy(ns,"blocked");
        break;
        case TERMINATED:
            strcpy(ns,"terminated");
        break;
    }
    printf("At time %d: Thread %d of Process %d moves from %s to %s\n",this->time,tid,pid,os,ns);

}


void Scheduler::print_stats(){
    // FCFS:
    // Total Time required is 344 time units
    // Average Turnaround Time is 27.9 time units
    // CPU Utilization is 94%

    printf("\n");

    if(this->type == FCFS){
        printf("FCFS:\n");
    }else{
        printf("Round Robin (quantum = %d time units):\n",this->quantum);
    }

    printf("\n");

    printf("Total Time required is %d time units\n",this->time);

    double turnaround_sum = 0;
    for(auto process : this->processes){
        int min_arrival = -1;
        int max_end = 0;
        for(auto thread : process->threads){
            if(min_arrival == -1) min_arrival = thread->arrival_time;
            if(min_arrival > thread->arrival_time) min_arrival = thread->arrival_time;
            if(max_end < thread->end_time) max_end = thread->end_time;
        }
        turnaround_sum += max_end - min_arrival;
    }
    double mean_turnaround_process = turnaround_sum / this->processes.size();

    printf("Average Turnaround Time is %.1f time units\n",mean_turnaround_process);

    float cpu_utilization = ((float)(this->cpu_utilization * 100)) / this->time;
    printf("CPU Utilization is %.0f%%\n",cpu_utilization);

    if(this->detailed){ //if details on each threads are required.
        for(auto process : this->processes){
            for(auto thread : process->threads){
                printf("\n");
                printf("Thread %d of Process %d:\n",thread->id,process->id);
                printf("\n");
                printf("arrival time: %d\n",thread->arrival_time);
                printf("service time: %d units\n",thread->service_time);
                printf("I/O time: %d units\n",thread->block_time);
                printf("turnaround time: %d units\n",thread->end_time - thread->arrival_time);
                printf("finish time: %d units\n",thread->end_time);
            }

        }
    }

}
