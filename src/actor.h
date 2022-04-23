#ifndef ACTOR_H
#define ACTOR_H

class Actor {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Actor() {}
  ~Actor() {}

  void Update();

  void GrowBody();
  bool CellIsOccuppied(int x, int y);

  Direction direction;

  float speed;
  int size;
  bool alive;

 private:
  bool growing;
  int grid_width;
  int grid_height;
};

#endif