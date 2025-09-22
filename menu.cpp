#include "menu.hpp"
#include "utilities.hpp"

void menu() {

    int current_selection = 0;
    WINDOW * menu_window = new_boxed_window(MENU_HEIGHT, MENU_WIDTH);

    if (menu_window == nullptr) return;

    keypad(menu_window, true);

    while (true) {
        current_selection = menu_selection(current_selection, menu_window);
        switch (current_selection)
        {
        case 2:
            delwin(menu_window);
            return;
            break;
        }
    }
    
}

int menu_selection(int current_selection, WINDOW * menu_window) {
    
    while (true)
    {
        visualize_menu(current_selection, menu_window);
        chtype new_selection = wgetch(menu_window);

        switch (new_selection)
        {
        case KEY_UP:
            if (current_selection <= 0)
                current_selection = NUM_OPTIONS - 1;
            else --current_selection; 
            break;
        case KEY_DOWN:
            if (current_selection >= NUM_OPTIONS - 1)
                current_selection = 0;
            else ++current_selection; 
            break;
        case KEY_ENTER:
            return current_selection;
            break;
        // The implementation of KEY_ENTER is unreliable in PDCurses 3.9
        case '\n':
            return current_selection;
        }
    }
}

void visualize_menu(int current_selection, WINDOW * menu_window) {

    string anchors[NUM_OPTIONS] = {"New maze", "Rankings", "Exit"};

    // It could be needed to add more options; the extra two accounts for
    // the top and bottom borders.
    int y_position = MENU_HEIGHT/(NUM_OPTIONS + 2);
    int x_position = MENU_WIDTH/2;

    wclear(menu_window);
    box(menu_window, ACS_VLINE, ACS_HLINE);

    for (int i = 0; i < NUM_OPTIONS; i++) {
        if (current_selection == i)
            wattron(menu_window, A_REVERSE);

        // Moving the cursor to the left to center the option string
        wmove(menu_window, y_position * (i + 1) + 1, x_position - static_cast<int>(anchors[i].length())/2);
        wprintw(menu_window, "%s", anchors[i].c_str());
        
        wattroff(menu_window, A_REVERSE);
    }

    wrefresh(menu_window);
}