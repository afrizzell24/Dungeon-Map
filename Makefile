map_file: main.c map_load.c map_save.c
	gcc main.c map_load.c map_save.c -o map_file -Wall -Werror

clean:
	rm -f map_file dungeon_file *~