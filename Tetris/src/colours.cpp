#include "colours.h"

#include <cmath>
#include <vector>

using namespace std;

const Color darkGrey = {26, 31, 40, 255};
const Color darkGreyTranslucent = {26, 31, 40, 50};
const Color green = {47, 230, 23, 255};
const Color greenTranslucent = {47, 230, 23, 50};
const Color red = {232, 18, 18, 255};
const Color redTranslucent = {232, 18, 18, 100};
const Color orange = {226, 116, 17, 255};
const Color orangeTranslucent = {226, 116, 17, 75};
const Color yellow = {237, 234, 4, 255};
const Color yellowTranslucent = {237, 234, 4, 50};
const Color purple = {166, 0, 247, 255};
const Color purpleTranslucent = {166, 0, 247, 100};
const Color cyan = {21, 204, 209, 255};
const Color cyanTranslucent = {21, 204, 209, 50};
const Color blue = {13, 64, 216, 255};
const Color blueTranslucent = {13, 64, 216, 100};
const Color whiteTranslucent = {255, 255, 255, 100};
const Color darkBlue = {44, 44, 127, 255};
const Color lightBlue = {59, 85, 162, 255};

vector<Color> getCellColours() {
  return {darkGrey, green, red, orange, yellow, purple, cyan, blue};
}

vector<Color> getProjectionColours() {
  return {darkGreyTranslucent, greenTranslucent,  redTranslucent,
          orangeTranslucent,   yellowTranslucent, purpleTranslucent,
          cyanTranslucent,     blueTranslucent};
}

Color getGrayColour() {
  float time = (float)((int)(GetTime() * 1000) % 2000) / 1000.0;

  Color timedGrey = {(unsigned char)(70.5 * cos(PI * time) + 184.5),
                     (unsigned char)(70.5 * cos(PI * time) + 184.5),
                     (unsigned char)(70.5 * cos(PI * time) + 184.5), 255};

  return timedGrey;
}