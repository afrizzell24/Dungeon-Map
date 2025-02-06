#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Map.h"

int main (int argc, char *argv[]) {
    srand(time(NULL));

    initializeMap();
    insertRooms();
    insertStairs();
    displayMap();

    return 0;
}