#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

#define N 4

using namespace std ;

int maxFlags = 0; // To store the maximum number of flags placed

// Function to check if the current position is safe for placing a flag
bool isSafe(int row, int col, bool cols[], bool mainDiags[], bool antiDiags[]) {
    int mainDiagIdx = row - col + (N - 1);
    int antiDiagIdx = row + col;

    return !cols[col] && !mainDiags[mainDiagIdx] && !antiDiags[antiDiagIdx];
}

// Backtracking function to place flags
void placeFlags(int row, bool cols[], bool mainDiags[], bool antiDiags[], int count) {
    // If all rows are processed, update the maximum flags
    if (row == N) {
        maxFlags = max(maxFlags, count);
        return;
    }

    // Try placing a flag in each column of the current row
    for (int col = 0; col < N; col++) {
        if (isSafe(row, col, cols, mainDiags, antiDiags)) {
            // Mark the current position as occupied
            cols[col] = true;
            mainDiags[row - col + (N - 1)] = true;
            antiDiags[row + col] = true;

            // Recur to place flags in the next row
            placeFlags(row + 1, cols, mainDiags, antiDiags, count + 1);

            // Backtrack and unmark the current position
            cols[col] = false;
            mainDiags[row - col + (N - 1)] = false;
            antiDiags[row + col] = false;
        }
    }

    // Also consider the possibility of not placing a flag in this row
    placeFlags(row + 1, cols, mainDiags, antiDiags, count);
}

int main() {
    // Create arrays to track columns and diagonals
    bool cols[N] = {false};               // Tracks columns
    bool mainDiags[2 * N - 1] = {false}; // Tracks main diagonals
    bool antiDiags[2 * N - 1] = {false}; // Tracks anti-diagonals

    // Start placing flags from the first row
    placeFlags(0, cols, mainDiags, antiDiags, 0);

    // Output the maximum number of flags that can be placed
    cout << "Maximum number of flags that can be placed: " << maxFlags << endl;

    return 0;
}