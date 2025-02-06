NOTE: All code line references are in Map.c

This program creates a map for the game. The program first creates an 21-80 array with a border, so the "playable area" 
is really a 19-78 array (Lines 10-26). Next, the program inserts 6-8 rooms with random sizes randomly around the map (Lines 88-134).
Throughout this method, there are multiple references to an array called pathPositions, this is an array storing random coordinates for 
each room so corridors can be added At the end of the method.

After inserting rooms, the corridors are added by simply connecting them from the X and Y directions. The program randomly picks
whether it should start with the X or Y direction (Lines ).

NOTE: In the moveXDirection() method, there is a disgusting chain in the if statements. I know it looks terrible. I
added this to stop paths generating right next to each in the X direction. I left it in because it worked on the first try
and I think it looks better. I didn't add it for the Y direction because it's much less likely to happen and it's horrible to read.

Lastly, the program adds the stairs and displays the map on the screen.
