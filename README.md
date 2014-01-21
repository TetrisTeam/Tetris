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

`Environment` is used as a context with information about the main screen, which to pass to the block objects in order to retrieve information for window size, HANDLE and the screen matrix.

As for background music, we used Windows' beeping functionality to recreate the original TETRIS theme!

More thorough description
------------------------
In TETRIS drawing is extremely optimized for maximum efficiency. At most two blocks are drawn at every given time (active block and the ghost block indicating its landing position). 

Each block (L-Block, Z-Block, etc.) consists of several cells. Blocks are defined in their corresponding class definitions via a matrix with 1 indicating a cell of the block and 0 indicating empty space. The matrix is a dynamic 2-dimensional array, allowing it to wrap each figure in accordance to its size.

Collision detection was recently optimized for best performance with less code! We defined a boolean matrix called `CollisionMatrix`. All of the inactive blocks are 'transfered' to `CollisionMatrix` and then each new falling block can be easily tested against the matrix for overlapping. Should one occur, the block is returned to its previous position.

When a block hits the ground, several checks are made, including whether the blocks are stacked way too high (in which case a GAME OVER! message is shown) and whether they form a full row (in which case ~~the row turns gray~~ and 40 points are given to the player).

The background music, defined in `BackgroundMusic`, starts a new thread with the start of the console app and runs for the whole lifecycle of the application. It is essentially an infinite loop, calling Beep with different arguments to simulate the original TETRIS theme.
