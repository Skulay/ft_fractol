*This project has been created as part of the 42 curriculum by alehamad.*

<div align="center">

# 🌀 fract-ol

**An interactive fractal explorer, written from scratch in C with the MiniLibX.**

![Language](https://img.shields.io/badge/language-C-00599C?style=flat-square&logo=c)
![School](https://img.shields.io/badge/school-42-000000?style=flat-square)
![Norm](https://img.shields.io/badge/norminette-passing-success?style=flat-square)
![Platform](https://img.shields.io/badge/platform-Linux-FCC624?style=flat-square&logo=linux&logoColor=black)
![Graphics](https://img.shields.io/badge/graphics-MiniLibX-8A2BE2?style=flat-square)

[Overview](#-overview) •
[Features](#-features) •
[Getting started](#-getting-started) •
[Controls](#-controls) •
[How it works](#-how-it-works) •
[Examples](#-examples) •
[Author](#-author)

<br>

<img src="assets/mandelbrot.png" alt="The Mandelbrot set rendered by fract-ol" width="600">

</div>

---

## 📖 Overview

**fract-ol** renders the **Mandelbrot**, **Julia** and **Burning Ship** sets in an 800×800 window and lets you explore them in real time: zoom towards the mouse, move around, change the precision and switch between colour palettes.

The goal of the project is to learn the basics of computer graphics and of the complex plane:

- how to map **screen pixels** to **complex numbers** and back
- how an **escape-time algorithm** decides whether a point belongs to a set
- how to draw into an **image buffer** instead of putting pixels one by one in a window
- how to react to **keyboard, mouse and window events** with an event loop

Everything is written in C (Norm-compliant) on top of our own `libft` and the school's **MiniLibX** (X11).

---

## ✨ Features

### Fractals

| Fractal | Formula | Parameters |
|---|---|---|
| **Mandelbrot** | `z₀ = 0`, `zₙ₊₁ = zₙ² + c`, with `c` = the pixel | none |
| **Julia** | `z₀` = the pixel, `zₙ₊₁ = zₙ² + c`, with `c` fixed | real and imaginary part of `c` |
| **Burning Ship** *(bonus)* | `zₙ₊₁ = (\|Re zₙ\| + i\|Im zₙ\|)² + c` | none |

A point is considered **out of the set** as soon as `|z|² > 4`, otherwise it is drawn in black after `max_iter` iterations.

### Rendering

| Feature | Details |
|---|---|
| Image buffer | Every frame is drawn into an MLX image, then pushed to the window in one call |
| Mouse zoom *(bonus)* | Zooms **towards the cursor**: the complex point under the mouse stays in place |
| Keyboard zoom | Zoom in / out around the centre of the window |
| Navigation *(bonus)* | Arrow keys move the view, the step scales with the zoom level |
| Iterations | Adjustable at runtime (default `50`, step `10`) to get more detail when zooming deep |
| Colour palettes *(bonus)* | 4 palettes, switchable at runtime, smooth gradient based on `iter / max_iter` |

### Argument parsing

| Check | Details |
|---|---|
| Fractal name | Must be exactly `mandelbrot`, `julia` or `burningship` |
| Argument count | 1 argument for Mandelbrot / Burning Ship, 3 for Julia |
| Julia parameters | Must be valid decimal numbers (`-0.8`, `+0.156`, `1`): no letters, no lonely `.`, no trailing garbage |
| Range | Julia parameters must stay within `[-40, 40]` |
| Error | Any invalid input prints the usage and exits with status `1` |

---

## 🚀 Getting started

### Requirements

- Linux with an X server (works under **WSL2 / WSLg**)
- `cc` / `gcc`
- `make`
- `git` and an internet connection on the first build (to fetch `libft` and the MiniLibX)
- X11 development headers

```bash
# Debian / Ubuntu
sudo apt install build-essential xorg libxext-dev libx11-dev zlib1g-dev libbsd-dev
```

### Build & run

```bash
git clone <repository-url> fractol
cd fractol
make
./fractol mandelbrot
```

> `libft` and `minilibx-linux` are not stored in this repository: on the first `make`, they are cloned automatically from [Skulay/libft](https://github.com/Skulay/libft) and [42Paris/minilibx-linux](https://github.com/42Paris/minilibx-linux).

### Usage

```
./fractol mandelbrot
./fractol julia <real> <imag>
./fractol burningship
```

### Make rules

| Rule | Action |
|---|---|
| `make` / `make all` | Clone `libft` and the MiniLibX if missing, build them, then `fractol` |
| `make clean` | Remove object files |
| `make fclean` | Remove object files, `libft.a` and the binary |
| `make distclean` | `fclean`, then delete the cloned `libft/` and `minilibx-linux/` |
| `make re` | `fclean` then `all` |

---

## 🎮 Controls

| Input | Action |
|---|---|
| 🖱️ Scroll up / down | Zoom in / out towards the cursor |
| <kbd>+</kbd> / <kbd>-</kbd> | Zoom in / out around the centre |
| <kbd>←</kbd> <kbd>→</kbd> <kbd>↑</kbd> <kbd>↓</kbd> | Move the view |
| <kbd>8</kbd> / <kbd>7</kbd> | Increase / decrease the number of iterations (±10) |
| <kbd>2</kbd> / <kbd>1</kbd> | Next / previous colour palette |
| <kbd>Esc</kbd> or ❌ | Close the window and quit cleanly |

---

## 🏗️ How it works

```
 argv ──► parsing ──► init (mlx, window, image) ──► render ──► mlx_loop
                                                      ▲            │
                                                      └── hooks ◄──┘
                                                   (keys, mouse, close)
```

### 1. Parsing — `src/parsing.c`

Checks the fractal name and the number of arguments, validates Julia's parameters with a small number checker (`valid_number`), then converts them with our own `ft_atod`.

### 2. Initialisation — `src/init.c`

All the state lives in a single struct:

```c
typedef struct s_data
{
    void        *mlx;        // MLX connection
    void        *win;        // window
    void        *img;        // off-screen image
    char        *addr;       // raw pixel buffer of the image
    int         bpp;
    int         line_len;
    int         endian;
    double      zoom;        // 1.0 = whole set visible
    double      offset_x;    // centre of the view (real axis)
    double      offset_y;    // centre of the view (imaginary axis)
    int         max_iter;
    int         type;        // MANDELBROT, JULIA or BURNSHIP
    int         color;       // palette index (0 → 3)
    t_complex   julia_c;     // constant c for Julia
}   t_data;
```

### 3. Pixel ↔ complex mapping

Each pixel `(x, y)` is converted to a point of the complex plane using the current zoom and offset:

```c
re = (x - WIDTH  / 2.0) / (0.5 * zoom * WIDTH)  + offset_x;
im = (y - HEIGHT / 2.0) / (0.5 * zoom * HEIGHT) + offset_y;
```

With `zoom = 1`, the window covers `[-2, 2]` on both axes.

### 4. Escape-time algorithm — `src/mandelbrot.c`, `src/julia.c`, `src/burningship.c`

For every pixel, the sequence `z → z² + c` is iterated until `|z|² > 4` or `max_iter` is reached. The number of iterations is the only thing the renderer needs.

### 5. Colouring — `src/color.c`

The iteration count is normalised to `t = iter / max_iter ∈ [0, 1]`, then turned into an RGB value by one of four palettes (polynomial gradient, red/blue, green/cyan, two-step blend). Points inside the set are black.

### 6. Events — `src/hook.c`

`mlx_hook` registers three handlers:

- **key press** → move, zoom, change iterations or palette, quit
- **mouse button** → zoom while keeping the point under the cursor fixed
- **window close (`DestroyNotify`)** → free everything and exit

After each change the whole image is redrawn and pushed to the window.

### 7. Clean up — `src/utils.c`

`close_window` destroys the image, the window and the display, then frees the struct, so the program exits without leaks.

---

## 📂 Project structure

```
.
├── assets/
│   └── mandelbrot.png       # screenshot used in this README
├── ft_fractol.h             # all types, constants and prototypes
├── libft/                   # our own C library, cloned by make (not versioned here)
├── minilibx-linux/          # MiniLibX, cloned by make (not versioned here)
├── makefile
└── src/
    ├── main.c               # entry point, hooks, mlx_loop
    ├── parsing.c            # argument checks
    ├── init.c               # struct, mlx, window and image creation
    ├── render.c             # dispatch to the right fractal
    ├── mandelbrot.c         # Mandelbrot set
    ├── julia.c              # Julia sets
    ├── burningship.c        # Burning Ship
    ├── color.c              # colour palettes
    ├── hook.c               # keyboard and mouse handlers
    └── utils.c              # put_pixel, ft_atod, clean up
```

---

## 💻 Examples

```bash
./fractol mandelbrot

# A few nice Julia sets
./fractol julia -0.8 0.156
./fractol julia -0.4 0.6
./fractol julia 0.285 0.01
./fractol julia -0.7269 0.1889

./fractol burningship
```

Invalid input prints the usage:

```console
$ ./fractol julia abc 0.5
Usage:
  ./fractol mandelbrot
  ./fractol julia <real> <imag>
  ./fractol burningship
Exemples:
  ./fractol julia -0.8 0.156
$ echo $?
1
```

---

## 🧪 Testing

- invalid arguments (wrong name, wrong count, `1.`, `.5`, `--1`, `1e3`, huge values)
- deep zooms with high iteration counts to check precision and responsiveness
- closing with <kbd>Esc</kbd> and with the window's ❌ button
- `valgrind` for leaks:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./fractol mandelbrot
```

*(The X11 libraries keep some memory of their own, only leaks coming from our code count.)*

---

## 📚 Resources

- [MiniLibX documentation (harm-smits)](https://harm-smits.github.io/42docs/libs/minilibx)
- [Mandelbrot set — Wikipedia](https://en.wikipedia.org/wiki/Mandelbrot_set)
- [Julia set — Wikipedia](https://en.wikipedia.org/wiki/Julia_set)
- [Burning Ship fractal — Wikipedia](https://en.wikipedia.org/wiki/Burning_Ship_fractal)
- [Plotting algorithms for the Mandelbrot set](https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set)

---

## 👤 Author

| | Login | Main areas |
|---|---|---|
| 🧑‍💻 | **alehamad** | Everything: parsing, rendering, fractals, colours, events |

<div align="center">

*Made with ☕ at 42*

</div>
