#include "block.h"

using namespace std;

Block::Block() {
  cellSize = 30;
  rotationState = 0;
  colours = getCellColours();
  coloursTranslucent = getProjectionColours();
  rowOffset = 0;
  colOffset = 0;
}

void Block::draw(int offsetY, int offsetX, bool pause, bool projection) {
  Color colour;
  if (!projection) {
    colour = colours[id];
  } else {
    colour = coloursTranslucent[id];
  }
  for (Position item : getCellPositions()) {
    DrawRectangleRounded({(float)(item.col * cellSize + offsetX),
                          (float)(item.row * cellSize + offsetY),
                          (float)(cellSize - 1), (float)(cellSize - 1)},
                         0.1, 0, colour);
    if (pause) {
      DrawRectangleRounded({(float)(item.col * cellSize + offsetX),
                            (float)(item.row * cellSize + offsetY),
                            (float)(cellSize - 1), (float)(cellSize - 1)},
                           0.1, 0, whiteTranslucent);
    }
  }
}

void Block::move(int rows, int cols) {
  rowOffset += rows;
  colOffset += cols;
}

vector<Position> Block::getCellPositions() {
  vector<Position> movedTiles;

  for (Position item : cells[rotationState]) {
    movedTiles.push_back(Position(item.row + rowOffset, item.col + colOffset));
  }

  return movedTiles;
}

void Block::rotate() {
  rotationState++;

  if (rotationState >= (int)cells.size()) {
    rotationState = 0;
  }
}

void Block::rotateReverse() {
  rotationState--;

  if (rotationState < 0) {
    rotationState = (int)cells.size() - 1;
  }
}
