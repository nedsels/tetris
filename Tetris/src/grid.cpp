#include "grid.h"

#include <iostream>

#include "colours.h"

using namespace std;

Grid::Grid() {
  numRows = 20;
  numCols = 10;
  cellSize = 30;
  initialize();
  colours = getCellColours();
}

void Grid::initialize() {
  for (int row = 0; row < numRows; row++) {
    for (int col = 0; col < numCols; col++) {
      Grid::grid[row][col] = 0;
    }
  }
}

void Grid::draw(bool pause) {
  for (int row = 0; row < numRows; row++) {
    for (int col = 0; col < numCols; col++) {
      DrawRectangleRounded({(float)(col * cellSize + 11), (float)(row * cellSize + 11), (float)(cellSize - 1),
                    (float)(cellSize - 1)}, 0.1, 0, colours[grid[row][col]]);
    }
  }

  if (pause) {
    DrawRectangle(10, 10, cellSize * numCols, cellSize * numRows,
                  whiteTranslucent);
  }
}

bool Grid::isCellOutside(int row, int col) {
  if (row < 0 || col < 0 || row >= numRows || col >= numCols) {
    return true;
  }

  return false;
}

bool Grid::isCellEmpty(int row, int col) {
  if (grid[row][col] == 0) {
    return true;
  }

  return false;
}

int Grid::clearFullRows() {
  int completedRows = 0;
  for (int row = numRows - 1; row >= 0; row--) {
    if (isRowFull(row)) {
      completedRows++;
      clearRow(row);
    } else if (completedRows > 0) {
      moveRowDown(row, completedRows);
    }
  }

  return completedRows;
}

bool Grid::isRowFull(int row) {
  for (int col = 0; col < numCols; col++) {
    if (grid[row][col] == 0) {
      return false;
    }
  }

  return true;
}

void Grid::clearRow(int row) {
  for (int col = 0; col < numCols; col++) {
    grid[row][col] = 0;
  }
}

void Grid::moveRowDown(int row, int numRows) {
  for (int col = 0; col < numCols; col++) {
    grid[row + numRows][col] = grid[row][col];
  }

  clearRow(row);
}
