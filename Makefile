generate_map: Map_main.c map.c
	gcc Map_main.c Map.c -o generate_map -Wall -Werror

clean:
	rm -f generate_map *~