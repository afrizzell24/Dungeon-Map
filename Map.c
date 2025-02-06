#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Map.h"

char map[21][80];
int rows = 21;
int cols = 80;

void initializeMap() {
    int i, j;

    for (i = 0; i < rows; ++i) {
        for (j = 0; j < cols; ++j) {

            if (i == 0 || i == (rows - 1)) {
                map[i][j] = '-';
            } else if (j == 0 || j == (cols - 1)){
                map[i][j] = '|';
            } else {
                map[i][j] = ' ';
            }

        }
    }
}

void moveXDirection(int start, int move, int height) {
    int i;

    if (move > 0) {
        for (i = 0; i < move; ++i) {
            if (map[height][start + i] != '.' && !(((map[height + 1][start + i - 1] == '#' || map[height + 1][start + i - 1] == '.') && map[height + 1][start + i] == '#' && (map[height + 1][start + i + 1] == '#' || map[height + 1][start + i + 1] == '.')) || 
               ((map[height - 1][start + i - 1] == '#' || map[height - 1][start + i - 1] == '.') && map[height - 1][start + i] == '#' && (map[height - 1][start + i + 1] == '#' || map[height - 1][start + i + 1] == '.')))) {

                map[height][start + i] = '#';
            }
        }
    } else {
        for (i = 0; i > move; --i) {
            if (map[height][start + i] != '.' && !(((map[height + 1][start + i - 1] == '#' || map[height + 1][start + i - 1] == '.') && map[height + 1][start + i] == '#' && (map[height + 1][start + i + 1] == '#' || map[height + 1][start + i + 1] == '.')) || 
               ((map[height - 1][start + i - 1] == '#' || map[height - 1][start + i - 1] == '.') && map[height - 1][start + i] == '#' && (map[height - 1][start + i + 1] == '#' || map[height - 1][start + i + 1] == '.')))) {
                
                map[height][start + i] = '#';
            }
        }        
    }
}

void moveYDirection(int start, int move, int width) {
    int i;

    if (move > 0) {

        for (i = 0; i < move; ++i) {
            if (map[start + i][width] != '.') {
                map[start + i][width] = '#';
            }
        }

    } else {

        for (i = 0; i > move; --i) {
            if (map[start + i][width] != '.') {
                map[start + i][width] = '#';
            }
        }

    }
}

void insertPaths(int startHeight, int startWidth, int endHeight, int endWidth) {
    int direction, moveX, moveY;

    direction = rand() % 2;
    moveX = endWidth - startWidth;
    moveY = endHeight - startHeight;

    if (direction == 0) {
        moveXDirection(startWidth, moveX, startHeight);
        moveYDirection(startHeight, moveY, endWidth);
    } else {
        moveYDirection(startHeight, moveY, startWidth);
        moveXDirection(startWidth, moveX, endHeight);
    }
}

void insertRooms() {
    const int MAX_ROOMS = (rand() % 3) + 6;
    int currentRooms, roomHeight, roomWidth, roomX, roomY, counter, bool, i, j;
    int pathPositions[2][MAX_ROOMS];

    currentRooms = 0;
    while (currentRooms < MAX_ROOMS) {
        roomHeight = (rand() % 4) + 3;
        roomWidth = (rand() % 12) + 4;
        roomX = (rand() % (cols - 1)) + 1;
        roomY = (rand() % (rows - 1)) + 1;
        counter = 0;

        while (counter <= 10) {
            if ((roomHeight + roomY) < (rows - 1) && (roomWidth + roomX) < (cols - 1)) {

                bool = 1;
                for (i = roomY - 3; i < (roomY + roomHeight + 3); ++i) {
                    for (j = roomX - 3; j < (roomX + roomWidth + 3); ++j) {
                        if (map[i][j] == '.') {
                            bool = 0;
                        }
                    }
                }

                if (bool == 1) {
                    for (i = roomY; i < (roomY + roomHeight); ++i) {
                        for (j = roomX; j < (roomX + roomWidth); ++j) {
                            map[i][j] = '.';
                        }
                    }
                    pathPositions[0][currentRooms] = (rand() % roomHeight) + roomY;
                    pathPositions[1][currentRooms] = (rand() % roomWidth) + roomX;
                    ++currentRooms;
                    break;
                }
            }
            ++counter;
            roomX = (rand() % (cols - 1)) + 1;
            roomY = (rand() % (rows - 1)) + 1;
        }
    }

    for (i = 0; i < MAX_ROOMS - 1; ++i) {
        insertPaths(pathPositions[0][i], pathPositions[1][i], pathPositions[0][i + 1], pathPositions[1][i + 1]);
    }
}

void insertStairs() {
    int numStairsUp, numStairsDown, currStairsUp, currStairsDown, x, y;

    numStairsUp = (rand() % 2) + 1;
    numStairsDown = (rand() % 2) + 1;
    currStairsUp = 0;
    currStairsDown = 0;

    while (currStairsUp < numStairsUp) {
        x = rand() % rows;
        y = rand() % cols;
        if (map[x][y] == '.') {
            map[x][y] = '<';
            ++currStairsUp;
        }
    }

    while (currStairsDown < numStairsDown) {
        x = rand() % rows;
        y = rand() % cols;
        if (map[x][y] == '.') {
            map[x][y] = '>';
            ++currStairsDown;
        }
    }    
}

void displayMap() {
    int i, j;

    for (i = 0; i < rows; ++i) {
        for (j = 0; j < cols; ++j) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}