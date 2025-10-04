# Terminal maze
Terminal game that uses [Wilson's algorithm](https://www.cs.cmu.edu/~15859n/RelatedWork/RandomTrees-Wilson.pdf) to generate unbiased mazes.

## Dependencies
In folder ```terminal-maze/third_party```, provide the following libraries:
- [PDCurses](https://pdcurses.org) 3.9
- [JSON for Modern C++](https://json.nlohmann.me/) 3.12.0

## Build requirements
- CMake (>= 3.20 recommended)
- A C++20-compatible compiler

## Build
```
cmake -S . -B build
cmake --build build
./build/maze.exe
```

## To-do
- Update CMake in order to make it use a package manager that automatically downloads the required dependencies (in ```./third-party```).