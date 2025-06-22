# Sudoku Puzzle Game

This project implements a classic Sudoku number-placement puzzle game with a user-friendly graphical interface. The objective of Sudoku is to fill a $9\times9$ grid with digits so that each column, each row, and each of the nine $3\times3$ subgrids (also called "boxes", "blocks", or "regions") contain all of the digits from 1 to 9. The game provides a partially completed grid, and for a well-posed puzzle, there is a single solution.

## Features

* **Classic $9\times9$ Sudoku Grid:** Adheres to the standard Sudoku rules.
* **Difficulty Selection:** Allows players to choose between Easy, Medium, and Hard difficulties, which affects the number of pre-filled cells.
* **Game Timer:** Tracks the player's time during gameplay.
* **Input Validation:** The game checks for valid solutions upon completion (win/lose messages).
* **High Score Tracking:** Saves and displays high scores.
* **Game State Management:**
    * **Play/Pause:** Start a new game or resume an existing one.
    * **Continue Game:** Loads saved game progress to resume a previous session.
    * **Quit Game:** Saves current progress before exiting.
* **Intuitive GUI:** Built using the powerful Qt framework for a responsive and visually appealing experience.

## How to Play

1.  **Start the Game:** Upon launching, you'll likely be presented with a home or play screen. Click the "Play" button to proceed.
2.  **Select Difficulty:** Choose your desired difficulty (Easy, Medium, or Hard).
3.  **Fill the Grid:**
    * The game board will appear with some cells already filled.
    * Your goal is to fill the empty cells with digits from 1 to 9.
    * **Rules:**
        * Each row must contain all digits from 1 to 9, without repetition.
        * Each column must contain all digits from 1 to 9, without repetition.
        * Each of the nine $3\times3$ blocks (marked out in the grid) must contain all digits from 1 to 9, without repetition.
4.  **Complete and Check:** Once you believe you have filled all cells, click the "Done" button to check your solution. The game will inform you if you won or lost, and update high scores.
5.  **Save/Quit/Continue:** Use the "Quit" button to save your game and exit, or the "Continue" button to load a previously saved game.
6.  **View Stats:** Check the "Stats" screen to see the recorded high scores.

## Technologies Used

This project's graphical user interface (GUI) is developed using:

* **Qt GUI Framework:** A comprehensive cross-platform development toolkit for creating visually appealing and interactive applications.

## Prerequisites

To build and run this project, you will need:

* **Qt Development Environment:** This includes the Qt framework itself and a compatible compiler (e.g., MinGW on Windows, GCC/Clang on Linux/macOS).

    A good guide for setting up Qt (including MinGW compiler) can be found in the first 10 minutes of this YouTube video:
    [https://youtu.be/Wi9nQTDFF4U](https://youtu.be/Wi9nQTDFF4U)

## Installation and Setup

1.  **Clone the Repository:**
    ```bash
    git clone <your-repository-url>
    cd sudoku-project-folder
    ```
2.  **Install Qt:** Follow the instructions in the prerequisite section to install the Qt development environment on your system.
3.  **Open the Project in Qt Creator:**
    * Launch Qt Creator (the IDE that comes with Qt).
    * Go to `File > Open File or Project...`
    * Navigate to the cloned repository and select the `.pro` (Qt project file) associated with this Sudoku game.
4.  **Configure for Your Device:**
    * Once the project is open, Qt Creator will likely prompt you to configure the project for your build environment (e.g., selecting your compiler kit). Follow the prompts to configure it appropriately.
5.  **Build and Run:**
    * After configuration, you can build the project by going to `Build > Build Project "Sudoku"` (or press `Ctrl+B` / `Cmd+B`).
    * Once built successfully, you can run the application by going to `Build > Run` (or press `Ctrl+R` / `Cmd+R`).

## Project Structure (Conceptual)

While the exact file structure is not provided, a typical Qt project would likely include:

* `.pro` file: The Qt project file, configuring the build process.
* `.h` files: Header files for C++ classes (e.g., `sudokugrid.h`, `mainwindow.h`).
* `.cpp` files: Source files for C++ class implementations.
* `.ui` files: Qt Designer UI files defining the layout and widgets.
* `main.cpp`: The entry point of the application.

## Core Functions Overview

The game logic is primarily driven by the following key functions (or "slots" in Qt terminology):

* `difficultySelected()`: Triggered by difficulty buttons (Easy, Medium, Hard). Sets up and displays the initial grid.
* `showTime()`: Updates the game timer display (called by a timer).
* `on_playButton_clicked()`: Switches to the difficulty selection screen.
* `on_doneButton_clicked()`: Checks the solution, displays win/lose messages, updates, and saves high scores.
* `on_gameGrid_cellChanged()`: Updates internal game data when a cell value is changed by the player.
* `on_quitButton_clicked()`: Saves game progress and prompts for confirmation before quitting.
* `on_continueButton_clicked()`: Loads saved game progress and resumes play.
* `on_completeHomeButton_clicked()` / `on_completeStatsButton_clicked()`: Switches to the home and stats screens, respectively.
* `on_statsButton_clicked()`: Reads and displays high scores on the stats screen.

