cmake_minimum_required(VERSION 3.20)

project(terminal-maze LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(maze
    src/wilson.cpp
    src/game.cpp
    src/main.cpp
    src/menu.cpp
    src/ranking.cpp
    src/utilities.cpp
    src/username.cpp
    )

set(PDCURSES_ROOT "${CMAKE_SOURCE_DIR}/third_party/PDCurses")
set(NLOHMANN_ROOT "${CMAKE_SOURCE_DIR}/third_party/nlohmann")

target_include_directories(maze PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
    "${PDCURSES_ROOT}"
    "${NLOHMANN_ROOT}"
)
target_link_libraries(maze PRIVATE "${PDCURSES_ROOT}/wincon/pdcurses.a")