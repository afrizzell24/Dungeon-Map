#ifndef MAP_H
#define MAP_H

void initializeMap();
void moveXDirection(int start, int move, int height);
void moveYDirection(int start, int move, int widthPosition);
void insertPaths(int startHeight, int startWidth, int endHeight, int endWidth);
void insertRooms();
void insertStairs();
void displayMap();

#endif