#pragma once
#include <raylib.h>

#include <vector>

using namespace std;

class Grid {
 public:
  Grid();

  int grid[20][10];
  int numRows;
  int numCols;
  int cellSize;

  void initialize();
  void draw(bool pause);
  bool isCellOutside(int row, int col);
  bool isCellEmpty(int row, int col);
  int clearFullRows();

 private:
  vector<Color> colours;

  bool isRowFull(int row);
  void clearRow(int row);
  void moveRowDown(int row, int numRows);
};