#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <endian.h>
#include "map_save.h"

char map[21][80];
uint8_t mapSaveHardness[21][80];
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

void saveInitialValues(FILE *file, uint16_t maxRooms, uint16_t stairsUp, uint16_t stairsDown)
{
        uint32_t fileSize = (1708 + (maxRooms * 4) + (stairsUp * 2) + (stairsDown * 2));
        char fileMarker[] = "RLG327-S2025";
        uint32_t versionMarker = 0;

        fwrite(&fileMarker, sizeof(char), 12, file);

        versionMarker = htobe32(versionMarker);
        fwrite(&versionMarker, sizeof(uint32_t), 1, file);

        fwrite(&fileSize, sizeof(uint32_t), 1, file);
}

void moveXDirection(int start, int move, int height) 
{
    int i;

    if (move > 0) {
        for (i = 0; i < move; ++i) {
            if (map[height][start + i] != '.' && map[height][start + i] != '@' && !(((map[height + 1][start + i - 1] == '#' || map[height + 1][start + i - 1] == '.') && (map[height + 1][start + i] == '#' || map[height + 1][start + i] == '.') && (map[height + 1][start + i + 1] == '#' || map[height + 1][start + i + 1] == '.')) || 
               ((map[height - 1][start + i - 1] == '#' || map[height - 1][start + i - 1] == '.') && (map[height - 1][start + i] == '#' || map[height - 1][start + i] == '.') && (map[height - 1][start + i + 1] == '#' || map[height - 1][start + i + 1] == '.')))) {

                map[height][start + i] = '#';
            }
        }
    } else {
        for (i = 0; i > move; --i) {
            if (map[height][start + i] != '.' && map[height][start + i] != '@' && !(((map[height + 1][start + i - 1] == '#' || map[height + 1][start + i - 1] == '.') && (map[height + 1][start + i] == '#' || map[height + 1][start + i] == '.') && (map[height + 1][start + i + 1] == '#' || map[height + 1][start + i + 1] == '.')) || 
               ((map[height - 1][start + i - 1] == '#' || map[height - 1][start + i - 1] == '.') && (map[height - 1][start + i] == '#' || map[height - 1][start + i] == '.') && (map[height - 1][start + i + 1] == '#' || map[height - 1][start + i + 1] == '.')))) {
                
                map[height][start + i] = '#';
            }
        }        
    }
}

void moveYDirection(int start, int move, int width) 
{
    int i;

    if (move > 0) {

        for (i = 0; i < move; ++i) {
            if (map[start + i][width] != '.' && map[start + i][width] != '@') {
                map[start + i][width] = '#';
            }
        }

    } else {

        for (i = 0; i > move; --i) {
            if (map[start + i][width] != '.' && map[start + i][width] != '@') {
                map[start + i][width] = '#';
            }
        }

    }
}

void insertPaths(int startHeight, int startWidth, int endHeight, int endWidth) 
{
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

void insertRooms(uint16_t maxRooms, uint8_t roomData[maxRooms][4], FILE *file) 
{
    int currentRooms, roomHeight, roomWidth, roomX, roomY, counter, bool, i, j;
    int pathPositions[2][maxRooms];

    currentRooms = 0;
    while (currentRooms < maxRooms) {
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

                    if (currentRooms == 0) {
                        int pcX, pcY;
                        uint8_t pcXWrite, pcYWrite;
                        pcY = (rand() % roomHeight) + roomY;
                        pcX = (rand() % roomWidth) + roomX;
                        map[pcY][pcX] = '@';

                        pcXWrite = pcX;
                        pcYWrite = pcY;
                        fwrite(&pcXWrite, sizeof(uint8_t), 1, file);
                        fwrite(&pcYWrite, sizeof(uint8_t), 1, file);
                    }

                    roomData[currentRooms][0] = roomX;
                    roomData[currentRooms][1] = roomY;
                    roomData[currentRooms][2] = roomWidth;
                    roomData[currentRooms][3] = roomHeight;
                    ++currentRooms;
                    break;
                }
            }
            ++counter;
            roomX = (rand() % (cols - 1)) + 1;
            roomY = (rand() % (rows - 1)) + 1;
        }
    }

    for (i = 0; i < maxRooms - 1; ++i) {
        insertPaths(pathPositions[0][i], pathPositions[1][i], pathPositions[0][i + 1], pathPositions[1][i + 1]);
    }
}

void saveMapHardness(FILE *file)
{
    int i, j;

    for (i = 0; i < 21; ++i) {
        for (j = 0; j < 80; ++j) {

            if (map[i][j] == '|' || map[i][j] == '-') {
                mapSaveHardness[i][j] = 255;
            } else if (map[i][j] == ' ') {
                mapSaveHardness[i][j] = 1;
            } else {
                mapSaveHardness[i][j] = 0;
            }

        }
    }

    fwrite(&mapSaveHardness, sizeof(uint8_t), 1680, file);
}

void saveRooms(FILE *file, uint16_t maxRooms, uint8_t roomData[maxRooms][4])
{
    uint16_t i, maxRoomsConverted;

    maxRoomsConverted = maxRooms;
    maxRoomsConverted = htobe16(maxRoomsConverted);
    fwrite(&maxRoomsConverted, sizeof(uint16_t), 1, file);
    for (i = 0; i < maxRooms; ++i)
    {
        fwrite(&roomData[i][0], sizeof(uint8_t), 1, file);
        fwrite(&roomData[i][1], sizeof(uint8_t), 1, file);
        fwrite(&roomData[i][2], sizeof(uint8_t), 1, file);
        fwrite(&roomData[i][3], sizeof(uint8_t), 1, file);
    }
}

void saveStairs(uint16_t stairsUp, uint16_t stairsDown, FILE *file) {
    uint8_t x, y;
    uint16_t currStairsUp, currStairsDown, stairsUpNative, stairsDownNative;

    currStairsUp = 0;
    currStairsDown = 0;
    stairsUpNative = stairsUp;
    stairsDownNative = stairsDown;

    stairsUp = htobe16(stairsUp);
    fwrite(&stairsUp, sizeof(uint16_t), 1, file);

    while (currStairsUp < stairsUpNative) {
        x = rand() % rows;
        y = rand() % cols;
        if (map[x][y] == '.') {
            map[x][y] = '<';

            fwrite(&y, sizeof(uint8_t), 1, file);
            fwrite(&x, sizeof(uint8_t), 1, file);
            ++currStairsUp;
        }
    }

    stairsDown = htobe16(stairsDown);
    fwrite(&stairsDown, sizeof(uint16_t), 1, file);

    while (currStairsDown < stairsDownNative) {
        x = rand() % rows;
        y = rand() % cols;
        if (map[x][y] == '.') {
            map[x][y] = '>';

            fwrite(&y, sizeof(uint8_t), 1, file);
            fwrite(&x, sizeof(uint8_t), 1, file);
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