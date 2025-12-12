# Space Shooter Game in C++ (ncurses)

A terminal-based 2D spaceship shooter game implemented in C++ using the
ncurses library. The player controls a spaceship, shoots enemies, and
survives as long as possible while tracking score and lives.

## Features:

**Player Controls:**

- Move left/right using arrow keys.

- Shoot bullets using the UP arrow key.

- Pause and resume the game using \'p\'.

- Quit the game using \'q\' or ESC.

**Enemies:**

- Spawn periodically and move horizontally across the screen.

- Drop bullets towards the player.

- Increase speed and spawn rate as the score increases.

**Score and Lives:**

- Player earns points by destroying enemies.

- Player loses lives when hit by enemy bullets or when enemies reach
the bottom.

- Game over occurs when lives reach zero.

**Pause Functionality:**

- Pausing stops all enemy and player actions.

- Press `p` to toggle pause.

**Restart:**

After game over, press `r` to restart the game. 

---

## Gameplay Mechanics 

**Player Movement:**
- The player moves horizontally within the game window.

- Player cannot move beyond the screen edges.

**Shooting:**

- The player fires bullets at enemies. Bullets move upward and disappear when off-screen. 

**Enemy Movement:**

- Enemies move horizontally, change direction at screen edges, and drop down gradually.

**Collision Detection:**

- Player bullets destroy enemies and increase score.

- Enemy bullets reduce player lives. o Enemy reaching the bottom ends the game.

**Difficulty Scaling:** 

- Enemy speed, spawn rate, and movement stepincrease as player score increases.

## Requirements
- *Linux / macOS terminal* (tested on Ubuntu)  
- g++ (C++ compiler)  
- ncurses library  

## To run
- use *./main*

