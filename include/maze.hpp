#include "utilities.hpp"
#include <vector>

typedef std::vector<std::vector<bool>> boolean_game_matrix;

// This function just transforms the game view in a grid where
// every free cell is surrounded by walls.
void gridify(WINDOW* game_window);

void start_end_markers(WINDOW* game_window);