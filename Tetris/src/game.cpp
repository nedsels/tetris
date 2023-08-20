#include "game.h"

#include <raylib.h>

#include <cmath>
#include <iostream>
#include <random>
#include <string>

using namespace std;

Game::Game() {
  grid = Grid();
  menu = Menu();
  blocks = getAllBlocks();
  currentBlock = getRandomBlock();
  getProjectionBlock();
  nextBlock = getRandomBlock();
  lastUpdateTime = 0;
  fallInterval = 0.4;
  level = 1;
  gameOver = false;
  score = 0;
  pause = false;
  pauseTime = 0;
  userHighScore = menu.getHighScore();
}

void Game::update() {
  userHighScore = menu.getHighScore();

  if (!gameOver) {
    handleInput();
    getProjectionBlock();

    if (intervalPassed(fallInterval)) {
      moveBlockDown();
    }
  } else if (gameOver && GetKeyPressed() != 0) {
    reset();
  }
}

Block Game::getRandomBlock() {
  if (blocks.empty()) {
    blocks = getAllBlocks();
  }

  int randIndex = rand() % blocks.size();
  Block block = blocks[randIndex];
  blocks.erase(blocks.begin() + randIndex);
  return block;
}

void Game::getProjectionBlock() {
  projectionBlock = currentBlock;

  while (1) {
    projectionBlock.move(1, 0);

    if (isBlockOutside(projectionBlock) || !blockFits(projectionBlock)) {
      projectionBlock.move(-1, 0);
      break;
    }
  }
}

vector<Block> Game::getAllBlocks() {
  return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::draw() {
  grid.draw(pause);
  currentBlock.draw(11, 11, pause, false);
  projectionBlock.draw(11, 11, pause, true);

  switch (nextBlock.id) {
    case 3:
      nextBlock.draw(290, 255, pause, false);
      break;
    case 4:
      nextBlock.draw(280, 255, pause, false);
      break;
    default:
      nextBlock.draw(270, 270, pause, false);
      break;
  }

  if (pause) {
    DrawRectangle(10 + grid.cellSize * 2.5, 10 + grid.cellSize * 7,
                  grid.cellSize * 1.5, grid.cellSize * 6, WHITE);
    DrawRectangle(10 + grid.cellSize * 6, 10 + grid.cellSize * 7,
                  grid.cellSize * 1.5, grid.cellSize * 6, WHITE);
  }
}

void Game::handleInput() {
  int key = GetKeyPressed();
  if (key == KEY_BACKSPACE) {
    updateHighScore();
    reset();
    menu.menuScreenOn = true;
  } else if (!pause) {
    switch (key) {
      case KEY_LEFT:
        moveBlockLeft();
        break;
      case KEY_RIGHT:
        moveBlockRight();
        break;
      case KEY_DOWN:
        moveBlockDown();
        updateScore(0, 1);
        break;
      case KEY_UP:
        rotateBlock();
        break;
      case KEY_ENTER:
        updateScore(0,
                    2 * (projectionBlock.rowOffset - currentBlock.rowOffset));
        currentBlock = projectionBlock;
        lockBlock();
        break;
      case KEY_SPACE:
        pause = !pause;
        pauseTime = GetTime();
        break;
    }
  } else {
    switch (key) {
      case KEY_SPACE:
        pause = !pause;
        lastUpdateTime += GetTime() - pauseTime;
        pauseTime = 0;
        break;
    }
  }
}

void Game::moveBlockLeft() {
  currentBlock.move(0, -1);

  if (isBlockOutside(currentBlock) || !blockFits(currentBlock)) {
    moveBlockRight();
  }
}

void Game::moveBlockRight() {
  currentBlock.move(0, 1);

  if (isBlockOutside(currentBlock) || !blockFits(currentBlock)) {
    moveBlockLeft();
  }
}

void Game::moveBlockDown() {
  currentBlock.move(1, 0);

  if (isBlockOutside(currentBlock) || !blockFits(currentBlock)) {
    currentBlock.move(-1, 0);
    lockBlock();
  }
}

bool Game::isBlockOutside(Block block) {
  for (Position item : block.getCellPositions()) {
    if (grid.isCellOutside(item.row, item.col)) {
      return true;
    }
  }

  return false;
}

void Game::rotateBlock() {
  currentBlock.rotate();

  if (isBlockOutside(currentBlock) || !blockFits(currentBlock)) {
    currentBlock.rotateReverse();
  }
}

void Game::lockBlock() {
  for (Position item : currentBlock.getCellPositions()) {
    grid.grid[item.row][item.col] = currentBlock.id;
  }

  currentBlock = nextBlock;

  if (!blockFits(currentBlock)) {
    gameOver = true;

    updateHighScore();
  }

  nextBlock = getRandomBlock();

  int rowsCleared = grid.clearFullRows();
  updateScore(rowsCleared, 0);
}

bool Game::blockFits(Block block) {
  for (Position item : block.getCellPositions()) {
    if (!grid.isCellEmpty(item.row, item.col)) {
      return false;
    }
  }

  return true;
}

void Game::reset() {
  grid.initialize();
  blocks = getAllBlocks();
  currentBlock = getRandomBlock();
  nextBlock = getRandomBlock();
  score = 0;
  gameOver = false;
  pause = false;
  fallInterval = 0.4;
  level = 1;
}

void Game::updateScore(int linesCleared, int moveDownPoints) {
  switch (linesCleared) {
    case 1:
      score += 100;
      break;
    case 2:
      score += 300;
      break;
    case 3:
      score += 500;
      break;
    case 4:
      score += 800;
      break;
  }

  score += moveDownPoints;

  updateLevel();
  updateSpeed();
}

void Game::updateLevel() { level = (int)floor(score / 500) + 1; }

void Game::updateSpeed() { fallInterval = -6.79e-2 * log(2.76e-3 * level); }

void Game::updateHighScore() {
  if (score > userHighScore) {
    menu.users[menu.userSelected].highScore = score;
    menu.updateUserInfo();
    userHighScore = menu.getHighScore();
  }
}

bool Game::intervalPassed(double interval) {
  if (!pause && GetTime() - lastUpdateTime >= interval) {
    lastUpdateTime = GetTime();
    return true;
  }

  return false;
}
