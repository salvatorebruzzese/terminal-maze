#include "game.hpp"
#include "menu.hpp"
#include "ranking.hpp"
#include "utilities.hpp"

constexpr int NUM_MENU_OPTIONS  = 3;
constexpr int FIRST_MENU_OPTION = 0;
constexpr int LAST_MENU_OPTION  = NUM_MENU_OPTIONS - 1;
constexpr int TOP_BOTTOM_BORDERS = 2;
constexpr int MENU_HEIGHT = 15;
constexpr int MENU_WIDTH = 30;

void menu(string current_player) {

    int current_selection = 0;
    WINDOW * menu_window = new_boxed_window(MENU_HEIGHT, MENU_WIDTH);

    if (menu_window == nullptr) return;

    keypad(menu_window, true);

    while (true) {
        current_selection = menu_selection(current_selection, menu_window);
        switch (current_selection)
        {
            case 0: 
                game();
                wrefresh(menu_window);
                break;
            case 1: 
                show_ranking();
                wrefresh(menu_window);
                break;
            case 2:
                delwin(menu_window);
                return;
        }
    }
    
}

int menu_selection(int current_selection, WINDOW * menu_window) {
    
    // Menu wrap-around logic; ensures non-negative result even if selected < 0.
    auto wrap = [](int selected, int options) -> int {
        return ((selected % options) + options) % options;
    };

    while (true)
    {
        visualize_menu(current_selection, menu_window);
        int new_selection = wgetch(menu_window);

        switch (new_selection)
        {
            case KEY_UP:
                current_selection = wrap(current_selection - 1, NUM_MENU_OPTIONS);
                break;
            case KEY_DOWN:
                current_selection = wrap(current_selection + 1, NUM_MENU_OPTIONS);
                break;
            // The implementation of KEY_ENTER is unreliable in PDCurses 3.9.
            case KEY_ENTER:
            case '\n':
            case '\r':
                return current_selection;
        }
    }
}

void visualize_menu(int current_selection, WINDOW * menu_window) {

    static string anchors[NUM_MENU_OPTIONS] = {"New maze", "Leaderboard", "Exit"};

    int y_position = MENU_HEIGHT/(NUM_MENU_OPTIONS + TOP_BOTTOM_BORDERS);

    wclear(menu_window);
    wborder(menu_window, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK,
                 ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK);

    for (int i = FIRST_MENU_OPTION; i <= LAST_MENU_OPTION; i++) {
        if (current_selection == i)
            wattron(menu_window, A_REVERSE);

        // Moving the cursor to the left to center the option string.
        wmove(menu_window, y_position * (i + 1) + 1, center_string(MENU_WIDTH, anchors[i].c_str()));
        wprintw(menu_window, "%s", anchors[i].c_str());
        
        wattroff(menu_window, A_REVERSE);
    }

    wrefresh(menu_window);
}