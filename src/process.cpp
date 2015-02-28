#include "process.hpp"

Thread::Thread(int id)
{
  this->id = id;
  this->state = NEW;
  this->arrival_time = 0;
  this->service_time = 0;

  this->cpu_times = std::deque<int>();
  this->io_times = std::deque<int>();
  this->time_remaining = 0;

  this->process = nullptr;

}

void Thread::add_cpu_time(int time){
  this->cpu_times.push_back(time);
}

void Thread::add_io_time(int time){
  this->io_times.push_back(time);
}

Process::Process(int id){
  this->id = id;
  this->threads = std::deque<Thread*>();
}

void Process::add_thread(Thread* thread)
{
  this->threads.push_back(thread);
  thread->process = this;
}
