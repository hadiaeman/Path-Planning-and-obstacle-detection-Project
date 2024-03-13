#include <iostream>
#include <queue>
#include <limits>
#include <cmath>

using namespace std;

const int ROWS = 8;
const int COLS = 10;

// Structure to represent a grid cell

struct Cell {
    int row, col;
    int distance;
    Cell* parent;

    Cell(int r, int c)
        : row(r), col(c), distance(numeric_limits<int>::max()), parent(NULL) {}
};


// Function to check if a cell is valid or not

bool isValid(int row, int col) {
    return (row >= 0) && (row < ROWS) && (col >= 0) && (col < COLS);
}

// Function to calculate the distance between two cells

int calculateDistance(int row1, int col1, int row2, int col2) {
    return abs(row2 - row1) + abs(col2 - col1);
}


// Function to reconstruct the path from destination to source

void reconstructPath(Cell* dest, int grid[ROWS][COLS]) {
    cout << "Path: ";
    Cell* current = dest;

    while (current != NULL) {
        grid[current->row][current->col] = 2;
        current = current->parent;
    }
}


// Dijkstra's algorithm to find the shortest path

struct CompareCells {
    bool operator()(const Cell* c1, const Cell* c2) {
        return c1->distance > c2->distance;
    }
};

void findPath(int grid[ROWS][COLS], int srcRow, int srcCol, int destRow, int destCol) {
    if (!isValid(srcRow, srcCol) || !isValid(destRow, destCol)) {
        cout << "Invalid source or destination!" << endl;
        return;
    }

    bool visited[ROWS][COLS];
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            visited[i][j] = false;
        }
    }

    priority_queue<Cell*, vector<Cell*>, CompareCells> openList;

    Cell* source = new Cell(srcRow, srcCol);
    source->distance = 0;
    openList.push(source);

    while (!openList.empty()) {
        Cell* current = openList.top();
        openList.pop();

        int row = current->row;
        int col = current->col;

        visited[row][col] = true;

        // Destination reached
        if (row == destRow && col == destCol) {
            reconstructPath(current, grid);
            return;
        }

        // Generate neighboring cells
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; ++i) {
            int newRow = row + dx[i];
            int newCol = col + dy[i];

            if (isValid(newRow, newCol) && !visited[newRow][newCol] && grid[newRow][newCol] != 1) {
                int distance = current->distance + calculateDistance(row, col, newRow, newCol);

                if (distance < numeric_limits<int>::max()) {
                    grid[newRow][newCol] = distance;

                    Cell* neighbor = new Cell(newRow, newCol);
                    neighbor->distance = distance;
                    neighbor->parent = current;

                    openList.push(neighbor);
                }
            }
        }
    }

    cout << "Path not found!" << endl;
}

int main() {
    int grid[ROWS][COLS] = {
        {0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 0, 1, 1, 0, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 1, 0, 0}
    };

    cout << "Obstacle Detection Environment:" << endl;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (grid[i][j] == 1) {
                cout << "X ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }

    int srcRow, srcCol, destRow, destCol;
    cout << "Enter source coordinates (row col): ";
    cin >> srcRow >> srcCol;
    cout << "Enter destination coordinates (row col): ";
    cin >> destRow >> destCol;

    findPath(grid, srcRow, srcCol, destRow, destCol);

    cout << "Grid with Path:" << endl;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (grid[i][j] == 1) {
                cout << "X ";
            } else if (grid[i][j] == 2) {
                cout << "P ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }

    return 0;
}

