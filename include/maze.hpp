#include <curses.h>
#include <random>
#include <vector>

#define TOP_LEFT_CORNER 1
#define FIRST_COLUMN 1
#define LAST_COLUMN (GAME_WIDTH - 2)
#define READCHAR 1

typedef std::pair<int, int> pair;

class MazeGenerator {
  public:
    explicit MazeGenerator(WINDOW* game_window);

    // Generates the maze and returns the start and end markers (y-coordinates)
    pair generate();

  private:
    WINDOW* game_window_;
    std::vector<pair> walls_;
    std::mt19937 generator_;

    void gridify();
    void kruskal();
    pair start_end_markers();
};