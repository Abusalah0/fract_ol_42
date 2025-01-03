Here's a detailed README template for your `fract_ol` project:

---

# fract_ol

## Overview

`fract_ol` is a graphical program that allows users to visualize various fractals, such as the Mandelbrot set, Julia set, and other popular fractals. The program leverages the MiniLibX graphics library for rendering and user interaction. This project demonstrates a fundamental understanding of fractal mathematics, computer graphics, and the usage of the MiniLibX library for graphical applications.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Supported Fractals](#supported-fractals)
- [Code Structure](#code-structure)
- [Equations](#equations)
- [Contributing](#contributing)
- [License](#license)

## Installation

### Prerequisites

- A Unix-based system (Linux, macOS, or similar)
- MiniLibX library installed (Typically provided with 42 projects)
- GCC (GNU Compiler Collection) for compiling C code

### Steps

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/fract_ol.git
   cd fract_ol
   ```

2. Compile the project:
   ```bash
   make
   ```

3. Run the program:
   ```bash
   ./fract_ol
   ```

   This will launch the fractal viewer, allowing you to interact with the various fractals.

## Usage

After running the program, you will see a window with a graphical representation of a fractal. You can interact with the fractal using the following controls:

- **Zoom in:** Use the mouse scroll wheel or press the `+` key.
- **Zoom out:** Use the mouse scroll wheel or press the `-` key.
- **Move view:** Click and drag to move the fractal view around.
- **Change fractal:** Use the arrow keys to switch between supported fractals.
- **Exit:** Press `ESC` or close the window.

## Supported Fractals

The following fractals are supported by `fract_ol`:

- **Mandelbrot Set**: A set of complex numbers that produces a famous fractal.
- **Julia Set**: A family of fractals that are closely related to the Mandelbrot set.
- **Burning Ship**: A fractal that is similar to the Mandelbrot set but with a different mathematical formulation.
- **Additional fractals (if applicable)**: [Describe any other fractals supported by your project].

## Equations

Here are the key mathematical equations used to generate the fractals:

### Mandelbrot Set

For a complex number `C = a + bi`, the Mandelbrot set is defined as the set of complex numbers `C` for which the function:

\[
f(z) = z^2 + C
\]

does not diverge when iterated from `z = 0`. The iteration continues until a maximum number of iterations is reached or the absolute value of `z` exceeds a threshold.

### Julia Set

For a complex number `C = a + bi` and a point `Z = x + yi`, the Julia set is defined by the equation:

\[
f(Z) = Z^2 + C
\]

where `C` is constant, and `Z` is iterated.

### Burning Ship

Similar to the Mandelbrot set, but the equation for the Burning Ship fractal is:

\[
f(Z) = (Re(Z)^2 - Im(Z)^2 + a) + (2 * |Re(Z) * Im(Z)| + b)i
\]

This equation creates a fractal that looks similar to the Mandelbrot set, but with a different shape.

## Contributing

Contributions are welcome! If you have ideas for new features, improvements, or bug fixes, please fork the repository and submit a pull request. Make sure to include tests and follow the coding standards.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

This template includes details on installation, usage, the mathematical equations, and general structure. You can adapt it further depending on your implementation and any additional features you may have.
