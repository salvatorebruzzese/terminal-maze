#include "utilities.hpp"
#include "ranking.hpp"

void show_ranking() {
    if (!fs::exists("data.json")) {
        WINDOW * no_ranking = new_boxed_window(POPUP_HEIGHT, POPUP_WIDTH);
        mvwprintw(no_ranking, 2, 2, "No ranking data");
        wgetch(no_ranking);
    }

    std::ifstream f("data.json");
    
    json ranking = json::parse(f);

    f.close();
}

void update_ranking(string current_player, int time) {

}