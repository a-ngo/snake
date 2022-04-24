#ifndef ACTOR_H
#define ACTOR_H

class Actor {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Actor() {}
  ~Actor() {}

  virtual void Update() = 0;
  virtual bool CellIsOccuppied(int x, int y) = 0;

  float speed{0.1f};
  int size{1};
  bool alive{true};

  Direction direction = Direction::kUp;
  int grid_width;
  int grid_height;
};

#endif