#include <raylib.h>

#include <fstream>
#include <iostream>
#include <string>

#include "colours.h"
#include "game.h"
#include "grid.h"

using namespace std;

const int windowWidth = 500;
const int windowHeight = 720;

void drawGameText(Game *game, Font font);
void drawMainMenu(Menu *menu, Font font, Texture logo);
void getNameMenu(Menu *menu, Font font);
void drawDeleteUserMenu(Menu *menu, Font font);

int main() {
  InitWindow(windowWidth, windowHeight, "Tetris");
  SetTargetFPS(60);

  const Font font_8514oem = LoadFontEx("fonts/8514oem.ttf", 64, 0, 0);

  Image image = LoadImage("graphics/logo.png");
  const Texture logo = LoadTextureFromImage(image);
  UnloadImage(image);

  Game game = Game();

  while (!WindowShouldClose()) {
    BeginDrawing();

    if (game.menu.menuScreenOn) {
      ClearBackground(darkBlue);

      game.menu.update();

      if (game.menu.nameUserScreen) {
        getNameMenu(&(game.menu), font_8514oem);
      } else if (game.menu.deleteUserScreen) {
        drawDeleteUserMenu(&(game.menu), font_8514oem);
      } else {
        drawMainMenu(&(game.menu), font_8514oem, logo);
      }
    } else {
      ClearBackground(darkBlue);

      game.update();

      drawGameText(&game, font_8514oem);

      game.draw();
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}

void drawGameText(Game *game, Font font) {
  // Score
  DrawTextEx(font, "Score", {355, 15}, 38, 2, WHITE);
  DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);

  char scoreText[10];
  sprintf(scoreText, "%d", game->score);
  Vector2 scoreTextSize = MeasureTextEx(font, scoreText, 38, 2);

  DrawTextEx(font, scoreText, {320 + (170 - scoreTextSize.x) / 2, 65}, 38, 2,
             WHITE);

  // High score
  DrawTextEx(font, "High Score", {25, 620}, 25, 2, WHITE);
  DrawRectangleRounded({20, 650, 150, 60}, 0.3, 6, lightBlue);

  char highScoreText[10];
  sprintf(highScoreText, "%d", game->userHighScore);
  Vector2 highScoreTextSize = MeasureTextEx(font, highScoreText, 40, 2);

  DrawTextEx(font, highScoreText,
             {20 + (150 - highScoreTextSize.x) / 2,
              650 + (60 - highScoreTextSize.y) / 2},
             40, 2, WHITE);

  // Next block
  DrawTextEx(font, "Next", {365, 175}, 38, 2, WHITE);
  DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);

  // Level
  DrawTextEx(font, "Level", {395, 620}, 25, 2, WHITE);
  DrawRectangleRounded({380, 650, 100, 60}, 0.3, 6, lightBlue);

  char levelText[10];
  sprintf(levelText, "%d", game->level);
  Vector2 levelTextSize = MeasureTextEx(font, levelText, 40, 2);

  DrawTextEx(
      font, levelText,
      {380 + (100 - levelTextSize.x) / 2, 650 + (60 - levelTextSize.y) / 2}, 40,
      2, WHITE);

  // Game over
  if (game->gameOver) {
    DrawTextEx(font, "GAME", {365, 470}, 38, 2, RED);
    DrawTextEx(font, "OVER", {365, 500}, 38, 2, RED);
  } else if (game->pause) {
    DrawTextEx(font, "paused", {345, 470}, 38, 2, WHITE);
  }

  // User
  DrawTextEx(font, "User", {250, 620}, 25, 2, WHITE);
  DrawRectangleRounded({180, 650, 190, 60}, 0.3, 6, lightBlue);

  const char *name = game->menu.users[game->menu.userSelected].name.c_str();
  int nameFontSize = 38;
  Vector2 userTextSize = MeasureTextEx(font, name, nameFontSize, 2);

  while (userTextSize.x > 180) {
    nameFontSize--;
    userTextSize = MeasureTextEx(font, name, nameFontSize, 2);
  }

  DrawTextEx(
      font, name,
      {180 + (190 - userTextSize.x) / 2, 650 + (60 - userTextSize.y) / 2},
      nameFontSize, 2, WHITE);
}

void drawMainMenu(Menu *menu, Font font, Texture logo) {
  Color colour;

  for (int i = 0; i < 3; i++) {
    if (i == menu->userSelected) {
      colour = WHITE;
    } else {
      colour = GRAY;
    }

    const char *name = menu->users[i].name.c_str();

    Vector2 nameTextSize = MeasureTextEx(font, name, 38, 2);
    DrawTextEx(font, name,
               {(windowWidth - nameTextSize.x) / 2, (float)250 + i * 100}, 38,
               2, colour);
  }

  DrawTexture(logo, 54.5, 50, WHITE);

  Vector2 selectUserTextSize = MeasureTextEx(font, "SELECT USER", 20, 2);
  DrawTextEx(font, "SELECT USER",
             {(windowWidth - selectUserTextSize.x) / 2, 600}, 20, 2,
             getGrayColour());
}

void getNameMenu(Menu *menu, Font font) {
  Rectangle textBox = {(windowWidth - 300) / 2, (windowHeight - 75) / 2, 300,
                       75};
  string *name = &(menu->users[menu->userSelected].name);

  if (*name == "_____") {
    *name = "";
  }

  bool mouseInBox = menu->getName(textBox);

  DrawRectangleRec(textBox, LIGHTGRAY);

  Color outlineColour;

  if (mouseInBox) {
    outlineColour = RED;
  } else {
    outlineColour = DARKGRAY;
  }

  DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width,
                     (int)textBox.height, outlineColour);

  Vector2 nameTextSize = MeasureTextEx(font, name->c_str(), 38, 2);
  DrawTextEx(font, name->c_str(),
             {textBox.x + (textBox.width - nameTextSize.x) / 2,
              textBox.y + (textBox.height - nameTextSize.y) / 2},
             38, 2, WHITE);

  Vector2 namePromptText = MeasureTextEx(font, "ENTER NAME:", 30, 2);
  DrawTextEx(font, "ENTER NAME:",
             {(windowWidth - namePromptText.x) / 2, textBox.y - 35}, 30, 2,
             WHITE);
}

void drawDeleteUserMenu(Menu *menu, Font font) {
  Vector2 deleteUserTextSize = MeasureTextEx(font, "DELETE USER:", 30, 2);
  DrawTextEx(font,
             "DELETE USER:", {(windowWidth - deleteUserTextSize.x) / 2, 270},
             30, 2, WHITE);

  const char *name = menu->users[menu->userSelected].name.c_str();

  Vector2 nameTextSize = MeasureTextEx(font, name, 55, 2);
  DrawTextEx(font, name, {(windowWidth - nameTextSize.x) / 2, 300}, 55, 2, RED);

  Vector2 confirmDeleteTextSizeLine1 =
      MeasureTextEx(font, "PRESS ENTER", 25, 2);
  Vector2 confirmDeleteTextSizeLine2 = MeasureTextEx(font, "TO CONFIRM", 25, 2);
  DrawTextEx(font, "PRESS ENTER",
             {(windowWidth - confirmDeleteTextSizeLine1.x) / 2, 500}, 25, 2,
             WHITE);
  DrawTextEx(font, "TO CONFIRM",
             {(windowWidth - confirmDeleteTextSizeLine2.x) / 2, 520}, 25, 2,
             WHITE);
}