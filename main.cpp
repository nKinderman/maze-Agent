/* Maze Agent Program
 *
 * File:   main.cpp
 * Author: Nick Kinderman
 * Created on September 12, 2017, 3:29 PM
 *
 * Description: My task was to create an agent that can process a maze.
 *   The following instructions were given: The maze will be a 10 x 10 grid.
 *   The grid will have a point of entry in the ‘0’ column (left wall) and a
 *   point of exit somewhere along the other three walls. The Entry will be
 *   designated with an ‘E’, and the exit will be designated with an ‘X’. The
 *   path that can be traveled in the maze will be designated with a ‘P’, and
 *   the walls will be designated with a ‘W’. All perimeter locations other
 *   than the entrance and exit will be a ‘W’. The locations in the grid will
 *   be identified top left to bottom right, using the row column number. Top
 *   left is 00, then 01, then 02, etc. Bottom line ends with 97, 98, 99. The
 *   data file will have one letter on each line. It will be named maze.txt.
 *   I will read the file into a 2D array as represented above to create the
 *   maze. My agent must traverse the left wall to find the Entry point and
 *   then must traverse the maze, following the path to the exit. I will use
 *   the Breadth First (queue), and Depth First (stack) methods. I will
 *   display the maze on the console, and the results of both traversals.
 *   My output will be presentable. I will include the row and column numbers,
 *   and appropriate spacing, so the reader can see what is taking place.
 *   I will label each traversal according to the type of search.
 *
 *   I decided early on that I did not want to utilize x and y type coordinates
 *   of a 2D array in my DFS and BFS functions. Instead, I used a simple 1D
 *   array to simplify the logic process for myself.  The queue, stack, and list
 *   libraries in the STL were a much welcomed addition to this program.
 * 
 *   I got some direction from a GeeksforGeeks maze article:
 *   http://www.geeksforgeeks.org/shortest-path-in-a-binary-maze/
 */

#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <string.h>
#include <list>

using namespace std;

//------------------ Globals Declarations/Definitions ------------------------//

#define SIZE 100  // element size of a 10 x 10 array
#define ROW 10  // row size
#define COL 10  // column size

// Object containing node location, data value, steps, and path(linked list)
struct Node{
    int location; // location in maze
    char data; // location data value
    int steps; // distance from source node
    list<int> path; // saved path in a linked list
};

char maze1D[SIZE];  // 1D maze array
char maze2D[ROW][COL];  // 2D maze array

// Array to used designate search pattern (clockwise from midnight)
int pattern[] = {-ROW, 1, ROW, -1};

//------------------------- Function Declarations ----------------------------//

// find entrance on left wall of maze
int source(char maze1D[]);

// populate 2D array with maze data from 1D array
void populate(char maze1D[SIZE], char maze2D[ROW][COL]);

// print 2D array (maze) w/ row/col numbers
void printMaze(char maze2D[ROW][COL]);

// Checks for valid location in the mazes range
bool isRangeValid(int location);

// Checks for valid data in the maze path (E = entry, P = path, X = exit)
bool isDataValid(char data);

// Breadth-first search function to find a path through the maze
void BFS(char maze[], int src);

// Depth-first search function to find a path through the maze
void DFS(char maze[SIZE], int src);

//----------------------------- Program Main ---------------------------------//

int main() {

    string line;  // ifstream line by line variable
    int count = 0;  // counting variable

    // buffer text file
    ifstream file;
    file.open("maze.txt");

    if(!file){
        cout << "There is no input text file with the name, maze.txt.";
    }
    else{
        // extract line by line and populate 1D array
        while(getline(file,line)){
            char c = line[0];
            maze1D[count] = c;
            count++;
        }

        file.close();

        int src = source(maze1D); // declare and set entry point

        populate(maze1D, maze2D);

        printMaze(maze2D);

        BFS(maze1D, src);

        DFS(maze1D, src);
    }

    return 0;
}

//------------------------- Function Definitions -----------------------------//

int source(char maze1D[SIZE]){
    int src;
    // search from 0 - 90, incrementing by 10
    for(int i = 0; i < SIZE; i += 10){
        if(maze1D[i] == 'E'){
            src = i;
        }
    }
    return src;
}

void populate(char maze1D[SIZE], char maze2D[ROW][COL]){
    int count = 0;
    for(int i = 0; i < ROW; i++){
            for(int j = 0; j < COL; j++){
                maze2D[i][j] = maze1D[count];
                count++;
            }
        }
}

void printMaze(char maze2D[ROW][COL]){
    cout << "The Maze" << endl;
        cout << "\t";
        for(int i = 0; i < 10; i++){
            cout << i << "\t";
        }
        cout << endl;
        for(int i = 0; i < 10; i++){
            cout << i << "\t";
            for(int j = 0; j < 10; j++){
                cout << maze2D[i][j] << "\t";
            }
            cout << endl;
        }
        cout << endl;
}

bool isRangeValid(int location){
    if((location >= 0) && (location < SIZE)){
        return true;
    }
    else{
        return false;
    }
}

bool isDataValid(char data){
    if ((data == 'E') || (data == 'P') || (data == 'X')){
        return true;
    }
    else{
        return false;
    }
}

void BFS(char maze[SIZE], int src){

    bool visited[SIZE]; // array to store visited status
    memset(visited, false, sizeof visited); // set array elements to false

    visited[src] = true;  // mark maze entrance as visited

    queue<Node> n;  // create a queue of Nodes for the search

    Node e;  // create entrance node;
    e.location = src;
    e.data = 'E';  // "E" is hard coded since "src" was found in source()
    e.steps = 0;  // initialize step count
    e.path.push_back(src);  // insert path into list

    n.push(e); // enqueue entrance node

    int locationHolder;  // while loop location variable
    list<int>::iterator it;  // for loop list iterator

    // loop until queue is empty
    while(!n.empty()){
        int counts = 0;
        counts++;
        Node curr = n.front();  // current node equals front of queue
        locationHolder = curr.location;  // temp variable for current location
        char data = curr.data;  // temp variable for data
        cout << counts << ": " << locationHolder << endl;


        // If exit ("X") is reached, print the path and break the loop
        if(data == 'X'){
            cout << "Breadth-First Search (BFS)" << endl;
            cout << "The step count via BFS is: " <<curr.steps;
            cout << endl << "The path via BFS is: ";
            for (it = curr.path.begin(); it != curr.path.end(); ++it){
                cout << ' ' << *it;
            }
            cout << endl;
            break;
        }

        n.pop();  // Else, dequeue the the front node and start the search pattern

        // loop through search path
        for(int i = 0; i < 4; i++){
            int location = locationHolder;  // temp location variable

            // check for left wall of 1D maze
            if((location == 0 || location == 10 || location == 20 ||
                location == 30 || location == 40 || location == 50 ||
                location == 60 || location == 70 || location == 80
                || location == 90) && pattern[i] == -1){
                // do nothing
            }
            // check for right wall of 1D maze
            else if((location == 9 || location == 19 || location == 29
                || location == 39 || location == 49 || location == 59
                || location == 69 || location == 79 || location == 89
                || location == 99) && pattern[i] == 1){
                // do nothing
            }
            else{
                location += pattern[i]; // define new temp location
                char data = maze[location]; // declare/define new temp data

                // is location in the maze - is location char valid - has location been visited
                if((isRangeValid(location)) && (isDataValid(data)) && (!visited[location])){

                    visited[location] = true; // set location to visited

                    Node neighbor;  // create neighbor node
                    neighbor.location = location;  // set location
                    neighbor.data = data;  // set data
                    neighbor.steps = curr.steps + 1; // increment steps
                    neighbor.path = curr.path; // copy list
                    neighbor.path.push_back(location); // insert path into list
                    n.push(neighbor);  // enqueue neighbor node
                }
            }
        }
    }
    cout << endl;
}

void DFS(char maze[SIZE], int src){

    bool visited[SIZE]; // array to store visited status
    memset(visited, false, sizeof visited); // set all elements to false

    visited[src] = true;  // mark maze entrance as visited

    stack<Node> n;  // create a stack of Nodes for the search

    Node e;  // create first node
    e.location = src;
    e.data = 'E'; // "E" is hard coded since "src" was found in source()
    e.steps = 0;  // initialize step count
    e.path.push_back(src);  // insert path into list

    n.push(e);  // push entrance node

    int locationHolder;  // while loop temp location variable
    list<int>::iterator it;  // for loop list iterator

    // while the stack is not empty
    while(!n.empty()){
        Node curr = n.top();  // current node equals the top of the stack
        locationHolder = curr.location;  // temp variable for current location
        char data = curr.data;  // temp variable for data

        // If exit ("X") is reached, print the path and break the loop
        if(data == 'X'){
            cout << "Depth-First Search (DFS)" << endl;
            cout << "The step count via DFS is: " <<curr.steps;
            cout << endl << "The path via DFS is: ";
            for (it = curr.path.begin(); it != curr.path.end(); ++it){
                cout << ' ' << *it;
            }
            cout << endl;
            break;
        }

        n.pop();  // Else pop the the top and start the search pattern

        for(int i = 0; i < 4; i++){
            int location = locationHolder;  // for loop temp location variable

            // check for left wall of 1D maze
            if((location == 0 || location == 10 || location == 20 ||
                location == 30 || location == 40 || location == 50 ||
                location == 60 || location == 70 || location == 80
                || location == 90) && pattern[i] == -1){
                // do nothing
            }
            // check for right wall of 1D maze
            else if((location == 9 || location == 19 || location == 29
                || location == 39 || location == 49 || location == 59
                || location == 69 || location == 79 || location == 89
                || location == 99) && pattern[i] == 1){
                // do nothing
            }
            else{
                location += pattern[i];  // define new temp location
                data = maze[location]; // define new temp data

                // is location in the maze - is location char valid - location not been visited
                if((isRangeValid(location)) && (isDataValid(data)) && (!visited[location])){
                    visited[location] = true; // set location to visited

                    Node neighbor;  // create neighbor node
                    neighbor.location = location;  // set location
                    neighbor.data = data;  // set data
                    neighbor.steps = curr.steps + 1;  // increment steps
                    neighbor.path = curr.path;  // copy list
                    neighbor.path.push_back(location);  // insert path into list
                    n.push(neighbor);  // push neighbor node
                }
            }
        }
    }
}
