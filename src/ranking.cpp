#include "ranking.hpp"
#include "curses.h"
#include "json.hpp"
#include "utilities.hpp"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <string>

using json = nlohmann::json;
using string = std::string;

namespace fs = std::filesystem;

constexpr int WARNING_ROW = 2;     // The row where the error is printed.
constexpr int WARNING_COL = 2;     // The column where the error is printed.
constexpr int RANKING_HEIGHT = 13; // The height of the ranking window.
constexpr int RANKING_WIDTH = 20;  // The width of the ranking window.
constexpr int PLAYERS_PRINT_COL =
    3; // The column where player names are printed.
constexpr int PLAYERS_PRINT_ROW = 2; // The row where player names are printed.
const char* TOP_TEN = " Top 10 ";

void show_ranking() {

    fs::path data_path = get_data_path();

    if (!fs::exists(data_path)) {
        show_error("No ranking data");
        return;
    }

    std::ifstream f(data_path);

    if (!json::accept(f)) {
        show_error("Invalid JSON");
        f.close();
        return;
    }

    // Returns the read position at the beginning of the file.
    f.clear();
    f.seekg(0, std::ios::beg);

    json ranking = json::parse(f);

    WINDOW* ranking_window = new_boxed_window(RANKING_HEIGHT, RANKING_WIDTH);

    print_top_ten(ranking_window, ranking);

    wgetch(ranking_window);

    f.close();
    delwin(ranking_window);
}

void print_top_ten(WINDOW* ranking_window, const json& object) {

    auto it = object.begin();
    int number_of_cycles = 0;
    int current_row = PLAYERS_PRINT_ROW;

    mvwprintw(ranking_window, 0, calculate_starting_x(RANKING_WIDTH, TOP_TEN),
              "%s", TOP_TEN);

    while (it != object.end() && number_of_cycles < 10) {

        int time = it->value("time", -1);
        std::string player = it->value("player", "ERROR");

        mvwprintw(ranking_window, current_row, PLAYERS_PRINT_COL, "%s: %d",
                  player.c_str(), time);

        it++;
        current_row++;
        number_of_cycles++;
    }

    wrefresh(ranking_window);
}

void update_ranking(const string& current_player, int time) {

    fs::path data_path = get_data_path();
    json ranking_data;

    std::ifstream input_file(data_path);
    if (input_file.is_open() &&
        input_file.peek() != std::ifstream::traits_type::eof()) {
        try {
            input_file >> ranking_data;
        } catch (json::parse_error& e) {
            ranking_data = json::array();
        }
    } else {
        ranking_data = json::array();
    }

    json new_entry = {{"player", current_player}, {"time", time}};
    ranking_data.push_back(new_entry);

    std::sort(
        ranking_data.begin(), ranking_data.end(),
        [](const json& a, const json& b) { return a["time"] < b["time"]; });

    std::ofstream output_file(data_path);
    output_file << ranking_data.dump(4);
}

void show_error(const string& error) {

    WINDOW* error_window = new_boxed_window(POPUP_HEIGHT, POPUP_WIDTH);
    mvwprintw(error_window, WARNING_ROW,
              calculate_starting_x(POPUP_WIDTH, error.c_str()), "%s",
              error.c_str());
    wgetch(error_window);
    delwin(error_window);
}