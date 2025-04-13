// Copyright 2024 Kita Trofimov
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../lib_parser/parser.h"

int Maze::toIndex(int x, int y) const {
    return x * cols + y;
}

void Maze::shuffle(int* array, int n) {
    for (int i = n - 1; i > 0; --i) {
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

Maze::Maze(int r, int c) : rows(r), cols(c), dsu(r* c) {
    walls_h = new int* [rows - 1];
    for (int i = 0; i < rows - 1; ++i) {
        walls_h[i] = new int[cols];
        for (int j = 0; j < cols; ++j) {
            walls_h[i][j] = 1;
        }
    }

    walls_v = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        walls_v[i] = new int[cols - 1];
        for (int j = 0; j < cols - 1; ++j) {
            walls_v[i][j] = 1;
        }
    }

    generateMaze();
}

Maze::~Maze() {
    for (int i = 0; i < rows - 1; ++i) delete[] walls_h[i];
    for (int i = 0; i < rows; ++i) delete[] walls_v[i];
    delete[] walls_h;
    delete[] walls_v;
}

void Maze::generateMaze() {
    srand(time(0));

    int h_walls = (rows - 1) * cols;
    int v_walls = rows * (cols - 1);
    int total_walls = h_walls + v_walls;
    int* walls = new int[total_walls];

    for (int i = 0; i < h_walls; ++i) {
        walls[i] = i;
    }
    for (int i = 0; i < v_walls; ++i) {
        walls[h_walls + i] = 100000 + i;
    }

    shuffle(walls, total_walls);

    for (int i = 0; i < total_walls; ++i) {
        if (walls[i] < 100000) {
            int idx = walls[i];
            int x = idx / cols;
            int y = idx % cols;
            int cell1 = toIndex(x, y);
            int cell2 = toIndex(x + 1, y);

            if (dsu.find(cell1) != dsu.find(cell2)) {
                dsu.Union(cell1, cell2);
                walls_h[x][y] = 0;
            }
        } else {
            int idx = walls[i] - 100000;
            int x = idx / (cols - 1);
            int y = idx % (cols - 1);
            int cell1 = toIndex(x, y);
            int cell2 = toIndex(x, y + 1);

            if (dsu.find(cell1) != dsu.find(cell2)) {
                dsu.Union(cell1, cell2);
                walls_v[x][y] = 0;
            }
        }
    }

    delete[] walls;
}

void Maze::printMaze() const {
    for (int j = 0; j < cols; ++j) {
        std::cout << "+---";
    }
    std::cout << "+\n";

    for (int i = 0; i < rows; ++i) {
        std::cout << "|";

        for (int j = 0; j < cols - 1; ++j) {
            std::cout << "   ";
            if (walls_v[i][j]) {
                std::cout << "|";
            } else {
                std::cout << " ";
            }
        }
        std::cout << "   |\n";

        if (i < rows - 1) {
            for (int j = 0; j < cols; ++j) {
                std::cout << "+";
                if (walls_h[i][j]) {
                    std::cout << "---";
                } else {
                    std::cout << "   ";
                }
            }
            std::cout << "+\n";
        }
    }

    for (int j = 0; j < cols; ++j) {
        std::cout << "+---";
    }
    std::cout << "+\n";
}
