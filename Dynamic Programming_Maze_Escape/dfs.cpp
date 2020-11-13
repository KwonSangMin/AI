//
// dfs.cpp - Version 1.0
// Kwon SangMin, 20151028, ckasd456@unist.ac.kr
/*
	I use map STL for making a least cost map of All visited Coordinate
	My IsShortest function get 2 arguments which are Coordinate and cost value to the Coordinate.
	whenever agent expand the fringe list, agent compare current least cost to the Coordinate if it is new least cost, then update new shortest path to the Coordinate
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
#	include <map>
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
  Coordinate(int x, int y) : x(x), y(y) {}

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
  bool operator<(const Coordinate& rhs) const {
	  if(x!=rhs.x)
	  return x < rhs.x;
	  return y > rhs.y;
  }
};
class path
{
	list<Coordinate> visited;
public:
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
	list<Coordinate> Re_visited()
	{
		return visited;
	}
	int get_depth()
	{
		return visited.size();
	}
};
map<Coordinate, int> cost_map;//Store least cost of the Coordinate
list<Coordinate> fringe;//Store fringes at current depth with Last in First out property
list<path> path_list;//Store path_list
list<path> Next_path_list;//Store for Next Limit
list<Coordinate> Next_fringe_list;//Store for Next Limit 
bool reach_Limit = 0;
class DepthFirstSearchAgent {
	int Limit;
public:

  DepthFirstSearchAgent(int size_x, int size_y) {
    // enter your code here
	  Limit = 2;
  }
  int IsShortest(Coordinate x, int y)
  {
	  if(x.getX()==0&&x.getY()==0)
	  {
		  return 0;
	  }
	  if (cost_map.find(x) == cost_map.end())//if we visit x at first just insert cost data
	  {
		  cost_map.insert(pair(x, y));
		  return 1;
	  }
	  else//if we already visited x
	  {
		   if (cost_map[x]> y)//if we find least cost to x, then update the cost
		  {
			   cost_map.erase(x);
			   cost_map.insert(pair(x, y));
			   return 1;
		  }
		  else
		  {
			  return 0;
		  }
	  }
  }
  optional<Coordinate> move(bool isExit, bool hasWallSouth, bool hasWallNorth, bool hasWallEast, bool hasWallWest) {
	  // enter your code here
	  Coordinate Now = fringe.front();//Get Now Coordinate value.
	  fringe.pop_front();//update fringe list
	  if (isExit != 1)//when current coord is not obtimal solution
	  {
		  path path_until_now = path_list.front();//Get path untill now
		  path_list.pop_front();//Update path list
		  path instant_path = path_until_now;
		  int cur_cost = instant_path.get_depth()+1;
		  if (instant_path.get_depth() == Limit)//Store fringe in Limit at the Next fringes List 
		  {
			  reach_Limit = 1;
			  if (hasWallSouth == 0)
			  {
				  Coordinate next(Now.getX(), Now.getY() + 1);
				  if (IsShortest(next, cur_cost) != 0)//If this path is not shortest path of the next Coordination then we do not append this path
				  {
					  Next_fringe_list.push_front(next);//Update fringe list
					  instant_path.append_path(Now.getX(), Now.getY() + 1);//append next coord
					  Next_path_list.push_front(instant_path);
					  instant_path = path_until_now;//restore path
				  }
			  }
			  if (hasWallNorth == 0)
			  {
				  Coordinate next(Now.getX(), Now.getY() - 1);
				  if (IsShortest(next, cur_cost) != 0)
				  {
					  Next_fringe_list.push_front(next);
					  instant_path.append_path(Now.getX(), Now.getY() - 1);//append next coord
					  Next_path_list.push_front(instant_path);
					  instant_path = path_until_now;//restore path
				  }
			  }
			  if (hasWallEast == 0)
			  {
				  Coordinate next(Now.getX() + 1, Now.getY());
				  if (IsShortest(next, cur_cost) != 0)
				  {
					  Next_fringe_list.push_front(next);
					  instant_path.append_path(Now.getX() + 1, Now.getY());//append next coord
					  Next_path_list.push_front(instant_path);
					  instant_path = path_until_now;//restore path
				  }
			  }
			  if (hasWallWest == 0)
			  {
				  Coordinate next(Now.getX() - 1, Now.getY());
				  if (IsShortest(next, cur_cost) != 0)
				  {
					  Next_fringe_list.push_front(next);
					  instant_path.append_path(Now.getX() - 1, Now.getY());//append next coord
					  Next_path_list.push_front(instant_path);
				  }
			  }
			  if (fringe.empty())//if fringe is empty it means that we traverse all node within Limit so extend Limit
			  {
				  Limit++;
				  reach_Limit = 0;
				  Coordinate start(0, 0);
				  while (!Next_fringe_list.empty())
				  {
					  fringe.push_back(Next_fringe_list.front());
					  Next_fringe_list.pop_front();
					  path_list.push_back(Next_path_list.front());
					  Next_path_list.pop_front();
				  }
				  return fringe.front();
			  }
			  return fringe.front();
		  }
		  else
		  {
			  if (hasWallSouth == 0)
			  {
				  Coordinate next(Now.getX(), Now.getY() + 1);
				  if (IsShortest(next,cur_cost)!= 0)//If this path is not shortest path of the next Coordination then we do not append this path
				  {
					  fringe.push_front(next);//Update fringe list
					  instant_path.append_path(Now.getX(), Now.getY() + 1);//append next coord
					  path_list.push_front(instant_path);
					  instant_path = path_until_now;//restore path
				  }
			  }
			  if (hasWallNorth == 0)
			  {
				  Coordinate next(Now.getX(), Now.getY() - 1);
				  if (IsShortest(next, cur_cost) != 0)
				  {
					  fringe.push_front(next);
					  instant_path.append_path(Now.getX(), Now.getY() - 1);//append next coord
					  path_list.push_front(instant_path);
					  instant_path = path_until_now;//restore path
				  }
			  }
			  if (hasWallEast == 0)
			  {
				  Coordinate next(Now.getX() + 1, Now.getY());
				  if (IsShortest(next, cur_cost) != 0)
				  {
					  fringe.push_front(next);
					  instant_path.append_path(Now.getX() + 1, Now.getY());//append next coord
					  path_list.push_front(instant_path);
					  instant_path = path_until_now;//restore path
				  }
			  }
			  if (hasWallWest == 0)
			  {
				  Coordinate next(Now.getX() - 1, Now.getY());
				  if (IsShortest(next, cur_cost) != 0)
				  {
					  fringe.push_front(next);
					  instant_path.append_path(Now.getX() - 1, Now.getY());//append next coord
					  path_list.push_front(instant_path);
				  }
			  }
			  if (fringe.empty())
			  {
				  Limit++;
				  reach_Limit = 0;
				  Coordinate start(0, 0);
				  while (!Next_fringe_list.empty())
				  {
					  fringe.push_back(Next_fringe_list.front());
					  Next_fringe_list.pop_front();
					  path_list.push_back(Next_path_list.front());
					  Next_path_list.pop_front();
				  }
				  return fringe.front();
			  }
			  return fringe.front();//return next location
		  }
	  }
	  return {};//return empty when we find Goal.
  }

  list<Coordinate> getShortestPath() {

    // enter your code here
	  return path_list.front().Re_visited();
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

  DepthFirstSearchAgent agent(size_x, size_y);
  Coordinate start(0, 0);
  fringe.push_back(start);
  path init_path(0, 0);
  path_list.push_back(init_path);
  while(true) {
    string s1, s2, s3, s4, s5;
    cin >> s1 >> s2 >> s3 >> s4 >> s5;

    bool isExit = (s1 != "0");
    bool hasWallSouth = (s2 != "0");
    bool hasWallNorth = (s3 != "0");
    bool hasWallEast = (s4 != "0");
    bool hasWallWest = (s5 != "0");

    auto coord = agent.move(isExit, hasWallSouth, hasWallNorth, hasWallEast, hasWallWest);

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

