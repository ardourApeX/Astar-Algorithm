#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include<algorithm>
using namespace std;



// Enumerators
enum class State {kEmpty, //When there is a 0 in 1.board file. It denotes path is cleared.
                  kObstacle, //When there is a 1 in 1.board file. It denotes Obstacle.
                  kClosed, // When the node is visited. Its state from whatever gets changed to kClosed. 
                  kPath, //When the node is considered as a path
                  kStart, //For Starting Point
                  kFinish}; //For Goal Point

const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
//ReadBoradFile Function
//It will take data from board file and generate a 2D vector comprise of States
vector<vector<State>> ReadBoardFile(string path) //Path of 1.board file
{
  ifstream myfile (path); //Creating an object for file
  vector<vector<State>> board{}; //Intializing 2D Vector
  if (myfile) 
  {
    string line;
    while (getline(myfile, line))
    {
      vector<State> row = ParseLine(line); //Generating State vector line by line
      board.push_back(row); //Pushing back 1D vector to a 2D vector to act as a single row
    }
  }
  return board; //Returning 2D vector named board, comprise of Sates corresponding to 1.board file
}



// ParseLine Function
// Assign states in 1.board file
vector<State> ParseLine(string line) 
{
    istringstream sline(line);  //Initiating an object for file
    int n;  //For Integer value
    char c; //For , 
    vector<State> row; //State vector
    while (sline >> n >> c) 
    {
      if (n == 0) 
      {
        row.push_back(State::kEmpty); //Pushing back empty state to vector
      } 
      else 
      {
        row.push_back(State::kObstacle); //Pushing back obstacle to vector
      }
    }
    return row; //Returning vector comprise of States
}



//PrintBoard Function
//Just to print the board with the help of CellString
void PrintBoard(const vector<vector<State>> board) 
{
  for (int i = 0; i < board.size(); i++) 
  {
    for (int j = 0; j < board[i].size(); j++) 
    {
      cout << CellString(board[i][j]);
    }
    cout << "\n";
  }
}



//CellString Function
//Return an actual obstacle if one encountered"
string CellString(State cell) 
{
  switch(cell) 
  {
    case State::kObstacle: return "⛰️   ";
    case State::kPath: return "🚗   ";
    case State::kStart: return  "🚦   ";
    case State::kFinish: return "🏁  ";
    default: return "0   "; 
  }
}



vector<vector<State>> Search(vector<vector<State>> grid, int init[2], int goal[2]) 
{ 

  //init & goal are integer arrays.
  //init holds coordinates of start position
  //goal---------------------- end ---------

  vector<vector<int>> open{}; //Integer Vector
  //Purpose of open : TO STORE THE COORDINATES OF VISITED NODES.
  
  int x = init[0]; //Accessing X coordinate of start point from init
  int y = init[1]; //--------- Y -----------------------------------
  int g = 0;
  int h = Heuristic(x, y, goal[0], goal[1]);
  AddToOpen(x, y, g, h, open, grid);
  while(open.size() > 0)
  {
    CellSort(&open);
    auto current = open.back(); //The one with least F value is postioned at very last
    open.pop_back(); //popping out all the nodes from open list as they aren't open anymore
    x = current[0];
    y = current[1];
    grid[x][y] = State::kPath; //Changing state of the node which has been chosen as a Path
    if(x == goal[0] && y == goal[1])
    {
       // Check if we're done.
      grid[init[0]][init[1]] = State::kStart;
      grid[goal[0]][goal[1]] = State::kFinish;
      return grid;
    }


    // If we're not done, expand search to current node's neighbors.
    ExpandNeighbors(current, goal, open, grid);
  }
  cout << "No path found!" << "\n";
  return std::vector<vector<State>> {};
}



//Heuristic Function
// Calculate the Manhattan distance
int Heuristic(int x1, int y1, int x2, int y2) {
  return abs(x2 - x1) + abs(y2 - y1);
}



//CheckValidCell Function
//Check whether the cell is empty or not for further visit
bool CheckValidCell(int x, int y, vector<vector<State>> grid)
{
  if((x >= 0 && x < grid.size()) && (y >=0 && y < grid[0].size())) //checking whether x,y belongs to grid size or not
     {
       if(grid[x][y] == State::kEmpty) //If belongs then check whether it is empty or not
         return true;
       else
         return false;
     }  
}


// TODO: Write the AddToOpen function here.
void AddToOpen(int x, int y, int g, int h, vector<vector<int>> &OpenNodes, vector<vector<State>> &Grid)
{
  OpenNodes.push_back(vector<int>{x, y, g, h});
  Grid[x][y] = State::kClosed;
}



void ExpandNeighbors( const vector<int> &current, int goal[2], vector<vector<int>> &open, vector<vector<State>> &grid )
{
  x_current = current[0];
  y_current = current[1];
  g_current = current[2];
  //No need of h value because it is different for every node
  //As there are 4 possibilites
  for(int i = 0; i < 4; i++)
  {
    int x_new = x_current + delta[i][0];
    int y_new = y_current + delta[i][1];
    if(CheckValidCell(x_new, y_new, grid))
    {
      int g_new = g_current + 1;
      int h_new = Heuristic(x_new, y_new, goal[0], goal[1]);
      AddToOpen(x_new, y_new, g_new, h_new, open, grid);

    }
  } 
}





// function to compare two node values
bool Compare(vector<int> node1, vector<int> node2)
{ 
  // node1 and 2 are comprise of {x, y, g, h}
  // so in order to calculate fValue all you need to apply indexing
  
  int f1, f2;
  f1 = node1[2] + node1[3]; //Accessing g and h value of node1
  f2 = node2[2] + node2[3]; //Accessing g and h value of node2
//f  = g        + h
  if(f1 > f2)
    return true;
  else
    return false;
}



//CellSort Function
//Sort the 2D vector of ints in descending order.
void CellSort(vector<vector<int>> *v)
{
  sort(v -> begin(), v -> end(), Compare);
}


#include "test.cpp"



int main() {
  int init[2]{0, 0};
  int goal[2]{4, 5};
  auto board = ReadBoardFile("1.board");
  auto solution = Search(board, init, goal);
  PrintBoard(solution);
  // Tests

  TestHeuristic();
  TestAddToOpen();
  TestCompare();
  TestSearch();
  TestCheckValidCell();
  TestExpandNeighbors();
}