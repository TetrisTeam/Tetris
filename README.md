Tetris
======

Course assignment for Introduction to Programming class @ FMI, SU.

General
------------------------
In the TETRIS source, both our variables and functions are in camel case, for example `WindowWidth`, `CheckIfFull`, etc..

The game logic lies in Tetris.cpp. 

We have taken advantage of the object oriented nature of C++. Each shape has its own dedicated class, extending `BlockBase` - `ZBlock`, `TBlock`, `LBlock`, `LineBlock` and `SquareBlock`.

As for background music, we used Windows' beeping functionality to recreate the original TETRIS theme!
