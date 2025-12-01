
<p align="center">
  <img src="https://github.com/user-attachments/assets/5a240706-b07e-4cd8-be5e-ded9cf71fdad" alt="animated" />
</p>

# Cub3D: A 3D Maze Exploration Game 🕹️

This project is a 3D maze exploration game implemented using the MiniLibX graphics library. It allows players to navigate a maze, rendered in 3D, using keyboard input. The game features textured walls, ceilings, and floors, as well as basic player movement and perspective.

## 🚀 Key Features

*   **3D Maze Rendering:** Renders a 3D representation of a maze using raycasting techniques.
*   **Textured Environment:** Supports textured walls, ceilings, and floors for a more immersive experience.
*   **Player Movement:** Allows players to move forward, backward, left, and right within the maze.
*   **View Control:** Enables players to rotate their view left and right, as well as look up and down.
*   **Collision Detection:** Prevents players from walking through walls.
*   **XPM Sprite Loading:** Loads textures and sprites from XPM files.
*   **Event Handling:** Responds to keyboard input for player control.
*   **Dynamic Image Scaling:** Scales images dynamically for rendering sprites at different sizes.

## 🛠️ Tech Stack

*   **Language:** C
*   **Graphics Library:** MiniLibX (MLX)
*   **Operating System:** Linux (designed for Linux, may require modifications for other OS)
*   **Image Format:** XPM (X PixMap)
*   **Build System:** Make
*   **Dependencies:** X11, Xext libraries

## 📦 Getting Started

Follow these instructions to get the game up and running on your local machine.

### Prerequisites

*   A Linux-based operating system.
*   The X11 and Xext libraries installed. These are usually available through your distribution's package manager (e.g., `apt-get install libx11-dev libxext-dev` on Debian/Ubuntu).
*   clang-12
*   Make

### Installation

1.  Clone the repository:

    ```bash
    git clone <repository_url>
    cd <repository_directory>
    ```

2.  Compile the code:

    ```bash
    make
    ```
    This will create an executable file named `cub3D`.

### Running Locally

1.  Run the executable:

    ```bash
    ./cub3D <map_file.cub>
    ```

    Replace `<map_file.cub>` with the path to your map file.  A sample map file should be included in the repository.

## 💻 Usage

Once the game is running, use the following keys to control the player:

*   **W:** Move forward
*   **S:** Move backward
*   **A:** Move left
*   **D:** Move right
*   **Left Arrow:** Rotate left
*   **Right Arrow:** Rotate right
*   **Up Arrow:** Look up
*   **Down Arrow:** Look down
*   **Shift:** Sprint

## 📝 License

This project is licensed under the [MIT License](LICENSE) - see the `LICENSE` file for details.

Thanks for checking out this project! I hope you find it interesting and/or useful.
