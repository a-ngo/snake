#include "pacman.h"

#include <cmath>

void Pacman::Update() { Move(); }

void Pacman::Move() {
  // TODO(a-ngo): implement behavior
  position_x += speed;

  // Wrap Pacman around to the beginning if going off of the screen.
  position_x = fmod(position_x + grid_width, grid_width);
  position_y = fmod(position_y + grid_height, grid_height);
}

// check if cell is occupied by pacman.
bool Pacman::CellIsOccuppied(int x, int y) {
  return x == static_cast<int>(position_x) && y == static_cast<int>(position_y);
}