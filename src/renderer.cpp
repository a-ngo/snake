#include "renderer.h"

#include <iostream>
#include <string>

#include "SDL_image.h"

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const snake, SDL_Point const& food,
                      Pacman const& pacman) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const& point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render pacman
  // get pacman textures
  SDL_Texture* entityTexture;
  SDL_Rect pacmanUP[3];
  SDL_Rect pacmanDOWN[3];
  SDL_Rect pacmanLEFT[3];
  SDL_Rect pacmanRIGHT[3];

  SDL_Surface* pacman_image =
      IMG_Load("../assets/pacman_and_ghost_texture.png");
  if (pacman_image == nullptr) {
    std::cerr << "ERROR: could not load pacman and ghost texture image./n";
  } else {
    entityTexture = SDL_CreateTextureFromSurface(sdl_renderer, pacman_image);

    int posTexX = 0, posTexY = 0;

    /// Pacman goes up
    for (int i = 0; i < 3; ++i)
      pacmanUP[i] = {posTexX, posTexY, 30, 30}, posTexX += 31;
    /// Pacman goes down
    for (int i = 3; i < 6; ++i)
      pacmanDOWN[i % 3] = {posTexX, posTexY, 30, 30}, posTexX += 31;
    /// Pacman goes left
    for (int i = 6; i < 9; ++i)
      pacmanLEFT[i % 3] = {posTexX, posTexY, 30, 30}, posTexX += 31;
    /// Pacman goes right
    for (int i = 9; i < 12; ++i)
      pacmanRIGHT[i % 3] = {posTexX, posTexY, 30, 30}, posTexX += 31;
  }

  SDL_FreeSurface(pacman_image);

  SDL_Rect srcRect, dsRect;
  dsRect = {static_cast<int>(pacman.position_x) * block.w,
            static_cast<int>(pacman.position_y) * block.h, pacman.width,
            pacman.height};
  ++pacman_frame;

  if (pacman_frame == 30) pacman_frame = 0;

  switch (pacman.direction) {
    case Pacman::Direction::kUp:
      srcRect = pacmanUP[pacman_frame / 10];
      break;
    case Pacman::Direction::kRight:
      srcRect = pacmanRIGHT[pacman_frame / 10];
      break;
    case Pacman::Direction::kDown:
      srcRect = pacmanDOWN[pacman_frame / 10];
      break;
    case Pacman::Direction::kLeft:
      srcRect = pacmanLEFT[pacman_frame / 10];
      break;
    default:
      srcRect = pacmanUP[0];
  }

  SDL_RenderCopy(sdl_renderer, entityTexture, &srcRect, &dsRect);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) +
                    " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
