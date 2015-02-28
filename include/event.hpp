/* event.hpp

    Student: Rodrigo Lopes de Carvalho
    Student ID: 0905095

    Header file for the Event struct, CompareEvent comparator class
    and EventType struct.

    The CompareEvent class is used to sort (weakly) the Events in the priority queue

    Contains a typedef from a priority_queue of Events to EventQueue,
    since that is an unyieldly type to memorize.


*/

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
