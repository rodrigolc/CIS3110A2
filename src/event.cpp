#include "event.hpp"

bool CompareEvent::operator()(const Event lhs, const Event rhs) const
{
  return lhs.time > rhs.time;
}
