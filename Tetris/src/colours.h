#pragma once
#include <raylib.h>

#include <vector>

using namespace std;

extern const Color darkGrey;
extern const Color darkGreyTranslucent;
extern const Color green;
extern const Color greenTranslucent;
extern const Color red;
extern const Color redTranslucent;
extern const Color orange;
extern const Color orangeTranslucent;
extern const Color yellow;
extern const Color yellowTranslucent;
extern const Color purple;
extern const Color purpleTranslucent;
extern const Color cyan;
extern const Color cyanTranslucent;
extern const Color blue;
extern const Color blueTranslucent;
extern const Color whiteTranslucent;
extern const Color darkBlue;
extern const Color lightBlue;

vector<Color> getCellColours();
vector<Color> getProjectionColours();
Color getGrayColour();