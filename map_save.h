#ifndef MAP_SAVE_H
#define MAP_SAVE_H

void initializeMap();
void initializeValues(uint16_t maxRooms, uint16_t stairsUp, uint16_t stairsDown);
void saveInitialValues(FILE *file, uint16_t maxRooms, uint16_t stairsUp, uint16_t stairsDown);
void insertRooms(uint16_t maxRooms, uint8_t roomData[maxRooms][4], FILE *file);
void saveMapHardness(FILE *file);
void saveRooms(FILE *file, uint16_t maxRooms, uint8_t roomData[maxRooms][4]);
void saveStairs(uint16_t stairsUp, uint16_t stairsDown, FILE *file);
void displayMap();

#endif