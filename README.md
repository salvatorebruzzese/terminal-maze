# Terminal Maze

A terminal-based game to solve mazes, written in C++.
Developed and targeted for Windows and Linux on AMD64 architectures.

## Build and dependencies

Make sure you have installed on your system:

- The GCC C++ Compiler.
- CMake.
- A Python interpreter.

Build with the following command:

```bash
python build.py
```

## Error Codes
The program uses `exit()` to stop when critical errors occur.

- `exit(1)`: Failed to initialize curses.
- `exit(2)`: Unable to create username acquisition window.
- `exit(3)`: Unable to get username `std::string`.
- `exit(4)`: Unable to create game window.

## License

This project is licensed under the **MIT License**.

### Third-Party Libraries

This project uses the following open-source libraries:

- **PDCurses:** Released under the Public Domain.
- **JSON for Modern C++ (nlohmann/json):** MIT License. *(Note: Contains sub-components licensed under MIT, CC0-1.0, and Apache 2.0).*