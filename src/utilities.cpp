#include <cstring>
#include <filesystem>
#include <windows.h>
#include <string>
#include "curses.h"
#include "utilities.hpp"

using std::string;

namespace fs = std::filesystem;

int center_string(int width, const char * str) {
    return width/2 - strlen(str)/2;
}

void init() {
    if (!initscr()) {
        fprintf(stderr, "Failed to initialize curses\n");
        exit(1);
    }

    curs_set(0);
    noecho();
    cbreak();
    refresh();
}

WINDOW* new_boxed_window(int height, int width) {
    if (height < 2 || width < 2) return nullptr;

    int sh, sw;
    getmaxyx(stdscr, sh, sw);

    if (height > sh || width > sw) return nullptr;

    int y = (sh - height) / 2;
    int x = (sw - width) / 2;

    WINDOW* win = newwin(height, width, y, x);
    if (!win) return nullptr;

    if (wborder(win, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK,
                     ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK) == ERR || wrefresh(win) == ERR) {
        delwin(win);
        return nullptr;
    }

    return win;
}

fs::path get_data_path() {

    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);         // Get executable's path

    fs::path gameDir = fs::path(buffer).parent_path();  // Get the folder the executable is running in

    fs::path dataFile = gameDir / "data.json";          // Append data.json

    return dataFile;
}