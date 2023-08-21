#pragma once
#include <map>
#include <vector>

#include "colours.h"
#include "position.h"

using namespace std;

class Block {
 public:
  Block();

  int id;
  map<int, vector<Position>> cells;
  int rowOffset;
  int colOffset;

  void draw(int offsetY, int offsetX, bool pause, bool projection);
  void move(int rows, int cols);
  vector<Position> getCellPositions();
  void rotate();
  void rotateReverse();

 private:
  int cellSize;
  int rotationState;
  vector<Color> colours;
  vector<Color> coloursTranslucent;
};