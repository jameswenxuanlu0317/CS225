#include "graph.h"
#include "schedule.h"
#include <vector>
#include <string>
#include "edge.h"
using namespace std;
edge::edge(string sources, string target)
{
  source=sources;
  _target=target;
}
string edge::getSources()
{
  return source;
}
string edge::getTarget()
{
  return _target;
}