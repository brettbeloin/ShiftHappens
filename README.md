# ShiftHappens

ShiftHappens is an interactive C++ educational command-line game engineered to bridge the gap between abstract binary logic and practical programmatic execution. Instead of forcing developers to memorize static truth tables or dry operator charts, ShiftHappens gamifies bitwise mathematics, allowing players to manipulate numbers directly at the bit level to build an intuitive, long-lasting mental model of low-level data transformation.

By presenting live, immediate hexadecimal and binary visual representations alongside real-time calculations, the application trains the player's brain to parse shifts, logical masks, and gate evaluations seamlessly. Whether you are optimizing a high-performance rendering pipeline, working on embedded systems, cracking assembly instructions, or simply drilling for technical interviews, ShiftHappens turns foundational bitwise logic into muscle memory.

## Build the Project
```bash
git clone git@github.com:brettbeloin/ShiftHappens.git
cd ShiftHappens
cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build
./build/bitGame
```

## Project Roadmap

### Completed Features
- [x] Functional decomposition into dedicated translation units (`bit.cpp`, `game.cpp`, `game.hpp`).
- [x] Cohesive state management via object-oriented architecture (`Game` class).
- [x] Robust, stream-isolated console input parsing using `std::getline` and `std::istringstream`.
- [x] Live visual binary display utilizing `std::bitset<8>` format.
- [x] Standard operational modes for Left Shift (`<<`), Right Shift (`>>`), Bitwise AND (`&`), and Bitwise OR (`|`).

### Future Development Pipeline
- [ ] **Random Gameplay Mode**: Selecting randomized operational modes (`<<`, `>>`, `&`, `|`) with mathematically safe bounds across the 8-bit unsigned range (0-255).
- [ ] **Difficulty Selection**: Dynamic parameter configurations ranging from Easy (8-bit bounded constraints) up to Hard modes utilizing 64-bit integer tracking fields.
- [ ] **Unit Testing Framework**: Structural verification tests to assert boundary rules and algorithmic computations.
- [ ] **Graphical User Interface (GUI)**: Migrating the console-driven engine to a decoupled frontend layout utilizing an active graphics abstraction context.
