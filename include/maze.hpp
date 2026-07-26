#include "utilities.hpp"
#include <vector>

#define TOP_LEFT_CORNER 1
#define BOTTOM_RIGHT_CORNER_Y (GAME_HEIGHT - 2)
#define BOTTOM_RIGHT_CORNER_X (GAME_WIDTH - 2)

// This function just transforms the game view in a grid where
// every free cell is surrounded by walls.
void gridify(WINDOW* game_window);

void start_end_markers(WINDOW* game_window);