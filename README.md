# Solar-System-in-C

A simple OpenGL simulation of the solar system written in C. This project visualizes the Sun and planets with approximate relative sizes, orbits, and colors. Please note that the colors and motion are **not 100% scientifically accurate**, but provide a visually appealing representation.

## Features

- Renders Sun and 9 planets (including Pluto) with textured spheres.
- Background stars with slight motion effect.
- Saturn ring implemented.
- Smooth camera orbit around the solar system.

## Requirements

Tested on **Ubuntu 24.04.3**. You need to have OpenGL development libraries and build tools installed.
```bash
# 1. Install required dependencies
sudo apt update
sudo apt install build-essential cmake git libglu1-mesa-dev libglew-dev libglfw3-dev libxi-dev
```

## Quick Start

Follow these steps to get the simulation running on Ubuntu 24.04.3:

1. **Download the project**

    You can either download the ZIP from GitHub or use `git`:
   ```bash
   git clone https://github.com/IconsNotFound/Solar-System-in-C.git
   ```

2. **Navigate to the project folder**

    Open a terminal at the root of the project:
    ```bash
    cd Solar-System-in-C
    ```

3. **Install required dependencies:**

    (See [Requirements](#requirements) for full instructions)

4. **Build and run the simulation:**

    ```bash
    gcc main.c -o solar_system_in_c -lglfw -lGLEW -lGL -lGLU -lm -ldl -lX11 -lpthread -lXrandr -lXi &&
    ./solar_system_in_c
    ```

## One-liner (download + install + build + run)

```bash
git clone https://github.com/IconsNotFound/Solar-System-in-C.git &&
cd Solar-System-in-C &&
sudo apt update &&
sudo apt install -y build-essential cmake git libglu1-mesa-dev libglew-dev libglfw3-dev libxi-dev &&
gcc main.c -o solar_system_in_c -lglfw -lGLEW -lGL -lGLU -lm -ldl -lX11 -lpthread -lXrandr -lXi &&
./solar_system_in_c
```

## Notes

- The simulation prioritizes visual appeal over scientific accuracy.
- The Sun is the brightest object and planets have approximate relative sizes.
- Stars have a subtle motion effect to create depth.

## License

This project is released under the MIT License.
