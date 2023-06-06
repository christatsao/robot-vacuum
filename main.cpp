#include <iostream>
#include <vector>
#include <array>
#include <set>
#include <cassert>
#include <time.h>
#include <queue>

using namespace std;

  const int numcols = 20;  // number of columns in our grid (width)
  const int numrows = 20;  // number of rows in our grid (height)
  char grid[numrows][numcols]; // declare our grid
  char original[numrows][numcols]; // declare our a duplicate of our grid for reference

  int currentRow = 0;      // starting row location of robot
  int currentCol = 0;      // starting col location of robot
  int totalMoves = 0;      // total count of moves made by the robot

  //
  // INIT THE GRID (written for you: please do not change this function)
  //
  void initGrid(){
    for(int r=0; r<numrows; r++){
      for(int c=0; c<numcols; c++){
        if(rand()%100 < 25){ // 25% change of creating random obstacle
          grid[r][c] = '*'; // this is an obstacle
        }
        else { // else we have garbage
          grid[r][c] = '.';   // this is garbage
        }
        original[r][c] = grid[r][c]; // put in our original array for final scoring
      }
    }
  }

  //
  // PRINT THE GRID (written for you: please do not change this function)
  //

  void printGrid(){
    
    cout << "-";
    for(int c=0; c<numcols; c++) // print top border
      cout << "---";
    cout << "-" << endl;

    for (int i = 0; i < numrows; i++) { // print all rows
      cout << "|";
        for (int j = 0; j < numcols; j++) { // print a row
          if ( i==currentRow && j==currentCol )
            cout << " " << 'V' << " "; // print a V for the vaccum
          else
            cout << " " << grid[i][j] << " ";  // print what is at this location
        }
        cout << "|" << endl; 
    }
    cout << "-";
    for(int c=0; c<numcols; c++) // print bottom border
      cout << "---";
    cout << "-" << endl;
  }

  //
  // GET ROW (written for you: please do not change this function)
  //

  int getRow(){   // return the current row location of the robot
      return currentRow;
  }

  int getCol(){
      return currentCol;  // return the current row location of the robot
  }

  //
  // MOVE TO (written for you: please do not change this function)
  //

  bool moveTo(int r, int c){ // move the robot to this location and sweep up what is there
    if (r<0 || r >= numrows) {
      cout << "moveT0() ignoring requested move to " << r << ", " << c << " because it is out of room" << endl;
      return false; // cannot move out of the room 
    }

    if (c<0 || c >= numcols) {
      cout << "moveT0() ignoring requested move to " << r << ", " << c << " because it is out of room" << endl;
      return false; // cannot mvoe out of the room
    }

    if (abs(r-currentRow) > 1 || (abs(c-currentCol) >1)){
      cout << "moveT0() ignoring requested move to " << r << ", " << c << " because it is > 1 in either direction" << endl;
      return false; // cannot move by more than 1 in each direction
    }

    currentRow = r;
    currentCol = c;
    grid[r][c] = ' '; // clean what was there even if it it was an obstacle.
    totalMoves++; // increment the number of total moves taken so far
    return true;
  }





//
// PRINT SCORE
//

  void printScore(){ // written for you: (please do not change this function)
    int obstaclesMissing = 0;
    int obstaclesTotal = 0;
    int garbageTotal = 0;
    int garbageMissed = 0;


    for(int r=0; r<numrows;  r++){
      for(int c=0; c<numcols; c++){
        if (grid[r][c] == '.') garbageMissed++; // found leftover garbage, 
        if (original[r][c] == '*') obstaclesTotal++; // total original obstacles
        if (original[r][c] == '.') garbageTotal++;   // total original garbage
        if (original[r][c] == '*' && grid[r][c] != '*') obstaclesMissing++; // someone removed an obstacle - that's bad
      }
    }

    int garbageSweptUp = (garbageTotal - garbageMissed); 

    int score = numrows*numcols - garbageMissed - obstaclesMissing; // reduce score from total possible by garbage that was not picked up and obstacles that were removed
    score = (100*score)/(numrows*numcols); // normalized based on total possible squares in grid

    cout << "SCORE:" << endl;
    cout << "----------------------" << endl;
    cout << "Total squares in grid = " << numrows*numcols << endl;
    cout << "Garbage total (original): " << garbageTotal << endl;
    cout << "Obstacles total (original): " << obstaclesTotal << endl;
    cout << "Garbage swept up: " << garbageSweptUp << endl;
    cout << "Garbage Missed = " << garbageMissed << " (minus " << garbageMissed << " points)" << endl;
    cout << "Obstacles Missing = " << obstaclesMissing << " out of " << obstaclesTotal << " (minus " << obstaclesMissing << " points)"<< endl;
    cout << "Total Moves taken = " << totalMoves << endl;
    if (totalMoves > 0)
      cout << "Cleaning efficiency = garbage swept up/totalMoves = %" << ((100*garbageSweptUp)/totalMoves) << endl;
    cout << "Final normalized score out of 100 possible = " << score << endl;
    
    if (score > 90) cout << "Well done!" << endl;
    else if (score > 80) cout << "Not bad - your robot is a bit sloppy though" << endl;
    else if (score > 70) cout << "So So - your robot might need a tune up" << endl;
    else if (score > 60) cout << "Not so great - your robot seems to be having a bad day" << endl;
    else  cout << "Hmmm - might want to call in some iRobot back-up for help.  Let me know if you have questions!" << endl;
  }


  //
// SWEEP GRID TODO - you need to write this function so that it cleans grid[][] without sweeping up obstacles
//explain the goal of each loop and function call
//all function arguments and return values documented
//all transient variables and data structures created locally inside functions documented

constexpr int flatten_grid(const int row, const int col) //passes in the rows and columns of the 2d array to simulate a 1d array to simplify code
{
    return row * numrows + col;
}

array<vector<int>, numrows * numcols> create_adj_matrix() //returns an adjacency list -- an array of vectors of a size of 400 (rows*columns) to store each adjacency in the graph
{
    array<vector<int>, numrows * numcols> adj; //default initializing the adjacency list named adj
    for (int i = 0; i < numrows; i++)
    {
        for (int j = 0; j < numcols; j++)
        {
            const int cell = flatten_grid(i, j); //calls flatten_grid and passes in number of rows and number of columns to store each position in the grid

            vector<pair<int, int>> arr = { //creates a vector of a pair of integers. the pairs are offsets of each direction around the vacuum; up, diagonally-right, diagonally-left, diagonally-bottom-left, left, down, diagonally-bottom-right, right
                {0, 1},
                {1, 1},
                {-1, 1},
                {-1, -1},
                {-1, 0},
                {0, -1},
                {1, -1},
                {1, 0},
            };

            for (auto &off : arr) //for each offset in arr
            {
                int newI = i + off.first; //get new row
                int newJ = j + off.second; //get new col

                if (0 <= newI && newI < numrows && 0 <= newJ && newJ < numcols) //check if inside bounds
                {
                    if (grid[newI][newJ] == '.') //check if it's garbage
                    {
                        adj[cell].push_back(flatten_grid(newI, newJ)); //if so then add it to the adjacency list
                    }
                }
            }
        }
    }
    return adj; //returns the created adjacency list 
}

vector<int> shortest_path(array<vector<int>, numrows * numcols> const &adj, const int i, const int j, const int toI, const int toJ) //This is almost 1:1 generic bfs code, just adding support for the returning path. Finds the shortest path between two positions in a grid. returns a vector containing the flattened cell positions between the two positions. The parameters are (adjacency list, starting row, starting column, destination row, destination column).
{
    array<bool, numrows * numcols> visited; //creates an array named visited of booleans of size 400 to document if it has been visited
    for (auto &node : visited) //for each node in the visited array, set it to false 
        node = false;

    queue<pair<int, vector<int>>> q; //create a queue for bfs
    int cell = flatten_grid(i, j); //again, flatten each position in the grid and call it cell
    q.push({cell, {}}); //push a pair, with the int being cell and the second being an empty vector (for the path)
    visited[cell] = true; 

    while (!q.empty()) //while there are still cells in our queue left to search 
    {
        auto front = q.front(); //get the front
        q.pop(); //pop it off

        int node = front.first; //get the node of the front
        vector<int> path = front.second; //save the path to the current point
        // Get all adjacent vertices of the dequeued
        for (int i = 0; i < adj[node].size(); i++)
        {
            if (!visited[adj[node][i]]) //If a adjacent has not been visited, then mark it visited and enqueue it
            {
                visited[adj[node][i]] = true; 
                vector<int> newPath = path; //the path to the new node
                newPath.push_back(adj[node][i]); //push the new path
                q.push({adj[node][i], newPath}); //enqueue the newpath and the adjacenct
                int row = adj[node][i] / numrows; 
                int col = adj[node][i] % numrows; 
                if (row == toI && col == toJ) //once we get there, return the path
                    return newPath;
            }
        }
    }
    return {}; //if there aren't, return nothing
}

int get_dots() //this counts the number of dots (garbage)
{
    int dots = 0; //intialize dots to 0
    for (int i = 0; i < numrows; i++) //iterate through an count the dots
        for (int j = 0; j < numcols; j++)
            if (grid[i][j] == '.')
                dots++;
    return dots; //returns the number of dots
}

void sweepGrid()
{
    auto adj = create_adj_matrix(); //make our adjacency list

    while (get_dots()) //while there are still dots to sweep, sweep them
    {
        int min = 9999999; //min is to keep track of the shortest path we found so far
        vector<int> minPath; //shortest path
        bool all_empty = true; //
        // Ran out of garbage, find the closest to us
        for (int i = 0; i < numrows; i++) //iterate through to find the next garbage
        {
            for (int j = 0; j < numcols; j++)
            {
                if (grid[i][j] == '.')
                {
                    vector<int> path = shortest_path(adj, getRow(), getCol(), i, j); //store our shortest path to the garbage
                    if (path.size() < min && !path.empty()) //if the path is shorter than the previous path found and the path isn't empty
                    {
                        min = path.size(); //update min
                        minPath = path; //store our new shortest path
                        all_empty = false; 
                        if (min == 1) 
                        {
                            goto found_min;
                        }
                    }
                }
            }
        }
    found_min:
        if (all_empty) //check if there is any garbage left that we can get a path to
            break;
        for (auto &x : minPath) //go to the garbage via the path we found
        {
            moveTo(x / numrows, x % numcols);
        }
    }
}
int main() {
  std::cout << "HW5 ALT - Robot Vacuum (starter) \n";

  initGrid();   // init the grid with garbage and obstacles
  cout << "Dirty Room before sweeping: " << endl;
  printGrid();

  sweepGrid();  // TODO Your routine!

  cout << "Clean Room after sweeping: " << endl;
  printGrid();

  printScore(); // your score
 
}
