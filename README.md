# Tetris
## Instructions
### 1. User menu
<img width="250" alt="image" src="https://github.com/nedsels/tetris/assets/142703703/fac44573-8434-4c4e-9c0f-bdc59ae34dcd">

- Use <kbd>Up↑</kbd> and <kbd>Down↓</kbd> arrows to navigate user menu
- Press <kbd>Enter</kbd> on a blank user (_____) to add a name
- Press <kbd>Backspace</kbd> on an existing user to delete
- Press <kbd>Enter</kbd> on an existing user to begin playing

### 2. Add user screen
<img width="250" alt="image" src="https://github.com/nedsels/tetris/assets/142703703/72872c7c-0308-401a-a7b9-ebc93c930c76">

- Hover the cursor over the grey box to type in a name
- Maximum 13 characters allowed
- Press <kbd>Enter</kbd> to confirm and begin playing

### 3. Delete user screen
<img width="248" alt="image" src="https://github.com/nedsels/tetris/assets/142703703/bd48fd45-2a80-4730-bc9c-51512244e0dd">

- Press <kbd>Enter</kbd> to delete user
- Press <kbd>Backspace</kbd> to cancel and return to menu

### 4. Game
<img width="251" alt="image" src="https://github.com/nedsels/tetris/assets/142703703/8504d3ea-92ec-4e54-a85c-bd6376a24ebd">

Blocks of different shapes will fall from the top. You can move them, left, right, and down, and rotate them. You can also lock them to the "ghost block" shown at the bottom of the game area.

You earn points when you press down and complete rows. The more rows you complete simultaneously, the more points you are awarded. Every 500 points, your level increases, and so does the speed at which the blocks fall. If a new block that spawns at the top overlaps with a block that has already fallen, the game is over.

#### Controls
- Press <kbd>Right→</kbd> to move the falling block right
- Press <kbd>Left←</kbd> to move the falling block left
- Press <kbd>Down↓</kbd> to move the falling block down
- Press <kbd>Up↑</kbd> to rotate the falling block clockwise
- Press <kbd>Enter</kbd> to lock the block to the position of the "ghost block" at the bottom
- Press <kbd>Space</kbd> to pause the game
- Press <kbd>Backspace</kbd> to end the game and return to the menu
- When "GAME OVER" shows, press any key to restart the game

## Credit
1. [This tutorial](https://youtu.be/wVYKG_ch4yM) was followed, excluding the sounds. However, the menus, pause feature, highscore and users, scoring system, level and speed system, and ghost blocks were made by me.
2. This uses the [Raylib library](https://www.raylib.com/).

## To do
1. Add include guards to <kbd>.h</kbd> files.
2. Create horizontal and vertical text centering functions in <kbd>main.cpp</kbd> to avoid manual centering for each piece of text.
