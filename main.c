#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdint.h>
#include "map_save.h"
#include "map_load.h"

void usage(const char *s)
{
    fprintf(stderr, "%s [--save | --load]\n", s);
}

int main (int argc, char *argv[]) 
{
    int option;

    option = -1;
    if (argc == 2 && argv[1][0] == '-' && argv[1][1] == '-') {
        if (argv[1][2] == 's' && argv[1][3] == 'a' && argv[1][4] == 'v' && argv[1][5] == 'e') {
            option = 0;
        } else if (argv[1][2] == 'l' && argv[1][3] == 'o' && argv[1][4] == 'a' && argv[1][5] == 'd') {
            option = 1;
        }
    }

    if (option == -1) {
        usage(argv[0]);
        return -1;
    }

    FILE *file;
    char *home;
    char *dungeon_file;
    int dungeon_file_length;

    home = getenv("HOME");
    dungeon_file_length = strlen(home) + strlen("/.rlg327/dungeon") + 1;

    if (!(dungeon_file = malloc(dungeon_file_length * sizeof (*dungeon_file)))) {
        printf("Failed to allocate space\n");
        return -1;
    }

    strcpy(dungeon_file, home);
    strcat(dungeon_file, "/.rlg327/dungeon");

    if (option == 0) {

        srand(time(NULL));

        file = fopen("dungeon_file", "wb");
        if (file == NULL) {
            printf("Failed to open file\n");
            return -1;
        }

        uint16_t maxRooms, stairsUp, stairsDown;

        maxRooms = (rand() % 3) + 6;
        stairsUp = (rand() % 2) + 1;
        stairsDown = (rand() % 2) + 1;
        uint8_t roomData[maxRooms][4];
        

        initializeMap();
        saveInitialValues(file, maxRooms, stairsUp, stairsDown);
        insertRooms(maxRooms, roomData, file);
        saveMapHardness(file);
        saveRooms(file, maxRooms, roomData);
        saveStairs(stairsUp, stairsDown, file);
        displayMap();
    
    } else if (option == 1) {
        
        file = fopen("dungeon_file", "rb");
        if (file == NULL) {
            printf("Failed to open file\n");
            return -1;
        }
 
        fseek(file, 20, SEEK_SET);

        initializeDungeon();
        loadPC(file);
        loadDungeonHardness(file);
        loadDungeonRooms(file);
        loadStairs(file);
        displayDungeon();
    }

    fclose(file);
    return 0;
}