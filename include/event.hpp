#include "process.hpp"
#include <queue>

#ifndef EVENT_HPP
#define EVENT_HPP

enum EventType
{
  THREAD_ARRIVE,
  THREAD_RUN,
  THREAD_BLOCK,
  THREAD_UNBLOCK,
  THREAD_END_QUANTUM,
  THREAD_TERMINATE
};

struct Event
{
  Thread* thread;
  EventType type;
  int time;
};

struct CompareEvent
{
  bool operator()(const Event lhs, const Event rhs) const;

};

typedef std::priority_queue<Event,std::deque<Event>,CompareEvent> EventQueue;

#endif //EVENT_HPP
