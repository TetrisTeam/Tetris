Tetris
======

__@NikolaDimitroff: We made the project at home so almost all of the code was uploaded from a single GitHub account.__

__UPDATE: Don't mind my recent commits.__

Course assignment for Introduction to Programming class @ FMI, SU.

General
------------------------
In the TETRIS source, both our variables and functions are in camel case, for example `WindowWidth`, `CheckIfFull`, etc..

The game logic lies in Tetris.cpp. 

We have taken advantage of the object oriented nature of C++. Each shape has its own dedicated class, extending `BlockBase` - `ZBlock`, `TBlock`, `LBlock`, `LineBlock` and `SquareBlock`.

`Environment` is used as a context with information about the main screen, which to pass to the block objects in order to retrieve information for window size and the screen matrix.

As for background music, we used Windows' beeping functionality to recreate the original TETRIS theme!

More thorough description
------------------------
In `Tetris` we have 2 matrices - `ScreenMatrix` and `PrevScreenMatrix`. In `ScreenMatrix` we store numbers, indicating the color of each cell, 0 if the cell is empty or -1 if the ghost block is there. And in `PrevScreenMatrix` we store the last state of `ScreenMatrix` so we can draw on each frame only the difference between the two, to optimize performance.

Each block (L-Block, Z-Block, etc.) consists of several cells. They are defined in their corresponding class definitions via a 3x3 matrix with 1 indicating a cell of the block and 0 indicating empty space. We chose it to be 3x3 to make it easier to realize collision detection (in `BlockBase`).

Collision detection is rather basic, it checks each of the block's cells to determine whether there is something beneath it (which is NOT a cell of the same block). If yes - several checks are made, including whether the blocks are stacked way too high (in which case a GAME OVER! message is shown) and whether they form a full row (in which case the row turns gray and 40 points are given to the player).

The background music, defined in `BackgroundMusic`, starts a new thread with the start of the console app and runs for the whole lifecycle of the application. It is essentially an infinite loop, calling Beep with different arguments to simulate the original TETRIS theme.
