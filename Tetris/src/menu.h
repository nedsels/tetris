#pragma once
#include <raylib.h>

#include <fstream>
#include <string>

using namespace std;

struct User {
  string name;
  int highScore;
};

class Menu {
 public:
  Menu();

  fstream userInfo;
  User users[3];
  bool menuScreenOn;
  int userSelected;
  bool nameUserScreen;
  int letterCount;
  int maxNameLength;
  bool deleteUserScreen;

  void update();
  bool getName(Rectangle textBox);
  void updateUserInfo();
  int getHighScore();
  void deleteUser(int user);
};