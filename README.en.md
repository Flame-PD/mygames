# My Games

This is a collection of classic command-line games written in C++, featuring several fun mini-games.

## Game List

This project includes the following games:

### 1. 2048
A classic number puzzle game.
- **Objective**: Merge numbered tiles to reach 2048 or higher
- **Controls**: Use arrow keys to move tiles
- **Features**: Tracks high score and move count

### 2. UNO
A command-line version of the classic card game UNO.
- **Gameplay**: Match cards by color or number; first player to discard all cards wins
- **Features**: Supports multiple card types (+2, Reverse, Skip, +4, etc.)
- **Mode**: Supports two-player mode

### 3. Clock (Clock Solitaire)
A clock-themed solitaire card game.
- **Rules**: Move cards to designated clock positions in a specific order
- **Goal**: Successfully place all cards

### 4. Fly Bird
A flight-dodging game similar to "Angry Birds".
- **Gameplay**: Control a bird to avoid obstacles
- **Controls**: Press a key to ascend; release to descend
- **Features**: Multiple skin options available

## System Requirements

- C++ compiler (supporting C++11 or higher)
- Windows operating system (uses Windows API in the code)

## Compilation and Execution

Each game has its own source file and can be compiled and run individually:

```bash
g++ -o 2048.exe main/cpp/2048/2048.cpp
./2048.exe
```

Other games can be compiled and executed similarly.

## Controls

- **2048**: Use arrow keys to move tiles
- **UNO**: Follow on-screen prompts to select actions
- **Clock**: Follow game prompts to play
- **Fly Bird**: Press spacebar or arrow keys to control flight

## Project Structure

```
main/cpp/
├── 2048/2048.cpp      # 2048 game
├── UNO/UNO.cpp        # UNO game
├── clock/Clock.cpp    # Clock Solitaire game
└── flyingbird/Fly Bird.cpp  # Flying bird game
```

## License

This project is intended solely for learning and educational purposes.