/* process.hpp

    Student: Rodrigo Lopes de Carvalho
    Student ID: 0905095

    Header file for the Process and Thread structs, and State enum.


*/

#include <deque>


#ifndef PROCESS_HPP
#define PROCESS_HPP


enum State{ NEW, READY, RUNNING, BLOCKED, TERMINATED};

struct Process;
struct Thread;

struct Thread{

  int id;
  State state;

  int arrival_time;
  int service_time;
  int block_time;
  int end_time;

  std::deque<int> cpu_times;
  std::deque<int> io_times;
  int time_remaining;
  Process* process;

  void add_cpu_time(int time);
  void add_io_time(int time);

  Thread(int id);
};

struct Process{
  int id;
  std::deque<Thread*> threads;

  void add_thread(Thread* thread);

  Process(int id);
};


#endif //EVENT_HPP
