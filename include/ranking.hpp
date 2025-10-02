#include <filesystem>
#include <fstream>
#include <string>
#include "json.hpp"

using json = nlohmann::json;
using std::string;
namespace fs = std::filesystem;

// Creates a window that shows the data in data.json.
void show_ranking();

// Creates a pop-up window that shows the error string.
void show_error(string error);

// Prints the ten players with fastest times.
void print_top_ten(WINDOW* ranking_window, json object);

// Updates the data.json file to add a new clear time.
void update_ranking(string current_player, int time);