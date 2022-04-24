#ifndef PACMAN_H
#define PACMAN_H

#include <actor.h>

#include <random>

class Pacman : public virtual Actor {
 public:
  Pacman(int grid_width, int grid_height);
  ~Pacman() {}

  void Update() override;
  bool CellIsOccuppied(int x, int y) override;

  float speed{0.5f};
  const int width{25};
  const int height{25};
  float position_x;
  float position_y;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_direction;

 private:
  void Move();

  int grid_width;
  int grid_height;
};

#endif