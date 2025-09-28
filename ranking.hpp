#include <filesystem>
namespace fs = std::filesystem;
#include <fstream>
#include <string>
using std::string;
#include "json.hpp"
using json = nlohmann::json;

// Creates a window that shows the data in data.json.
void show_ranking();

// Creates a pop-up window that shows the error string.
void show_error(string error);

// Updates the data.json file to add a new clear time.
void update_ranking(string current_player, int time);