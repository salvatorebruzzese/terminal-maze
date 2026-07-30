#ifndef MENU_H
#define MENU_H

#include "curses.h"
#include <string>
#include <vector>

class Menu {
  public:
    Menu(int height, int width);

    ~Menu();

    Menu(const Menu&) = delete;
    Menu& operator=(const Menu&) = delete;

  protected:
    static constexpr int FIRST_MENU_OPTION = 0;
    static constexpr int TOP_BOTTOM_BORDERS = 2;

    std::string current_player_;
    int height_;
    int width_;
    std::vector<std::string> anchors_;
    WINDOW* menu_window_;
    int current_selection_;

    int handle_selection();
    void visualize() const;
    int wrap(int selected, int options) const;
};

class MainMenu : public Menu {
  public:
    MainMenu(int height, int width);
    void run();
};

class PauseMenu : public Menu {
  public:
    PauseMenu(int height, int width);

    bool run();
};

#endif // MENU_H