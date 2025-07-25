#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <math.h>

using std::cout;
using std::endl;

struct Cell {
    int x, y;
};

int W; 
int H;
char **maze;

std::vector<Cell> walls;

void mazePrint() {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cout << maze[i][j];
        }
        cout << endl;
    }
}

void mapInit() {
    maze = new char*[H];
    for (int i = 0; i < H; i++) {
        maze[i] = new char[W];
        for (int j = 0; j < W; j++) {
            maze[i][j] = '#';
        }
    }
}

bool inBounds(int x, int y) {
    return x > 0 && x < W - 1 && y > 0 && y < H - 1;
}

void addWalls(int x, int y) {
    int dx[] = {2, -2, 0, 0};
    int dy[] = {0, 0, 2, -2};
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (inBounds(nx, ny) && maze[ny][nx] == '#') {
            walls.push_back({nx, ny});
        }
    }
}

void mazeGenerate() {
    int startX = 1 + (rand() % (W / 2)) * 2;
    int startY = 1 + (rand() % (H / 2)) * 2;
    maze[startY][startX] = ' ';
    addWalls(startX, startY);
    Cell directions[4] = {
        {2, 0}, {0, 2}, {-2, 0}, {0, -2}
    };
    while (!walls.empty()) {
        /*
        Sleep(100);
        system("cls");
        mazePrint();
        */
        int idx = rand() % walls.size();
        Cell cell = walls[idx];
        walls.erase(walls.begin() + idx);
        int dx[] = { 2, -2, 0, 0 };
        int dy[] = { 0, 0, 2, -2 };
        for (int i = 0; i < 4; i++) {
            int j = rand() % 4;
            std::swap(directions[i], directions[j]);
        }
        for (int i = 0; i < 4; i++) {
            int nx = cell.x + directions[i].x;
            int ny = cell.y + directions[i].y;
            if (inBounds(nx, ny) && maze[ny][nx] == ' ') {
                int betweenX = (cell.x + nx) / 2;
                int betweenY = (cell.y + ny) / 2;

                if (maze[cell.y][cell.x] == '#') {
                    maze[cell.y][cell.x] = ' ';
                    maze[betweenY][betweenX] = ' ';
                    addWalls(cell.x, cell.y);
                }
                break;
            }
        }
    }
}

void addEntryAndExit() {
    std::vector<Cell> borderCells;

    int x = rand() % (W - 1) + 1;
    int y = rand() % (H - 1) + 1;

    maze[y][x] = 'T';

    for (int x = 1; x < W - 1; x += 2) {
        if (maze[1][x] == ' ') borderCells.push_back({x, 0});
        if (maze[H - 2][x] == ' ') borderCells.push_back({x, H - 1});
    }
    for (int y = 1; y < H - 1; y += 2) {
        if (maze[y][1] == ' ') borderCells.push_back({0, y});
        if (maze[y][W - 2] == ' ') borderCells.push_back({W - 1, y});
    }

    Cell entry = borderCells[rand() % borderCells.size()];

    Cell exit = entry;
    double maxDist = 0;
    for (const Cell& c : borderCells) {
        double dist = std::sqrt((c.x - entry.x) * (c.x - entry.x) + (c.y - entry.y) * (c.y - entry.y));
        if (dist > maxDist) {
            maxDist = dist;
            exit = c;
        }
    }

    maze[entry.y][entry.x] = 'S';
    maze[exit.y][exit.x] = 'E';
}


int main(void) {
    srand(time(0));
    cout << "S - start\nE - exit\nT - treasure" << endl;
    cout << "Enter size x, y: ";
    std::cin >> W >> H;
    if (W % 2 == 0) W += 1;
    if (H % 2 == 0) H += 1;
    mapInit();
    mazeGenerate();
    addEntryAndExit();
    mazePrint();

    return 0;
}