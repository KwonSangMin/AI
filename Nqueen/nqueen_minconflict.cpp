#include <iostream>
#include <cstring>
#include <cstdlib>
#include <list>
#include <map>
#include <vector>
using namespace std;
// Kwon Sangmin, 20151028, ckasd456@unist.ac.kr
/*
 * The n-queens problem solver
 *
 * size      - the number of queens
 * isVerbose - whether the intermediate nodes are displayed
 */
bool get_next(int**, int);
class Coord {
public:
    int x;
    int y;
    Coord(int x2, int y2)
    {
        x = x2;
        y = y2;
    }
    bool operator<(const Coord& rhs) const
    {
        if (x != rhs.x)
            return x < rhs.x;
        else
            return y < rhs.y;
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
    bool operator()(xyandnum x, xyandnum y) {
        return x.numofx < y.numofx;
    }
};
map<string, int> path_list;
map<int, int> Queen;

void Init_Board(int**, int);
void decrease_board(int**, int, int, int);
void update_board(int**, int, int, int);
void solve_nqueen(int size, bool isVerbose) {
    int** Board = new int* [size];
    for (int i = 0; i < size; i++)
    {
        Board[i] = new int[size];
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == j)
            {
                Board[i][j] = 0;
            }
            else
                Board[i][j] = 0;
        }
    }
    Init_Board(Board, size);
    bool goal = false;
    int x = 0;
    while (goal == false)
    {
        goal = get_next(Board, size);
        if (isVerbose == true && goal == false)
        {
            cout << "-------- " << x++ << endl;
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    if (Board[i][j] == 1)
                        cout << 'Q';
                    else
                        cout << "*";
                }
                cout << endl;
            }
        }
    }
    if (goal == true && isVerbose == true) {
        cout << "-------- Solution" << endl;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (Board[i][j] == 1)
                    cout << 'Q';
                else
                    cout << "*";
            }
            cout << endl;
        }
    }
    else if (goal == true && isVerbose == false)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (Board[i][j] == 1)
                    cout << 'Q';
                else
                    cout << "*";
            }
            cout << endl;
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
bool get_next(int** Board, int size)
{
    string path = "";//for checking visited path
    int check_infinity = 0;
    for (int i = 0; i < size; i++)
    {
        xyandnum min_conflict(0, i, 10000000);
        for (int j = 0; j < size; j++)
        {
            if (Board[i][j] < min_conflict.numofx)
            {
                min_conflict.numofx = Board[i][j];
                min_conflict.y = i;
                min_conflict.x = j;
            }
        }
        Coord origin(Queen[i], i);
        path += (char)origin.x + 0x30;
        path += ",";
        path += (char)origin.y + 0x30;
        path += ",";
        if ((origin.x == min_conflict.x) && (origin.y == min_conflict.y))
        {
            check_infinity++;
        }
        else
        {
            decrease_board(Board, origin.x, origin.y, size);
            update_board(Board, min_conflict.x, min_conflict.y, size);
            Queen[i] = min_conflict.x;
        }

    }
    if (path_list.find(path) == path_list.end() && check_infinity < size)
        path_list.insert(make_pair(path, 1));
    else
    {
        int randy = rand() % size;
        int newx = rand() % size;
        decrease_board(Board, Queen[randy], randy, size);
        update_board(Board, newx, randy, size);
        Queen[randy] = newx;
        return false;
    }
    for (int i = 0; i < size; i++)
    {
        if (Board[i][Queen[i]] != 1)
            return false;
    }
    return true;
}
void Init_Board(int** Board, int size)
{
    for (int j = 0; j < size; j++)
    {
        int x;
        int y=j;
        if (j == 0)
        {
            x = 0;
        }
        else
        {
            int H = size;
            int tmp = 0;
            for (int x2 = 0; x2 < size; x2++)
            {
                if (Board[j][x2] < H)
                {
                    H = Board[j][x2];
                    tmp = x2;
                }
            }
            x = tmp;
        }
        Queen.insert(make_pair(j, x));
        for (int i = 0; i < size; i++)
        {
            Board[y][i]++;
        }
        for (int i = 0; i < size; i++)
        {
            Board[i][x]++;
        }
        for (int i = 1; y + i < size; i++)
        {
            if (x + i < size)
                Board[y + i][x + i]++;
            if (x - i >= 0)
                Board[y + i][x - i]++;
        }
        for (int i = 1; y - i >= 0; i++)
        {
            if (x + i < size)
                Board[y - i][x + i]++;
            if (x - i >= 0)
                Board[y - i][x - i]++;
        }
        Board[y][x]--;
    }
}
void decrease_board(int** Board, int x, int y, int size)
{
    for (int i = 0; i < size; i++)
    {
        Board[y][i]--;
    }
    for (int i = 0; i < size; i++)
    {
        Board[i][x]--;
    }
    for (int i = 1; y + i < size; i++)
    {
        if (x + i < size)
            Board[y + i][x + i]--;
        if (x - i >= 0)
            Board[y + i][x - i]--;
    }
    for (int i = 1; y - i >= 0; i++)
    {
        if (x + i < size)
            Board[y - i][x + i]--;
        if (x - i >= 0)
            Board[y - i][x - i]--;
    }
    Board[y][x]++;
}
void update_board(int** Board, int x, int y, int size)
{
    for (int i = 0; i < size; i++)
    {
        Board[y][i]++;
    }
    for (int i = 0; i < size; i++)
    {
        Board[i][x]++;
    }
    for (int i = 1; y + i < size; i++)
    {
        if (x + i < size)
            Board[y + i][x + i]++;
        if (x - i >= 0)
            Board[y + i][x - i]++;
    }
    for (int i = 1; y - i >= 0; i++)
    {
        if (x + i < size)
            Board[y - i][x + i]++;
        if (x - i >= 0)
            Board[y - i][x - i]++;
    }
    Board[y][x]--;
}