/***************************************************************************************
 *
 * Author : Brian Graham
 * Date: 11.18.14
 * CS 165
 * gameOfLife.cpp - Conway's Game of Life using a 80 x 22 grid, gives the user 3 options
 * to start with. Goes through 32 generations then lets user choose again.
 ****************************************************************************************/


#include <iostream>
#include <cstdlib>
using std::cout;

const int WIDTH = 22;
const int LENGTH = 80;
void runProgram(); // runs the whole program

//these are the options for starting points:
void setupSquareArray(char array[][LENGTH]); // setup square starting point
void setupArray(char array[][LENGTH]); // sets up single line position
void setupGliderArray(char array[][LENGTH]); // glider setup
//next ones modify the arrays
void updateArray(char array[][LENGTH]); // update new generation
void checkGrid(char array[][LENGTH], char newArray[][LENGTH]); // loop that goes through entire grid
void checkNeighbors(char board[][LENGTH], char updatedArray[][LENGTH], int x, int y);//checkNeighbors checks current cell for neighbors, updates next gen
void aliveOrDead(int x, int y, bool& lifeCheck, char array[][LENGTH]); // changes new array based on old one
void copyArray(char board[][LENGTH], char updatedArray[][LENGTH]); // copys old array into new one to be updated

//these are used to help check neighbors of cells
bool checkCell(int x, int y, char oldArray[][LENGTH]);
int returnCounter(int& counter, int x, int y, char board[][LENGTH]);// checks cell neighbors, returns how many are alive

int main(int argc, const char * argv[])
{
    runProgram();
    return 0;
}

void runProgram()
{
    char board[WIDTH][LENGTH]; // init two arrays, board is original, newBoard is nextgen
    char newBoard[WIDTH][LENGTH];
    int i = 0;
    int genCount = 0; // counts # of generations that have past
    std::string bye = ""; // exit protocol
    bool setupAreaYet = false;
    bool isArrayCopied = false;
    while (bye != "-1")
    {
        if (setupAreaYet == false) // if user has not selected an option yet, go here
        {
            cout << "\n1) Single Line Starting Point\n\n2) The Glider\n\n3) Square\n\nPlease enter an option (1-3):\n";
            int option;
            std::cin >> option;
            if (option == 1) setupArray(board);
            if (option == 2)setupGliderArray(board);
            if (option == 3) setupSquareArray(board);
            setupAreaYet = true;
        }
        if (isArrayCopied == false)
        {
            copyArray(board, newBoard); // copy the initial board into the nextgen board
            isArrayCopied = true;
        }
        checkGrid(board, newBoard); // check cells in grid
        updateArray(newBoard); // show the new generation
        copyArray(newBoard, board); // copy newBoard into board
        ++i;
        system("sleep .11");
        if (i % 80 == 2)
        {
            cout << "\n\n" << i << " generations have past.. Would you like to continue? Press -1 to exit, 0 for the menu, anything else to continue:\n";
            std::getline(std::cin, bye);
            if (bye == "0")
            {
                isArrayCopied = false;
                genCount += i;
                i = 0;
                setupAreaYet =false;
                bye = "";
            }
        }
    }
    cout << "User Exited. Goodbye.\n";
}

void setupSquareArray(char array[][LENGTH]) // intial setup is similar to a square
{
    cout << "\n\n";
    for (int i = 0;i < WIDTH; ++i)
    {
        for (int j =0; j < LENGTH; ++j)
        {
            if (i == 15 && ((j > 9 && j < 13) || j == 14))array[i][j] = 'O';
            
            else if (i == 16 && j == 10)array[i][j] = 'O';
            
            else if (i == 17 && j > 12 && j < 15)array[i][j] = 'O';
            
            else if (i == 18 && ((j > 10 && j < 13) || j == 14))array[i][j] = 'O';
            
            else if (i == 19 && (j == 10 || j == 12 || j == 14))array[i][j] = 'O';
            
            else array[i][j] = '-';
            cout << array[i][j];
        }
        cout << "\n";
    }
}
// SETUP SINGLE LINE STARTING POSITION (These are based off of the three most productive patterns on wikipedia)s
void setupArray(char array[][LENGTH])
{
    cout << "\n\n";
    for (int i = 0;i < WIDTH; ++i)
    {
        for (int j =0; j < LENGTH; ++j)
        {
            if ((i == 1) && (j != 0) && (j < 10))array[i][j] = 'O';
        
            else if (i == 1 && j > 10 && j < 16)array[i][j] = 'O';
            
            else if (i == 1 && j > 18 && j < WIDTH)array[i][j] = 'O';
            
            else if (i == 1 && j > 27 && j < 35)array[i][j] = 'O';
            
            else if (i == 1 && j > 35 && j < 41)array[i][j] = 'O';
            
            else array[i][j] = '-';
            cout << array[i][j];
        }
        cout << "\n";
    }
}

// SETUP GLIDER STARTING PATTERN
void setupGliderArray(char array[][LENGTH]) 
{
    cout << "\n\n";
    for (int i = 0;i < WIDTH; ++i)
    {
        for (int j =0; j < LENGTH; ++j)
        {
            if (i == 1 && j == 25) array[i][j] = 'O';
            else if (i == 2 && (j == 25 || j == 23)) array[i][j] = 'O';
            else if (i == 3 && (j == 13 || j == 14 || j == 21 || j == WIDTH || j == 35 || j == 36))array[i][j] = 'O';
            else if (i == 4 && (j== 16 || j== 12 || (j > 20 && j < 23) || (j > 34 && j < 37)))array[i][j] = 'O';
            else if (i == 5 && (j == 1 || j == 2 || j == 21 || j == WIDTH ||j == 11 || j == 17))array[i][j] = 'O';
            else if (i == 6 && (j == 1 || j == 2 || j == 11 || j == 23 || j == 25 || j == 17 || j == 18|| j == 15))array[i][j] = 'O';
            else if (i == 7 && (j == 11 || j == 17 || j == 25))array[i][j] = 'O';
            else if (i == 8 && (j == 12 || j == 16))array[i][j] = 'O';
            else if (i == 9 && (j == 13 || j == 14))array[i][j] = 'O';
            else array[i][j] = '-';
            cout << array[i][j];
        }
        cout << "\n";
    }
}

// SHOW NEWEST GENERATION
void updateArray(char array[][LENGTH])
{
    cout << "\n\n";
    for (int i = 0;i < WIDTH; i++)
    {
        for (int j =0; j < LENGTH; j++)
        {
            cout << array[i][j];
        }
        cout << "\n";
    }
}

// CHECK GRID FOR NEXT GENERATION
void checkGrid(char array[][LENGTH], char newArray[][LENGTH])
{
    for (int i = 0;i < WIDTH; i++)
    {
        for (int j =0; j < LENGTH; j++)
        {
            checkNeighbors(array, newArray, i, j);
        }
    }
}

// USED IN CHECK GRID TO CHECK EACH CELLS NEIGHBORS
void checkNeighbors(char board[][LENGTH], char updatedArray[][LENGTH], int x, int y)
{
    bool isItAlive = false;
    int counter = 0;
    counter = returnCounter(counter, x, y, board);

    if (counter > 3 || counter < 2)
    {
        // cell dies, change to - in new array
        isItAlive = false;
        aliveOrDead(x, y, isItAlive, updatedArray);
    }
    if ((counter == 3 && board[x][y] == '-') || ((counter == 2 || counter == 3) && board[x][y] == 'O'))
    {
        // dead cell is now alive, add to new array or cell lives cuz it has 2 or 3 neighbors
        isItAlive = true;
        aliveOrDead(x, y, isItAlive, updatedArray);
    }
}

// USED IN CHECKNEIGHBORS TO UPDATE THE CELL FOR THE NEW GEN
void aliveOrDead(int x, int y, bool& lifeCheck, char array[][LENGTH])
{
    if (lifeCheck == true)
    {
        // make x,y in new array an alive cell
        array[x][y] = 'O';
    }
    else
    {
        // make x,y a dead cell in new array
        array[x][y] = '-';
    }
}

// COPYS OLD ARRAY TO THE NEW ONE TO BE MODIFIED
void copyArray(char board[][LENGTH], char updatedArray[][LENGTH])
{
    for (int i = 0; i < WIDTH; ++i)
    {
        for (int j = 0; j < LENGTH; ++j)
        {
            updatedArray[i][j] = board[i][j];
        }
    }
}

// USED TO ALLOW WRAPPING OF INTEGERS, WORKS FOR ALL INTS IN GRID
bool checkCell(int x, int y, char oldArray[][LENGTH])
{
    bool result = false;
    x %= WIDTH;
    y %= LENGTH;
    x += (x < 0) ? WIDTH : 0;
    y += (y < 0) ? LENGTH : 0;
    if (oldArray[x][y] == 'O') result = true;
    return result;
}
// Checks cells neighbors to see if they are alive, if so, add to the counter and return when done
int returnCounter(int& counter, int x, int y, char board[][LENGTH])
{
    if (checkCell((x - 1), y, board)) counter++; // checks above cell
    if (checkCell((x + 1), (y - 1), board)) counter++; // checks left bottom corner cell
    if (checkCell((x - 1), (y - 1), board)) counter++; // checks upper left corner
    if (checkCell((x - 1), (y+1), board)) counter++; // checks upper right corner
    if (checkCell((x + 1), (y + 1), board)) counter++; // checks bottom right corner
    if (checkCell(x, (y - 1), board)) counter++; // checks left cell
    if (checkCell(x, (y+1), board)) counter++; // checks right cell
    if (checkCell((x + 1), y, board)) counter++; // checks below cell
    return counter;
}
