# ncurses_snake

A small terminal Snake game written in C using [ncurses](https://invisible-island.net/ncurses/).

The snake moves around a 16×16 board. Eat the red snacks to grow, and avoid the
walls and your own tail. When the game ends, your score (snacks eaten) is printed
to the terminal.

## Requirements

- A C compiler (`gcc`)
- ncurses development headers
  - Arch: `sudo pacman -S ncurses`
  - Debian/Ubuntu: `sudo apt install libncurses-dev`
  - Fedora: `sudo dnf install ncurses-devel`
- A terminal with 256-color support (the game uses extended color indices)

## Building

```sh
make
```

This compiles `main.c` and produces `a.out`. Or build it by hand:

```sh
gcc main.c -lncurses
```

## Running

```sh
./a.out
```

### Controls

| Key | Action     |
|-----|------------|
| `w` | Move up    |
| `a` | Move left  |
| `s` | Move down  |
| `d` | Move right |
| `q` | Quit       |

The terminal runs in raw mode while the game is active, so use `q` to quit
(`Ctrl+C` is not handled).

## Project layout

| File             | Purpose                                                                 |
|------------------|-------------------------------------------------------------------------|
| `main.c`         | Entry point: ncurses setup, input handling, and the game loop           |
| `game_objects.c` | Board constants, `Snake`/`Segment`/`Snack` types, drawing and collision |
| `Makefile`       | Builds the game                                                         |

## Tweaking

- Board size: `WIDTH` and `HEIGHT` in `game_objects.c`
- Colors: `COLOR_FIELD`, `COLOR_SNAKE`, and `COLOR_SNACK` in `game_objects.c` (256-color indices)
- Speed: `frameTime.tv_nsec` in `main.c` (default 100 ms per frame)
