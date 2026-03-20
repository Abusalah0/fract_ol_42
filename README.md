# fract_ol (fractol)

A MiniLibX fractal explorer written in C, featuring Mandelbrot, Julia, and Burning Ship sets with interactive zoom/pan controls.

## Table of Contents

- [1. What this project does](#1-what-this-project-does)
- [2. Quick start](#2-quick-start)
- [3. Usage](#3-usage)
- [4. Controls](#4-controls)
- [5. Fractal math](#5-fractal-math)
- [6. How rendering works in this codebase](#6-how-rendering-works-in-this-codebase)
- [7. Project structure](#7-project-structure)
- [8. Pictures](#8-pictures)
- [9. Troubleshooting](#9-troubleshooting)
- [10. Possible improvements](#10-possible-improvements)

## 1. What this project does

This program renders escape-time fractals in real time:

- Mandelbrot
- Julia
- Burning Ship

It maps each screen pixel to a point in the complex plane, iterates the fractal recurrence, and colors the pixel based on the number of iterations before divergence.

## 2. Quick start

### Requirements

- Linux
- `cc` with standard C support
- X11 development libraries
- MiniLibX (Linux flavor)

### Build

```bash
make
```

This builds:

- local `libft` static library
- executable `fractol`

### Run

```bash
./fractol mandelbrot
./fractol julia
./fractol burning_ship
```

## 3. Usage

The program expects exactly one argument:

```bash
./fractol <fractal_name>
```

Valid names:

- `mandelbrot`
- `julia`
- `burning_ship`

If the argument is missing or invalid, the program prints the accepted fractal names and exits.

## 4. Controls

### Keyboard

- `Arrow Left` / `Arrow Right`: pan horizontally
- `Arrow Up` / `Arrow Down`: pan vertically
- `Esc`: close window and exit

### Mouse

- `Scroll Up`: zoom in
- `Scroll Down`: zoom out
- `Left Click` (Julia only): set Julia constant from mouse position

Notes:

- Pan step scales with zoom: movement gets finer as you zoom in.
- Zoom is centered around the mouse cursor position.

## 5. Fractal math

All three fractals use an iterative map in the complex plane and the same escape radius check:

$$
|z_n|^2 = \operatorname{Re}(z_n)^2 + \operatorname{Im}(z_n)^2 > 4
$$

If a point does not escape before `MAX_ITER`, it is treated as inside the set and drawn black.

### Mandelbrot

Recurrence:

$$
z_{n+1} = z_n^2 + c
$$

In this implementation, the initial value is set as:

$$
z_0 = c
$$

Then iterate until escape or max iterations.

### Julia

Recurrence:

$$
z_{n+1} = z_n^2 + k
$$

- $z_0$ is the mapped pixel coordinate.
- $k$ is a constant (`julia_re`, `julia_im`), initialized to:
   - $k_r = -0.512511498387847167$
   - $k_i = 0.521295573094847167$

For Julia mode, left click updates $k$ from the cursor point to explore different Julia shapes interactively.

### Burning Ship

Recurrence:

$$
z_{n+1} = (|\operatorname{Re}(z_n)| + i|\operatorname{Im}(z_n)|)^2 + c
$$

Absolute values before squaring create the characteristic "ship" geometry.

### Coloring (escape-time gradient)

For iteration ratio $t = \frac{\text{iter}}{\text{max\_iter}}$, RGB is computed with polynomial curves:

$$
R = 9(1-t)t^3 \cdot 255
$$

$$
G = 15(1-t)^2 t^2 \cdot 255
$$

$$
B = 8.5(1-t)^3 t \cdot 255
$$

Then packed as `(R << 16) | (G << 8) | B`.

## 6. How rendering works in this codebase

High-level loop:

1. Validate CLI input and choose fractal type.
2. Initialize fractal parameters (`zoom`, shifts, iteration limit, Julia constant).
3. Initialize MLX context, window, image buffer.
4. For each pixel `(x, y)`, map to complex plane:

$$
c_r = \frac{(x - W/2)\cdot4}{W\cdot zoom} + shift_x
$$

$$
c_i = \frac{(y - H/2)\cdot4}{W\cdot zoom} + shift_y
$$

5. Compute iteration count using selected fractal function.
6. Convert count to color and write into image buffer.
7. Blit image to window.
8. Re-render whenever keyboard or mouse events modify fractal state.

Implementation detail:

- The buffer write uses `data[y * WIDTH + x]`, so the image is treated as a linear pixel array in row-major order.

## 7. Project structure

- `src/main.c`: app entry, hooks registration, MLX loop
- `src/init_program.c`: input validation and state initialization
- `src/fractals.c`: Mandelbrot, Julia, Burning Ship iteration + per-frame render pass
- `src/color.c`: escape-time gradient mapping
- `src/key_events.c`: keyboard pan/exit, mouse zoom, Julia parameter update
- `src/error_handling.c`: cleanup and fatal error helpers
- `include/fract_ol.h`: shared types, constants, function prototypes
- `libft/`: utility library used by the project
- `Makefile`: build rules for `libft` + main executable

## 8. Pictures

Add your screenshots to a folder like `assets/screenshots/` and update paths below.

Example gallery block:

```md
### Mandelbrot
![Mandelbrot](assets/screenshots/mandelbrot.png)

### Julia (interactive constant)
![Julia](assets/screenshots/julia.png)

### Burning Ship
![Burning Ship](assets/screenshots/burning_ship.png)
```

Suggested capture ideas:

- Mandelbrot: full set and a deep zoom around mini-brots
- Julia: 3-4 different constants selected by click
- Burning Ship: full structure and one zoomed flame-like area

## 9. Troubleshooting

- Build fails with missing `mlx.h`:
   - Make sure MiniLibX headers/libs are installed and visible to compiler/linker.
- Window does not open on Linux:
   - Verify X11 is available (`-lX11 -lXext` are linked in this Makefile).
- Program exits immediately:
   - Check argument spelling (`mandelbrot`, `julia`, `burning_ship`).

## 10. Possible improvements

- Increase/decrease iteration limit at runtime
- Add color palettes and palette cycling
- Add reset view shortcut
- Preserve aspect ratio mapping explicitly for non-square windows
- Optional smooth coloring (normalized iteration)
