# Terminal Maze
A terminal-based game to solve mazes, written in C++. 
Developed and targeted for Windows on amd64 architectures.

## Build and dependencies
Place the following libraries inside the `terminal-maze/third_party` directory:
- Version 3.9 of [PDCurses](https://pdcurses.org) (must be built before).
- Version 3.12.0 of [JSON for Modern C++](https://json.nlohmann.me/).

Make sure you have cmake and a C++20 compiler installed on your system. 

Build with the following commands:

```bash
cmake -S . -B build
cmake --build build
./build/maze.exe
```

## Error Codes
The program uses `exit()` to stop when critical errors occur.
- `exit(1)`: Failed to initialize curses.
- `exit(2)`: Unable to create username acquisition window.
- `exit(3)`: Unable to get username `std::string`.
- `exit(4)`: Unable to create game window.

## License
This project is licensed under the **MIT License**. See the `LICENSE` folder for the full license text.

### Third-Party Libraries
This project uses the following open-source libraries:
- **PDCurses:** Released under the Public Domain.
- **JSON for Modern C++ (nlohmann/json):** MIT License. *(Note: Contains sub-components licensed under MIT, CC0-1.0, and Apache 2.0).*