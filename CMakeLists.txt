cmake_minimum_required(VERSION 3.20)

project(terminal-maze LANGUAGES CXX)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(maze
    src/game.cpp
    src/main.cpp
    src/maze.cpp
    src/menu.cpp
    src/ranking.cpp
    src/utilities.cpp
    src/username.cpp
)

target_include_directories(maze PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
)

FetchContent_Declare(
    nlohmann_json
    URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(nlohmann_json)

target_link_libraries(maze PRIVATE nlohmann_json::nlohmann_json)

# Run build.py to download PDCurses and build it
if (WIN32)
    set(PDCURSES_ROOT "${CMAKE_SOURCE_DIR}/third_party/PDCurses")
    target_include_directories(maze PRIVATE "${PDCURSES_ROOT}")
    target_link_libraries(maze PRIVATE "${PDCURSES_ROOT}/wincon/pdcurses.a")
else()
    set(CURSES_NEED_NCURSES TRUE)
    set(CURSES_NEED_WIDE TRUE)
    find_package(Curses REQUIRED)
    target_include_directories(maze PRIVATE ${CURSES_INCLUDE_DIRS})
    target_link_libraries(maze PRIVATE ${CURSES_LIBRARIES})
endif()