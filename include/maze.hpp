#include "utilities.hpp"
#include <curses.h>
#include <map>
#include <tuple>
#include <vector>

#define TOP_LEFT_CORNER 1
#define BOTTOM_RIGHT_CORNER_Y (GAME_HEIGHT - 2)
#define BOTTOM_RIGHT_CORNER_X (GAME_WIDTH - 2)

typedef std::tuple<int, int> pair;

// Simple DSU implementation optimized with path compression and union by rank.
// The implementation is not general-purpose, as it is tailored for the maze
class dsu {
    std::map<pair, pair> parent;
    std::map<pair, int> rank;

  public:
    dsu() {
        for (int y = 1; y <= GAME_HEIGHT_NO_BORDERS; y = y + 2) {
            for (int x = 1; x <= GAME_WIDTH_NO_BORDERS; x = x + 2) {
                pair pos(y, x);
                parent[pos] = pos;
                rank[pos] = 0;
            }
        }
    }

    // Path compression on tuples
    pair find(const pair& i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    // Union by rank
    void merge(const pair& s1, const pair& s2) {
        pair root1 = find(s1);
        pair root2 = find(s2);

        if (root1 == root2)
            return;

        if (rank[root1] < rank[root2]) {
            parent[root1] = root2;
        } else if (rank[root2] < rank[root1]) {
            parent[root2] = root1;
        } else {
            parent[root1] = root2;
            rank[root2]++;
        }
    }
};

// Turns the game view in a grid where every free cell is surrounded by walls.
// Adds the walls to a map mid-process in preparation for Kruskal's algorithm
void gridify(WINDOW* game_window, std::vector<pair>& walls);

void maze(WINDOW* game_window);

void start_end_markers(WINDOW* game_window);