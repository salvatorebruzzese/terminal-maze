#include "menu.hpp"
#include "game.hpp"
#include "ranking.hpp"
#include "utilities.hpp"
#include <curses.h>

Menu::Menu(int height, int width)
    : height_(height), width_(width), current_selection_(FIRST_MENU_OPTION),
      menu_window_(nullptr) {

    menu_window_ = new_boxed_window(height_, width_);

    if (menu_window_ != nullptr) {
        keypad(menu_window_, true);
    }
}

MainMenu::MainMenu(int height, int width) : Menu(height, width) {
    anchors_ = {" New maze ", " Leaderboard ", " Exit "};
}

PauseMenu::PauseMenu(int height, int width) : Menu(height, width) {
    anchors_ = {" Quit "};
}

Menu::~Menu() {
    if (menu_window_ != nullptr) {
        delwin(menu_window_);
    }
}

void MainMenu::run() {
    if (menu_window_ == nullptr) {
        return;
    }

    bool exit_menu = false;

    while (!exit_menu) {
        current_selection_ = handle_selection();

        switch (current_selection_) {
        case 0:
            game();
            wrefresh(menu_window_);
            break;
        case 1:
            show_ranking();
            wrefresh(menu_window_);
            break;
        case 2:
            exit_menu = true;
            break;
        }
    }
}
void PauseMenu::run() {
    if (menu_window_ == nullptr) {
        return;
    }
    handle_selection();
    wclear(menu_window_);
    wrefresh(menu_window_);
}

int Menu::handle_selection() {
    while (true) {
        visualize();
        int new_selection = wgetch(menu_window_);

        switch (new_selection) {
        case KEY_UP:
            current_selection_ = wrap(current_selection_ - 1, anchors_.size());
            break;
        case KEY_DOWN:
            current_selection_ = wrap(current_selection_ + 1, anchors_.size());
            break;
        // The implementation of KEY_ENTER is unreliable in PDCurses 3.9.
        case KEY_ENTER:
        case '\n':
        case '\r':
            return current_selection_;
        }
    }
}

void Menu::visualize() const {
    int y_position = height_ / (anchors_.size() + TOP_BOTTOM_BORDERS);

    wclear(menu_window_);

    wattron(menu_window_, A_REVERSE);
    wborder(menu_window_, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wattroff(menu_window_, A_REVERSE);

    for (int i = FIRST_MENU_OPTION; i < anchors_.size(); i++) {
        if (current_selection_ == i) {
            wattron(menu_window_, A_REVERSE);
        }

        // Moving the cursor to the left to center the option string.
        wmove(menu_window_, y_position * (i + 1) + 1,
              calculate_starting_x(width_, anchors_[i].size()));
        wprintw(menu_window_, "%s", anchors_[i].c_str());

        if (current_selection_ == i) {
            wattroff(menu_window_, A_REVERSE);
        }
    }

    wrefresh(menu_window_);
}

int Menu::wrap(int selected, int options) const {
    return ((selected % options) + options) % options;
}