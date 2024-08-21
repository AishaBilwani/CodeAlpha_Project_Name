#include <iostream>
#include <vector>

using namespace std;

const int N = 9; // Sudoku grid size

// Function to print the Sudoku board
void printBoard(const vector<vector<int> >& board) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to check if placing num in board[row][col] is valid
bool isValid(const vector<vector<int> >& board, int row, int col, int num) {
    // Check if num is not in the current row
    for (int x = 0; x < N; ++x) {
        if (board[row][x] == num) return false;
    }

    // Check if num is not in the current column
    for (int x = 0; x < N; ++x) {
        if (board[x][col] == num) return false;
    }

    // Check if num is not in the current 3x3 grid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i + startRow][j + startCol] == num) return false;
        }
    }

    return true;
}

// Backtracking function to solve the Sudoku
bool solveSudoku(vector<vector<int> >& board) {
    int row, col;
    bool empty = false;

    // Find an empty cell in the board
    for (row = 0; row < N; ++row) {
        for (col = 0; col < N; ++col) {
            if (board[row][col] == 0) {
                empty = true;
                break;
            }
        }
        if (empty) break;
    }

    // If there is no empty cell, the Sudoku is solved
    if (!empty) return true;

    // Try placing numbers 1 to 9 in the empty cell
    for (int num = 1; num <= N; ++num) {
        if (isValid(board, row, col, num)) {
            board[row][col] = num;
            if (solveSudoku(board)) return true;
            board[row][col] = 0; // Backtrack
        }
    }

    return false; // Trigger backtracking
}

// Function to initialize the board
void initializeBoard(vector<vector<int> >& board) {
    int initialBoard[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            board[i][j] = initialBoard[i][j];
        }
    }
}

int main() {
    // Create a 9x9 Sudoku board with all cells initialized to 0
    vector<vector<int> > board(N, vector<int>(N, 0));

    // Initialize the board with a sample Sudoku puzzle
    initializeBoard(board);

    cout << "Original Sudoku Board:" << endl;
    printBoard(board);

    if (solveSudoku(board)) {
        cout << "\nSolved Sudoku Board:" << endl;
        printBoard(board);
    } else {
        cout << "No solution exists!" << endl;
    }

    return 0;
}

