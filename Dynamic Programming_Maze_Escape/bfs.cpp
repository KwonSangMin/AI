//
// bfs.cpp - Version 1.0
// KwonSangMin, 20151028, ckasd456@unist.ac.kr
/* check_visted function take a role that was this node already visited or not.
   if the node was not visited, then put next Coordinate at the fringe list which has First in First out priority if the location is valid and it did not visited before
   if visiting Coordinate is Goal Coordination then it return empty value. then my program will print shortest path to Goal location
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

	bool operator==(const Coordinate& rhs) const {
		return x == rhs.x && y == rhs.y;
	}

	bool operator!=(const Coordinate& rhs) const {
		return !(rhs == *this);
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
	list<Coordinate> Re_visited()//Return path
	{
		return visited;
	}
};
list<Coordinate> fringe;//First in First out list of fringe
list<path> path_list;//All visited coordinate list untill now
list<Coordinate> Visited;//check list for is it already visited or not
int check_visited(Coordinate x)//if the Coordinate x is already visited, then return 1. The other return 0
{
	list<Coordinate>::iterator it = Visited.begin();
	for (; it != Visited.end(); it++)
	{
		if(*it==x)
		{
			return 1;
		}
	}
	return 0;
}
class BreadthFirstSearchAgent {
public:

	BreadthFirstSearchAgent(int size_x, int size_y) {

		// enter your code here
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
			if (hasWallSouth == 0)
			{
				Coordinate next(Now.getX(), Now.getY() + 1);
				if (check_visited(next)==0)//If next Coordinate is not Visited, then append next to fringe list
				{
					fringe.push_back(next);//Update fringe list
					Visited.push_front(next);//Append Visited list
					instant_path.append_path(Now.getX(), Now.getY() + 1);//append next coord
					path_list.push_back(instant_path);
					instant_path = path_until_now;//restore path
				}
			}
			if (hasWallNorth == 0)
			{
				Coordinate next(Now.getX(), Now.getY() - 1);
				if (check_visited(next) == 0)
				{
					fringe.push_back(next);
					Visited.push_front(next);
					instant_path.append_path(Now.getX(), Now.getY() - 1);//append next coord
					path_list.push_back(instant_path);
					instant_path = path_until_now;//restore path
				}
			}
			if (hasWallEast == 0)
			{
				Coordinate next(Now.getX() + 1, Now.getY());
				if (check_visited(next) == 0)
				{
					fringe.push_back(next);
					Visited.push_front(next);
					instant_path.append_path(Now.getX() + 1, Now.getY());//append next coord
					path_list.push_back(instant_path);
					instant_path = path_until_now;//restore path
				}
			}
			if (hasWallWest == 0)
			{
				Coordinate next(Now.getX() - 1, Now.getY());
				if (check_visited(next) == 0)
				{
					fringe.push_back(next);
					Visited.push_front(next);
					instant_path.append_path(Now.getX() - 1, Now.getY());//append next coord
					path_list.push_back(instant_path);
				}
			}
			return fringe.front();//return next location
		}
		return {};//return empty when we find Goal.
	}

	list<Coordinate> getShortestPath() {

		// enter your code here
		return path_list.front().Re_visited();
	}

};


int main(int argc, char* argv[]) {

	int size_x, size_y;

	if (argc == 3) {
		size_x = atoi(argv[1]);
		size_y = atoi(argv[2]);
	}
	else {
		cerr << "Error: wrong arguments." << endl;
		return -1;  // do nothing
	}

	BreadthFirstSearchAgent agent(size_x, size_y);//maze size confirm
	//agent initial position is (0,0)
	Coordinate start(0, 0);
	fringe.push_back(start);
	Visited.push_front(start);
	path init_path(0, 0);
	path_list.push_back(init_path);
	while (true) {
		string s1, s2, s3, s4, s5;
		cin >> s1 >> s2 >> s3 >> s4 >> s5;//sensing information

		bool isExit = (s1 != "0");
		bool hasWallSouth = (s2 != "0");
		bool hasWallNorth = (s3 != "0");
		bool hasWallEast = (s4 != "0");
		bool hasWallWest = (s5 != "0");

		auto coord = agent.move(isExit, hasWallSouth, hasWallNorth, hasWallEast, hasWallWest);//chosen next position

		if (coord) {
			cout << coord->getX() << " " << coord->getY() << endl;
		}
		else {
			break;
		}
	}

	list<Coordinate> path = agent.getShortestPath();

	cout << "PATH" << endl;
	for (auto&& coord : path) {
		cout << coord.getX() << " " << coord.getY() << endl;
	}
	cout << "END" << endl;

	return 0;
}