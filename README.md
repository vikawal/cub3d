# cub3D - My First RayCaster

cub3D is a project inspired by the classic **Wolfenstein 3D**, the first-ever FPS game developed by id Software. This project delves into the fundamentals of ray casting, allowing you to create a dynamic 3D maze exploration experience. The goal is to implement a realistic first-person perspective inside a maze using C and the **MLX42** library.

---

## Features

- **3D Rendering**: A dynamic, first-person view of a maze created using ray casting principles.
- **Smooth Window Management**: Seamless handling of focus changes, minimizing, and more.
- **Textures**: North, South, East, and West wall textures, configurable via the `.cub` file.
- **Customizable Colors**: Floor and ceiling colors are fully adjustable.
- **Player Controls**:
  - **Movement**: Navigate the maze using `W`, `A`, `S`, `D`.
  - **Look Around**: Use arrow keys to look left and right.
  - **Exit**: Quit the program using `ESC` or the window's close button.

---

## Prerequisites

- **MLX42**: This project uses the **MLX42** library for graphical rendering. Please ensure the library is properly installed on your system. Visit the [MLX42 documentation](https://github.com/codam-coding-college/MLX42) for installation instructions.
- **C Compiler**: A compiler such as `gcc` with `-Wall`, `-Wextra`, and `-Werror` flags.
- **Math Library**: The project links against the math library (`-lm`).

---
