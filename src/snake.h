#ifndef SNAKE_H
#define SNAKE_H

#include <actor.h>

#include <vector>

#include "SDL.h"

class Snake : public virtual Actor {
 public:
  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}

  void Update() override;
  bool CellIsOccuppied(int x, int y) override;

  void GrowBody();

  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif