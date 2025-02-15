#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <endian.h>
#include "map_load.h"

char dungeon[21][80];
uint8_t mapLoadHardness[21][80];

void initializeDungeon() 
{
    int i, j;

    for (i = 0; i < 21; ++i) {
        for (j = 0; j < 80; ++j) {

            if (i == 0 || i == (21 - 1)) {
                dungeon[i][j] = '-';
            } else if (j == 0 || j == (80 - 1)){
                dungeon[i][j] = '|';
            } else {
                dungeon[i][j] = ' ';
            }

        }
    }
}

void loadPC(FILE *file)
{
    uint8_t i, j;

    fread(&i, sizeof(uint8_t), 1, file);
    fread(&j, sizeof(uint8_t), 1, file);
    dungeon[j][i] = '@';
}

void loadDungeonHardness(FILE *file)
{
    fread(&mapLoadHardness, sizeof(uint8_t), 1680, file);
    int i, j;

    for (i = 0; i < 21; ++i) {
        for (j = 0; j < 80; ++j) {
            
            if (mapLoadHardness[i][j] == 0 && dungeon[i][j] != '@') {
                dungeon[i][j] = '#';
            } else if (mapLoadHardness[i][j] == 255 && dungeon[i][j] != '|' && dungeon[i][j] != '-') {
                dungeon[i][j] = '*';
            }
        }
    }
}

void addRoom(uint8_t col, uint8_t row, uint8_t width, uint8_t height, char map[21][80])
{
    uint8_t i, j;
    for (i = row; i < row + height; ++i) {
        for (j = col; j < col + width; ++j) {
            if (map[i][j] != '@') {
                map[i][j] = '.';
            }
        }
    }
}

void loadDungeonRooms(FILE *file)
{
    uint16_t i, numRooms;

    fread(&numRooms, sizeof(uint16_t), 1, file);
    numRooms = htobe16(numRooms);

    for (i = 0; i < numRooms; ++i)
    {
        uint8_t col, row, width, height;

        fread(&col, sizeof(uint8_t), 1, file);
        fread(&row, sizeof(uint8_t), 1, file);
        fread(&width, sizeof(uint8_t), 1, file);
        fread(&height, sizeof(uint8_t), 1, file);

        addRoom(col, row, width, height, dungeon);
    }
}

void loadStairs(FILE *file)
{
    uint8_t stairPosX, stairPosY;
    uint16_t numStairsUp, numStairsDown, i;

    fread(&numStairsUp, sizeof(uint16_t), 1, file);
    numStairsUp = htobe16(numStairsUp);

    for (i = 0; i < numStairsUp; ++i)
    {
        fread(&stairPosX, sizeof(uint8_t), 1, file);
        fread(&stairPosY, sizeof(uint8_t), 1, file);
        dungeon[stairPosY][stairPosX] = '<';
    }

    fread(&numStairsDown, sizeof(uint16_t), 1, file);
    numStairsDown = htobe16(numStairsDown);

    for (i = 0; i < numStairsDown; ++i)
    {
        fread(&stairPosX, sizeof(uint8_t), 1, file);
        fread(&stairPosY, sizeof(uint8_t), 1, file);
        dungeon[stairPosY][stairPosX] = '>';
    }
}

void displayDungeon()
{
    int i, j;

    for (i = 0; i < 21; ++i) {
        for (j = 0; j < 80; ++j) {
            printf("%c", dungeon[i][j]);
        }
        printf("\n");
    }
}