#include <iostream>
#include <cstring>
#include <cstdlib>
#include <list>
#include <queue>
using namespace std;
bool update_Board = false;
// Kwon Sangmin, 20151028, ckasd456@unist.ac.kr
/*
 * The n-queens problem solver
 *
 * size      - the number of queens
 * isVerbose - whether the intermediate nodes are displayed
 */
int x = 0;
class Coord {
public:
    int x;
    int y;
    bool Exetend;
    Coord(int x2, int y2)
    {
        x = x2;
        y = y2;
        Exetend = false;
    }
};
class path {
public:
    list<Coord> visited;
    list<Coord> fringe;
    path(){}
    path(list<Coord> a)
    {
       visited = a;
    }
    void Append_coord(Coord x)
    {
        visited.push_back(x);
    }
    list<Coord> retrun_route()
    {
        return visited;
    }
};
list<path> path_list;
class yandnum {
public:
    int y;
    int numofx;
    yandnum(int a, int b)
    {
        y = a;
        numofx = b;
    }
};
class xyandnum {
public:
    int y;
    int x;
    int numofx;
    xyandnum(int a, int b, int c)
    {
        y = b;
        x = a;
        numofx = c;
    }
    Coord coord()
    {
        Coord a(x, y);
        return a;
    }
};
struct cmp {
    bool operator()(yandnum x, yandnum y) {
        return x.numofx > y.numofx;
    }
};//for ascending order
struct cmp2 {
    bool operator()(xyandnum x, xyandnum y) {
        return x.numofx < y.numofx;
    }
};//for descending order
priority_queue<xyandnum, vector<xyandnum>, cmp2> LCV(list<Coord>, char**, int);// queue for LCV priority

bool get_next(char**, int);

void solve_nqueen(int size, bool isVerbose) {
    char **Board = new char*[size];
    for (int i = 0; i < size; i++)
    {
        Board[i] = new char[size];
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
                Board[i][j] = '*';
        }
    } 
    for (int i = 0; i < size; i++) {
        path Init;
        Coord init(i, 0);
        Init.Append_coord(init);
        path_list.push_back(Init);
    }
    bool goal = false;
    
    while (goal == false)
    {
        
        goal = get_next(Board, size);
        if (path_list.empty()&&goal==false)
        {
            cout << "Solution not found. Solution may not exist." << endl;
            break;
        }
        if (isVerbose==true&&goal==false)
        {
            cout << "-------- " << x++ << endl;
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    if (Board[i][j] == 'Q')
                        cout << Board[i][j];
                    else
                        cout << "*";
                }
                cout << endl;
            }
        }
    }
    if(goal==true&&isVerbose==true){
    cout << "-------- Solution"<< endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (Board[i][j] == 'Q')
                cout << Board[i][j];
            else
                cout << "*";
        }
        cout << endl;
    }
    }
    else if(goal==true&&isVerbose==false)
    {
      for(int i=0;i<size;i++)
      {
        for(int j=0;j<size;j++)
        {
          if(Board[i][j]=='Q')
            cout<<Board[i][j];
          else
            cout<<"*";
        }
        cout<<endl;
      } 
    }
    //initailize N Queen Board,
    
}


/*
 * The main function.
 */
int main(int argc, char** argv) {

    int size;
    bool isVerbose = false, isArgValid = true;

    if (argc == 2) {
        size = atoi(argv[1]);
        isArgValid = (size > 0);
    }
    else if (argc == 3) {
        if (strcmp(argv[1], "-v") == 0) {
            isVerbose = true;
            size = atoi(argv[2]);
            isArgValid = (size > 0);
        }
        else {
            isArgValid = false;
        }
    }
    else {
        isArgValid = false;
    }

    if (!isArgValid) {
        cout << "Error in command line arguments." << endl;
        cout << "Usage: " << argv[0] << " [-v] n" << endl;
        cout << "where n is the number of queens and the size of the board (nxn)." << endl;
        cout << "The option -v enables the output of the intermediate states of" << endl;
        cout << "the search procedure." << endl;
        return 1;
    }

    solve_nqueen(size, isVerbose);

    return 0;
}
bool get_next(char** Board, int size)
{
    path CP = path_list.front();
    path_list.pop_front();
    list<Coord> visited = CP.retrun_route();
    if (visited.size() == size)
    {
        Coord xy = visited.back();
        int x = xy.x;
        int y = xy.y;
        Board[y][x] = 'Q';
        return true;
    }//we find solution.
    list<int> valid_y;//list for no Queen row
    for (int i = 1; i < size; i++)
    {
        valid_y.push_back(i);
    }
    if (update_Board == true)//If we reach new path, then clear the Board.
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                Board[i][j] = '*';
            }
        }
        update_Board = false;
    }
    if (visited.back().Exetend == true)//current path is just extending the past path
    {
        Coord xy = visited.back();
        visited.back().Exetend = false;
        int x = xy.x;
        int y = xy.y;
        valid_y.remove(y);
        for (int i = 0; i < size; i++)
        {
            Board[y][i] = 'x';
        }
        for (int i = 0; i < size; i++)
        {
            Board[i][x] = 'x';
        }
        for (int i = 1; y + i < size; i++)
        {
            if (x + i < size)
                Board[y + i][x + i] = 'x';
            if (x - i >= 0)
                Board[y + i][x - i] = 'x';
        }
        for (int i = 1; y - i > 0; i++)
        {
            if (x + i < size)
                Board[y - i][x + i] = 'x';
            if (x - i >= 0)
                Board[y - i][x - i] = 'x';
        }
        Board[y][x] = 'Q';
        while (!visited.empty())
        {
            Coord xy = visited.front();
            visited.pop_front();
            int y = xy.y;
            valid_y.remove(y);
        }
    }
    else//if we search new path, then we have to update Board condition
    {
        while (!visited.empty())
        {
            Coord xy = visited.front();
            visited.pop_front();
            int x = xy.x;
            int y = xy.y;
            valid_y.remove(y);
            for (int i = 0; i < size; i++)
            {
                Board[y][i] = 'x';
            }
            for (int i = 0; i < size; i++)
            {
                Board[i][x] = 'x';
            }
            for (int i = 1; y + i < size; i++)
            {
                if (x + i < size)
                    Board[y + i][x + i] = 'x';
                if (x - i >= 0)
                    Board[y + i][x - i] = 'x';
            }
            for (int i = 1; y - i > 0; i++)
            {
                if (x + i < size)
                    Board[y - i][x + i] = 'x';
                if (x - i >= 0)
                    Board[y - i][x - i] = 'x';
            }
            Board[y][x] = 'Q';
        }
    }
    priority_queue<yandnum, vector<yandnum>, cmp> pq;
    int valid_x = 0;
    if (valid_y.size() < size - CP.retrun_route().size())//If there is no enough valid row, then just escape the current path.
    {
        update_Board = true;
        return false;
    }
    while (!valid_y.empty())
    {
        int y = valid_y.front();
        valid_y.pop_front();
        int value = 0;
        for (int i = 0; i < size; i++)
        {
            if (Board[y][i] == '*')
                value++;
        }
        if (value == 0)
        {
            update_Board = true;
            return false;
        }
        else
        {
            valid_x++;
        }
        yandnum A(y, value);
        pq.push(A);
    }//Ordering the next fringe with ascending order which is related with MRV.
    if (valid_x < size - CP.retrun_route().size())//If we dont have enough colum, then just escape
    {
        update_Board = true;
        return false;
    }
    int y = pq.top().y;
    pq.pop();
    for (int i = 0; i < size; i++)
    {
       if (Board[y][i] == '*')
       {
            Coord a(i, y);
            CP.fringe.push_back(a);
       }
    }//update fringe list.
    priority_queue<xyandnum, vector<xyandnum>, cmp2> Pq = LCV(CP.fringe,Board,size);//Ordering fringe list with descending order which is related with LCV
    while (!Pq.empty())
    {
        Coord next(Pq.top().x,Pq.top().y);
        Pq.pop();
        if (Pq.empty())
            next.Exetend = true;
        path nextp(CP.visited);
        nextp.Append_coord(next);
        path_list.push_front(nextp);
    }//Update next Path.
    return false;
}
priority_queue<xyandnum, vector<xyandnum>, cmp2> LCV(list<Coord> fringe,char** Board,int size)
{
    priority_queue<xyandnum, vector<xyandnum>, cmp2> result;
    int x;
    int y;
    while (!fringe.empty())
    {
        Coord next = fringe.front();
        x = next.x;
        y = next.y;
        fringe.pop_front();
        int count = 0;
        for (int i = 0; i < size; i++)
        {
            if (Board[y][i] == '*')
                count++;
        }
        for (int i = 0; i < size; i++)
        {
            if (Board[i][x] == '*')
                count++;
        }
        for (int i = 1; y + i < size; i++)
        {
            if (x + i < size)
                if (Board[y + i][x + i] == '*')
                    count++;
            if (x - i >= 0)
               if( Board[y + i][x - i] == '*')
                   count++;
        }
        for (int i = 1; y - i > 0; i++)
        {
            if (x + i < size)
                if (Board[y - i][x + i] == '*')
                    count++;
            if (x - i >= 0)
                if(Board[y - i][x - i] == '*')
                    count;
        }
        xyandnum rx(next.x,next.y, count);
        result.push(rx);
    }
    return result;
}
