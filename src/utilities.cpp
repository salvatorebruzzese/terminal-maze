#include "utilities.hpp"
#include "curses.h"
#include <cstdio>
#include <cstdlib>
#include <filesystem>

#include <string>

#ifdef _WIN32
#include <libloaderapi.h>
#else
#include <limits.h>
#include <unistd.h>
#endif

using std::string;

namespace fs = std::filesystem;

int calculate_starting_x(const int width, const int len) {
    return width / 2 - len / 2;
}

void init_curses() {
    setlocale(LC_ALL, "");
    if (!initscr()) {
        fprintf(stderr, "Failed to initialize ncurses\n");
        exit(1);
    }

    start_color();
    init_pair(1, COLOR_BLACK, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_RED);

    curs_set(0);
    noecho();
    cbreak();
    refresh();
}

WINDOW* new_boxed_window(int height, int width) {
    if (height < 2 || width < 2)
        return nullptr;

    int sh, sw;
    getmaxyx(stdscr, sh, sw);

    if (height > sh || width > sw)
        return nullptr;

    int y = (sh - height) / 2;
    int x = (sw - width) / 2;

    WINDOW* win = newwin(height, width, y, x);
    if (!win)
        return nullptr;

    wattron(win, A_REVERSE);
    if (wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ') == ERR ||
        wrefresh(win) == ERR) {
        wattroff(win, A_REVERSE);
        delwin(win);
        return nullptr;
    }

    return win;
}

fs::path get_data_path() {
#ifdef _WIN32
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH); // Get executable's path

    // Get the folder the executable is running in
    fs::path gameDir = fs::path(buffer).parent_path();

    return gameDir / "data.json"; // Append data.json;
#else
    char buffer[PATH_MAX + 1];
    // Special symlink to read executable working directory
    ssize_t len = readlink("/proc/self/exe", buffer, PATH_MAX);

    if (len != -1) {
        buffer[len] = '\0';
        fs::path gameDir = fs::path(buffer).parent_path();
        return gameDir / "data.json";
    }

    return "";
#endif
}