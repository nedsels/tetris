#include "menu.h"

#include <raylib.h>

#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

Menu::Menu() {
  menuScreenOn = true;
  userSelected = 0;
  nameUserScreen = false;
  letterCount = 0;
  maxNameLength = 13;
  deleteUserScreen = false;

  userInfo.open("userInfo.txt", ios::in);

  if (userInfo.is_open()) {
    string line;
    bool empty = true;

    bool getName = false;
    bool getScore = false;
    int userNum = -1;

    while (getline(userInfo, line)) {
      empty = false;

      if (!strncmp(line.c_str(), "USER", 4)) {
        userNum = line[4] - '0';
        getName = true;
        continue;
      }

      if (!strncmp(line.c_str(), "SCORE", 5)) {
        userNum = line[5] - '0';
        getScore = true;
        continue;
      }

      if (getName) {
        users[userNum].name = line;
        getName = false;
      }

      if (getScore) {
        users[userNum].highScore = stoi(line);
        getScore = false;
      }
    }

    if (empty) {
      users[0].name = "_____";
      users[0].highScore = 0;
      users[1].name = "_____";
      users[1].highScore = 0;
      users[2].name = "_____";
      users[2].highScore = 0;

      updateUserInfo();
    }

    if (userInfo.is_open()) {
      userInfo.close();
    }
  } else {
    cout << "userInfo.txt did not open at game initialization." << endl;
  }
}

void Menu::update() {
  switch (GetKeyPressed()) {
    case KEY_DOWN:
      userSelected++;

      if (userSelected > 2) {
        userSelected--;
      }

      break;
    case KEY_UP:
      userSelected--;

      if (userSelected < 0) {
        userSelected++;
      }
      break;
    case KEY_ENTER:
      if (deleteUserScreen) {
        deleteUser(userSelected);
        deleteUserScreen = false;
      } else if (users[userSelected].name[0] == '_' && !nameUserScreen) {
        nameUserScreen = true;
        letterCount = 0;
      } else if (users[userSelected].name.size() > 0) {
        updateUserInfo();
        nameUserScreen = false;
        menuScreenOn = false;
      }

      break;
    case KEY_BACKSPACE:
      if (!deleteUserScreen && !nameUserScreen &&
          users[userSelected].name[0] != '_') {
        deleteUserScreen = true;
      } else if (deleteUserScreen && !nameUserScreen) {
        deleteUserScreen = false;
      }

      break;
  }
}

bool Menu::getName(Rectangle textBox) {
  bool mouseInBox = CheckCollisionPointRec(GetMousePosition(), textBox);
  string *name = &(users[userSelected].name);

  if (mouseInBox) {
    SetMouseCursor(MOUSE_CURSOR_IBEAM);
    int character = GetCharPressed();

    while (character > 0) {
      if (!(character == '_' && letterCount == 0) && character >= 33 &&
          character <= 125 && letterCount < maxNameLength) {
        name->push_back((char)character);
        letterCount++;
      }

      character = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE)) {
      letterCount--;

      if (letterCount < 0) {
        letterCount = 0;
      }

      name->pop_back();
    }
  } else {
    SetMouseCursor(MOUSE_CURSOR_DEFAULT);
  }

  return mouseInBox;
}

void Menu::updateUserInfo() {
  if (userInfo.is_open()) {
    userInfo.close();
  }

  userInfo.open("userInfo.txt", ios::out);

  userInfo << "USER0" << endl;
  userInfo << users[0].name << endl;
  userInfo << "SCORE0" << endl;
  userInfo << users[0].highScore << endl;
  userInfo << "USER1" << endl;
  userInfo << users[1].name << endl;
  userInfo << "SCORE1" << endl;
  userInfo << users[1].highScore << endl;
  userInfo << "USER2" << endl;
  userInfo << users[2].name << endl;
  userInfo << "SCORE2" << endl;
  userInfo << users[2].highScore;

  userInfo.close();
}

int Menu::getHighScore() { return users[userSelected].highScore; }

void Menu::deleteUser(int user) {
  users[user].name = "_____";
  users[user].highScore = 0;

  updateUserInfo();
}
