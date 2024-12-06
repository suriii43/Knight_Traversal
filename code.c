#include <stdio.h>
#include <stdbool.h>

// Define the size of the chessboard
#define N 8

// Define the movements of the knight
int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

// Function to check if the move is valid
bool isValid(int x, int y, int board[N][N]) {
    return (x >= 0 && y >= 0 && x < N && y < N && board[x][y] == -1);
}

// Function to print the path of the knight in coordinates
void printPath(int board[N][N]) {
    int path[N * N][2];
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            path[board[x][y]][0] = x;
            path[board[x][y]][1] = y;
        }
    }
    for (int i = 0; i < N * N; i++) {
        printf("(%d, %d)\n", path[i][0], path[i][1]);
    }
}

// Function to count the number of valid moves
int countValidMoves(int x, int y, int board[N][N]) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        int next_x = x + dx[i];
        int next_y = y + dy[i];
        if (isValid(next_x, next_y, board)) {
            count++;
        }
    }
    return count;
}

// Function to solve the Knight's Tour problem using Warnsdorff's rule
bool solveKnightTour(int x, int y, int movei, int board[N][N]) {
    int next_x, next_y;
    if (movei == N * N) {
        return true;
    }

    // Array to store the number of valid moves for each move
    int validMoves[8];
    for (int i = 0; i < 8; i++) {
        next_x = x + dx[i];
        next_y = y + dy[i];
        if (isValid(next_x, next_y, board)) {
            validMoves[i] = countValidMoves(next_x, next_y, board);
        } else {
            validMoves[i] = -1;
        }
    }

    // Sort the moves based on the number of valid moves (Warnsdorff's rule)
    for (int i = 0; i < 8 - 1; i++) {
        for (int j = i + 1; j < 8; j++) {
            if (validMoves[i] > validMoves[j]) {
                int temp = validMoves[i];
                validMoves[i] = validMoves[j];
                validMoves[j] = temp;

                int temp_dx = dx[i];
                dx[i] = dx[j];
                dx[j] = temp_dx;

                int temp_dy = dy[i];
                dy[i] = dy[j];
                dy[j] = temp_dy;
            }
        }
    }

    // Try all next moves from the current coordinate x, y
    for (int k = 0; k < 8; k++) {
        next_x = x + dx[k];
        next_y = y + dy[k];
        if (isValid(next_x, next_y, board)) {
            board[next_x][next_y] = movei;
            if (solveKnightTour(next_x, next_y, movei + 1, board)) {
                return true;
            } else {
                board[next_x][next_y] = -1; // Backtracking
            }
        }
    }
    return false;
}

// Function to initialize the Knight's Tour problem
bool startKnightTour(int startX, int startY) {
    int board[N][N];

    // Initialize the chessboard
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            board[x][y] = -1;
        }
    }

    // Starting position of the knight
    board[startX][startY] = 0;

    // Start solving the problem
    if (solveKnightTour(startX, startY, 1, board)) {
        printPath(board);
        return true;
    } else {
        printf("Solution does not exist\n");
        return false;
    }
}

int main() {
    int startX, startY;

    // Get the starting position from the user
    printf("Enter the starting X coordinate (0-7): ");
    scanf("%d", &startX);
    printf("Enter the starting Y coordinate (0-7): ");
    scanf("%d", &startY);

    // Validate the input
    if (startX < 0 || startX >= N || startY < 0 || startY >= N) {
        printf("Invalid starting position. Please enter values between 0 and 7.\n");
        return -1;
    }

    startKnightTour(startX, startY);
    return 0;
}