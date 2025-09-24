#include <filesystem>
namespace fs = std::filesystem;
#include <fstream>
#include <string>
using std::string;
#include "external/nlohmann/json.hpp"
using json = nlohmann::json;

void show_ranking();

void update_ranking(string current_player, int time);