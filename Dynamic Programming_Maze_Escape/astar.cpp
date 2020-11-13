//
// astar.cpp - Version 1.0
// Kwon SangMin, 20151028, ckasd456@unist.ac.kr
/*
	my check_visited fucntion take a role that if the Coordinate(=node) was not visited, then just put the Coordinate at fringe list.
	on the other hand, if the Coordinate was already visited, then compare with current cost and past Least cost to the Coordinate
	If find the new Least cost to Coordinate, then update the cost. By doing this, Agents can expand the fringe with only least cost path
*/
// Please write your name, your student ID, and your email address here.
// Moreover, please describe the implementation of your functions here.
// You will have to submit this file.
//

#include <iostream>
#include <list>
#include <string>
#include <cstdlib>

// ---------------------------------------------------------------------
// Include the optional header with backward compatibility
// see http://codereview.stackexchange.com/questions/136350/seamlessly-migrating-experimental-optional-to-optional
#if __has_include(<optional>)
#   include <optional>
#	include <queue>
#	include <vector>
namespace stdx {
  using namespace ::std;
}
#elif __has_include(<experimental/optional>)
#   include <experimental/optional>
namespace stdx {
  using namespace ::std;
  using namespace ::std::experimental;
}
#else
#   error <experimental/optional> and <optional> not found
#endif

using namespace stdx;
// ---------------------------------------------------------------------


#define MAX_SIZE 300


class Coordinate {

  int x, y;
public:
	float distance;
	bool update;
	float cost;
	Coordinate(int x, int y) : x(x), y(y) { }

  int getX() const {
    return x;
  }

  int getY() const {
    return y;
  }

  bool operator==(const Coordinate &rhs) const {
    return x == rhs.x && y == rhs.y;
  }

  bool operator!=(const Coordinate &rhs) const {
    return !(rhs == *this);
  }
  void set_cost(float x) // update cost value
  {
	  cost = x;
  }
};
class path
{
	list<Coordinate> visited;//list for all visited node
public:
	float cost;//recent node cost for synchronizing with fringe queue
	path(int x, int y)
	{
		Coordinate loc(x, y);
		visited.push_back(loc);
	}
	void append_path(int x, int y)
	{
		Coordinate loc(x, y);
		visited.push_back(loc);
	}
	list<Coordinate> Re_visited()//Return path
	{
		return visited;
	}
	int get_depth()
	{
		return visited.size();
	}
	void set_path_cost(float x) {
		cost = x;
	}
};
struct cmp//Logical function for ordering Coordinate
{
	bool operator()(const Coordinate &x, const Coordinate &y)
	{
		return x.cost > y.cost;
	}
};
struct cmp2//Logical function for ordering path 
{
	bool operator()(const path& x, const path& y) {
		return x.cost > y.cost;
	}
};
list<Coordinate> visited;
priority_queue<Coordinate, vector<Coordinate>, cmp> fringe;
priority_queue<path, vector<path>, cmp2> path_list;
class AStarFirstSearchAgent {

public:

  AStarFirstSearchAgent(int size_x, int size_y) {

    // enter your code here
	  Coordinate start(0, 0);
	  start.cost = 0;
	  start.update = true;
	  visited.push_back(start);
	  fringe.push(start);
	  path init_path(0, 0);
	  init_path.cost=0;
	  path_list.push(init_path);
  }
  optional<Coordinate> check_visited(Coordinate x)//if the Coordinate x is already visited, then return the Coordinate object. The other return {}
  {
	  list<Coordinate>::iterator it = visited.begin();
	  for (; it != visited.end(); it++)
	  {
		  if (*it == x)
		  {
			  return *it;
		  }
	  }
	  return {};
  }
  optional<Coordinate> move(bool isExit, bool hasWallSouth, bool hasWallNorth, bool hasWallEast, bool hasWallWest, double distance) {
  
    // enter your code here
	  Coordinate Now = fringe.top();
	  fringe.pop();
	  if (isExit != 1)//when current coord is not obtimal solution
	  {
		  path path_until_now = path_list.top();//Get path untill now
		  path_list.pop();//Update path list
		  path instant_path = path_until_now;
		  float cost = instant_path.get_depth() + distance;
		  if (Now.update==false)//if this Coordinate cost is not updated, then update the cost and dont expand fringe list
		  {
			  Now.cost = cost;
			  Now.distance=distance;
			  instant_path.cost = cost;
			  Now.update = true;
			  fringe.push(Now);
			  path_list.push(instant_path);
			  return fringe.top();
		  }
		  if (hasWallSouth == 0)
		  {
			  Coordinate next(Now.getX(), Now.getY() + 1);
			  auto ptr_Coord = check_visited(next);
			  if (!ptr_Coord)//If we meet the Coordinate at first just append at fringe list
			  {
				  visited.push_front(next);
				  next.update = false;
				  next.set_cost(0);
				  fringe.push(next);//Update fringe list
				  instant_path.append_path(Now.getX(), Now.getY() + 1);//append next coord
				  instant_path.set_path_cost(0);
				  path_list.push(instant_path);
				  instant_path = path_until_now;//restore path
			  }
			  else//if the Coordinate was already visited and agent find the new least cost path, then update the cost and shortest path to the Coordinate
			  {
				  float new_cost = (ptr_Coord->distance) + instant_path.get_depth() + 1;
				  if ((ptr_Coord->cost) > new_cost)
				  {
					  next.set_cost(new_cost);
					  fringe.push(next);//Update fringe list
					  instant_path.append_path(Now.getX(), Now.getY() + 1);//append next coord
					  instant_path.set_path_cost(new_cost);
					  path_list.push(instant_path);
					  instant_path = path_until_now;//restore path
				  }
			  }
		  }
		  if (hasWallNorth == 0)
		  {
			  Coordinate next(Now.getX(), Now.getY() - 1);
			  auto ptr_Coord = check_visited(next);
			  if (!ptr_Coord)
			  {
				  visited.push_front(next);
				  next.update = false;
				  next.set_cost(0);
				  fringe.push(next);//Update fringe list
				  instant_path.append_path(Now.getX(), Now.getY() - 1);//append next coord
				  instant_path.set_path_cost(0);
				  path_list.push(instant_path);
				  instant_path = path_until_now;//restore path
			  }
			  else
			  {
				  float new_cost = (ptr_Coord->distance) + instant_path.get_depth() + 1;
				  if ((ptr_Coord->cost) > new_cost)
				  {
					  next.set_cost(new_cost);
					  fringe.push(next);//Update fringe list
					  instant_path.append_path(Now.getX(), Now.getY() - 1);//append next coord
					  instant_path.set_path_cost(new_cost);
					  path_list.push(instant_path);
					  instant_path = path_until_now;//restore path
				  }
			  }

		  }
		  if (hasWallEast == 0)
		  {
			  Coordinate next(Now.getX() + 1, Now.getY());
			  auto ptr_Coord = check_visited(next);
			  if (!ptr_Coord)
			  {
				  visited.push_front(next);
				  next.update = false;
				  next.set_cost(0);
				  fringe.push(next);//Update fringe list
				  instant_path.append_path(Now.getX() + 1, Now.getY());//append next coord
				  instant_path.set_path_cost(0);
				  path_list.push(instant_path);
				  instant_path = path_until_now;//restore path
			  }
			  else
			  {
				  float new_cost = (ptr_Coord->distance) + instant_path.get_depth() + 1;
				  if ((ptr_Coord->cost) > new_cost)
				  {
					  next.set_cost(new_cost);
					  fringe.push(next);//Update fringe list
					  instant_path.append_path(Now.getX() + 1, Now.getY());//append next coord
					  instant_path.set_path_cost(new_cost);
					  path_list.push(instant_path);
					  instant_path = path_until_now;//restore path
				  }
			  }

		  }
		  if (hasWallWest == 0)
		  {
			  Coordinate next(Now.getX() - 1, Now.getY());
			  auto ptr_Coord = check_visited(next);
			  if (!ptr_Coord)
			  {
				  visited.push_front(next);
				  next.update = false;
				  next.set_cost(0);
				  fringe.push(next);//Update fringe list
				  instant_path.append_path(Now.getX() - 1, Now.getY());//append next coord
				  instant_path.set_path_cost(0);
				  path_list.push(instant_path);
			  }
			  else
			  {
				  float new_cost = (ptr_Coord->distance) + instant_path.get_depth() + 1;
				  if ((ptr_Coord->cost) > new_cost)
				  {
					  next.set_cost(new_cost);
					  fringe.push(next);//Update fringe list
					  instant_path.append_path(Now.getX() - 1, Now.getY());//append next coord
					  instant_path.set_path_cost(new_cost);
					  path_list.push(instant_path);
				  }
			  }
		  }
		  return fringe.top();//return next location
	  }
	  return {};//return empty when we find Goal.
  }

  list<Coordinate> getShortestPath() {
    
    // enter your code here
	  path x = path_list.top();
	  return x.Re_visited();    
  }

};

int main(int argc, char *argv[]) {

  int size_x, size_y;

  if (argc == 3) {
    size_x = atoi(argv[1]);
    size_y = atoi(argv[2]);
  } else {
    cerr << "Error: wrong arguments." << endl;
    return -1;  // do nothing
  }

  AStarFirstSearchAgent agent(size_x, size_y);

  while(true) {
    string s1, s2, s3, s4, s5, s6;
    cin >> s1 >> s2 >> s3 >> s4 >> s5 >> s6;

    bool isExit = (s1 != "0");
    bool hasWallSouth = (s2 != "0");
    bool hasWallNorth = (s3 != "0");
    bool hasWallEast = (s4 != "0");
    bool hasWallWest = (s5 != "0");
    double distance = stof(s6);

    auto coord = agent.move(isExit, hasWallSouth, hasWallNorth, hasWallEast, hasWallWest, distance);

    if (coord) {
      cout << coord->getX() << " " << coord->getY() << endl;
    } else {
      break;
    }
  }

  list<Coordinate> path = agent.getShortestPath();

  cout << "PATH" << endl;
  for(auto&& coord : path) {
    cout << coord.getX() << " " << coord.getY() << endl;
  }
  cout << "END" << endl;

  return 0;
}
