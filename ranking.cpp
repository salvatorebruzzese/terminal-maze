#include "utilities.hpp"
#include "ranking.hpp"

void show_ranking() {

    // The column and row to print the warning to.
    constexpr int WARNING_COL = 2;
    constexpr int WARNING_ROW = 2;
    
    if (!fs::exists("data.json")) {
        WINDOW * no_ranking = new_boxed_window(POPUP_HEIGHT, POPUP_WIDTH);
        mvwprintw(no_ranking, WARNING_ROW, WARNING_COL, "No ranking data");
        wgetch(no_ranking);
    }

    std::ifstream f("data.json");
    
    json ranking = json::parse(f);

    f.close();
}

void update_ranking(string current_player, int time) {

}