/* event.cpp

    Student: Rodrigo Lopes de Carvalho
    Student ID: 0905095

    Implementation for the Event struct and CompareEvent comparator class.
    Since the Event struct is mostly data, and doesn't have functions
    on its own, just CompareEvent::operator() is implemented.

*/

#include "event.hpp"

bool CompareEvent::operator()(const Event lhs, const Event rhs) const
{
  return lhs.time > rhs.time;
}
