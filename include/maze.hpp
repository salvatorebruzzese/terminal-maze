#include <curses.h>
#include <vector>

#define TOP_LEFT_CORNER 1
#define BOTTOM_RIGHT_CORNER_Y (GAME_HEIGHT - 2)
#define BOTTOM_RIGHT_CORNER_X (GAME_WIDTH - 2)

typedef struct point {
    int x, y;
} wall;

typedef std::vector<wall> wall_vector;

// Simple DSU implementation optimized with path compression and union by rank
class dsu {
    std::vector<int> parent, rank;

  public:
    dsu(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    void merge(int s1, int s2) {
        int root1 = find(s1);
        int root2 = find(s2);

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

// Turns the game view in a grid where
// every free cell is surrounded by walls.
void gridify(WINDOW* game_window);

void start_end_markers(WINDOW* game_window);