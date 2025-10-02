#include "utilities.hpp"
#include "ranking.hpp"

constexpr int WARNING_ROW = 2;
constexpr int WARNING_COL = 2;
constexpr int RANKING_HEIGHT = 8;
constexpr int RANKING_WIDTH = 20;
constexpr int PRINT_COL = 3;
constexpr int MAX_PLAYERS = 5;

void show_ranking() {
    
    if (!fs::exists("data.json")) {
        show_error("No ranking data");
        return;
    }

    std::ifstream f("data.json");

    if (!json::accept(f)) {
        f.close();
        return;
    }

    f.clear();
    f.seekg(0, std::ios::beg);
    
    json ranking = json::parse(f);

    WINDOW * ranking_window = new_boxed_window(RANKING_HEIGHT, RANKING_WIDTH);
    
    mvwprintw(ranking_window, 1, 1, "Top 5");

    int PRINT_ROW = 2;
    int cycle = 0;

    for (json::iterator it = ranking.begin();
         it != ranking.end() && cycle < MAX_PLAYERS;
         it++, PRINT_ROW++, cycle++) {
        int score = it->at("score").get<int>();
        string player = it->at("player").get<string>();

        mvwprintw(ranking_window, PRINT_ROW, PRINT_COL, "%s: %d", player.c_str(), score);
    }

    wrefresh(ranking_window);

    wgetch(ranking_window);

    f.close();
    delwin(ranking_window);
}

void update_ranking(string current_player, int time) {

}

void show_error(string error) {
    
    WINDOW * error_window = new_boxed_window(POPUP_HEIGHT, POPUP_WIDTH);
    mvwprintw(error_window, WARNING_ROW, WARNING_COL, error.c_str());
    wgetch(error_window);
    delwin(error_window);
}