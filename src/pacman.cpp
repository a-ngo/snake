#include "pacman.h"

#include <cmath>

void Pacman::Update() {
  Move();

  // TODO(a-ngo): update body - grow
  // Grow();
}

void Pacman::Move() {
  position_x += speed;

  // Wrap Pacman around to the beginning if going off of the screen.
  position_x = fmod(position_x + grid_width, grid_width);
  position_y = fmod(position_y + grid_height, grid_height);
}

// Inefficient method to check if cell is occupied by pacman.
bool Pacman::CellIsOccuppied(int x, int y) {
  if (x == static_cast<int>(position_x) && y == static_cast<int>(position_y)) {
    return true;
  }
  //   for (auto const &item : body) {
  //     if (x == item.x && y == item.y) {
  //       return true;
  //     }
  //   }
  return false;
}