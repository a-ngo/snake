#ifndef PACMAN_H
#define PACMAN_H

class Pacman {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Pacman(int grid_width, int grid_height)
      : grid_width{grid_width},
        grid_height{grid_height},
        position_x{},
        position_y{} {}
  ~Pacman() {}

  void Update();

  void GrowBody();
  bool CellIsOccuppied(int x, int y);

  Direction direction = Direction::kRight;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  const int width{25};
  const int height{25};
  float position_x;
  float position_y;

 private:
  void Move();

  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif