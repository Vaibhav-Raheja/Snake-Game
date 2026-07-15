# Snake Game

A classic Snake game written in C++ using the WinBGIm graphics library, built as a Code::Blocks project.

![C++](https://img.shields.io/badge/language-C%2B%2B-blue.svg)
![WinBGIm](https://img.shields.io/badge/graphics-WinBGIm%20(graphics.h)-orange.svg)
![Code::Blocks](https://img.shields.io/badge/build-Code%3A%3ABlocks%20%2F%20gcc-lightgrey.svg)
![Platform](https://img.shields.io/badge/platform-Windows-informational.svg)

## Overview

This is a console/graphics-window implementation of the classic Snake game. The player steers a growing snake around a bordered arena, eating apples to increase their score while avoiding the walls. The game renders with the Borland-style `graphics.h` API (via the WinBGIm library) and reads keyboard input directly through the Windows API (`GetAsyncKeyState`).

## Features

- Real-time snake movement in four directions
- Randomly spawning apples with collision-based "eating" detection
- Score tracking, displayed live in the game window
- Wall-collision game-over detection
- Post-game menu to restart or exit
- Debug and Release build targets (Code::Blocks project)

## Controls

| Key           | Action              |
|---------------|----------------------|
| Arrow Up      | Move up              |
| Arrow Down    | Move down            |
| Arrow Left    | Move left            |
| Arrow Right   | Move right           |
| Space         | Start the game       |
| `1` (at Game Over prompt) | Restart |
| `2` (at Game Over prompt) | Exit    |

## Build & Run

This project targets **Windows** and depends on the **WinBGIm** graphics library (the `graphics.h` / `initwindow`, `bar`, `circle`, `outtextxy` API), plus the Windows API for key polling (`GetAsyncKeyState`). It will not build as-is on Linux/macOS without porting to a cross-platform graphics library.

### Option A — Code::Blocks (recommended, matches the included project file)

1. Install [Code::Blocks](https://www.codeblocks.org/) with the bundled MinGW/gcc toolchain.
2. Install the WinBGIm library and header (`graphics.h`) into your compiler's `include`/`lib` directories. TODO: confirm exact WinBGIm version/source used originally.
3. Open `Snake.cbp` (the project file — note it is checked in under the name `Snake.cpp`; TODO: rename to `Snake.cbp` for clarity) in Code::Blocks.
4. Build the **Debug** or **Release** target (`Build > Build`).
5. Run the produced executable from `bin/Debug/Snake.exe` or `bin/Release/Snake.exe`.

### Option B — Command line (MinGW/gcc on Windows)

```
g++ main.cpp -o Snake.exe -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
Snake.exe
```

Flags used by the project's own build configuration: `-Wall -fexceptions` (both targets), `-g` (Debug), `-O2` and linker `-s` (Release).

## Gameplay

`TODO: add a gameplay screenshot or GIF here (docs/gameplay.gif)`

## Tech Stack

- **Language:** C++
- **Graphics:** WinBGIm (`graphics.h`, Borland BGI-style API)
- **Input:** Windows API (`GetAsyncKeyState`)
- **Build system:** Code::Blocks project (gcc/MinGW)

## Project Structure

```
main.cpp     # Game source (entry point, game loop, rendering, input)
Snake.cbp    # Code::Blocks project file (checked in as "Snake.cpp")
```

## Author

**Vaibhav Raheja** ([@Vaibhav-Raheja](https://github.com/Vaibhav-Raheja))
