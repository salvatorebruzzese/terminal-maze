#include "utilities.hpp"
#include "ranking.hpp"

constexpr int WARNING_ROW = 2;
constexpr int WARNING_COL = 2;

void show_ranking() {
    
    if (!fs::exists("data.json")) {
        show_error("No ranking data");
        return;
    }

    std::ifstream f("data.json");
    
    json ranking = json::parse(f);

    f.close();
}

void update_ranking(string current_player, int time) {

}

void show_error(string error) {
    
    WINDOW * error_window = new_boxed_window(POPUP_HEIGHT, POPUP_WIDTH);
    mvwprintw(error_window, WARNING_ROW, WARNING_COL, error.c_str());
    wgetch(error_window);
    delwin(error_window);
}