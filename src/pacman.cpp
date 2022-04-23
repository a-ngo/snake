#include "pacman.h"

#include <cmath>
#include <iostream>

void Pacman::Update() { Move(); }

// random movement
void Pacman::Move() {
  float prev_position_x = position_x;
  float prev_position_y = position_y;

  int dir = random_direction(engine);
  switch (dir) {
    case 0:
      direction = Direction::kUp;
      position_y -= speed;
      break;
    case 1:
      direction = Direction::kRight;
      position_x += speed;
      break;
    case 2:
      direction = Direction::kDown;
      position_y += speed;
      break;
    case 3:
      direction = Direction::kLeft;
      position_x -= speed;
  }

  // Wrap Pacman around to the beginning if going off of the screen.
  position_x = fmod(position_x + grid_width, grid_width);
  position_y = fmod(position_y + grid_height, grid_height);
}

// check if cell is occupied by pacman.
bool Pacman::CellIsOccuppied(int x, int y) {
  return x == static_cast<int>(position_x) && y == static_cast<int>(position_y);
}