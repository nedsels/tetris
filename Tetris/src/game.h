#pragma once

#include "blocks.cpp"
#include "colours.h"
#include "grid.h"
#include "menu.h"

using namespace std;

class Game {
 public:
  Game();

  Grid grid;
  Menu menu;
  double lastUpdateTime;
  double fallInterval;
  int level;
  bool gameOver;
  int score;
  bool pause;
  double pauseTime;
  int userHighScore;

  Block getRandomBlock();
  void getProjectionBlock();
  vector<Block> getAllBlocks();
  void draw();
  void handleInput();
  void moveBlockLeft();
  void moveBlockRight();
  void moveBlockDown();
  void update();
  bool intervalPassed(double interval);

 private:
  vector<Block> blocks;
  Block currentBlock;
  Block projectionBlock;
  Block nextBlock;

  bool isBlockOutside(Block block);
  void rotateBlock();
  void lockBlock();
  bool blockFits(Block block);
  void reset();
  void updateScore(int linesCleared, int moveDownPoints);
  void updateLevel();
  void updateSpeed();
  void updateHighScore();
};