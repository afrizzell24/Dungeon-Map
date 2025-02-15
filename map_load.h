#ifndef MAP_LOAD_H
#define MAP_LOAD_H

void initializeDungeon();
void loadPC(FILE *file);
void loadDungeonHardness(FILE *file);
void loadDungeonRooms(FILE *file);
void loadStairs(FILE *file);
void displayDungeon();

#endif