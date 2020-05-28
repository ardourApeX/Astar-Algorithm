#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

enum class State {kEmpty, kObstacle}; // Defining Enumerators


// Function to generate vector of State from string (a line from 1.board file)
vector<State> ParseLine(string line) //Assigning State into a String
{ 
    istringstream sline(line);
    int n; //For numeric values
    char c; //For ,
    vector<State> row;
    while (sline >> n >> c && c == ',') {
      if (n == 0) {
        row.push_back(State::kEmpty);
      } else {
        row.push_back(State::kObstacle);
      }
    }
    return row;
}

//Function to generate a 2D vector of State from 1.board file using ParseLine Function
vector<vector<State>> ReadBoardFile(string path) //Function to Convert Vector full of States
{
  ifstream fin;
  fin.open(path);
  vector<vector<State>> board{}; //Vector comprise of binary input from 1.board
  if (myfile) //If such file exists then...
  {
    string line;
    while (getline(fin, line)) 
    {
      Board.push_back(ParseLine(Line));
    }
  }
  return board; //Returning a Vector consit of States
  fin.close();

}

//Heuristic Function to calculate heuristic distance
int Heuristic (int x1, int y1, int x2, int y2)
{
  return (abs(x2 - x1) + abs(y2 - y1));
}


//It will designated visited nodes with a State enumerator kClosed.
void AddToOpen(int x, int y, int g, int h, vector<vector<int>> &OpenNodes, vector<vector<State>> &Grid)
{
  vector<int> node = {x, y, g, h};
  Grid[x][y] = State::kClosed;
}



//Search Function
vector<vector<State>> Search (auto grid, int Start[2], int Goal[2])
{
  cout<<"No path found";
  return vector<vector<State>> {};
  
}

//Function to return image of obstacle on the basis of state vector
string CellString(State Cell)  
{
  if(Cell == State::kObstacle)
    return"⛰️ ";
  else
    return "0 "; 
}


void PrintBoard(const vector<vector<State>> Board)
{

  for(auto I : Board){ //OR for(vector<State> I : Board)
    for(auto J : I)  //OR for(State J : I)
      cout<<CellString(J);
    cout<<"\n";
  }
}



#include "test.cpp" //for testing solution



int main() {
  // TODO: Declare "init" and "goal" arrays with values {0, 0} and {4, 5} respectively.
  int init[] = {0,0};
  int goal[] = {4,5};
  auto board = ReadBoardFile("1.board");
  auto solution = Search(board, init, goal);
  PrintBoard(solution);
  TestHeuristic();
}
