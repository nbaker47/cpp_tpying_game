/*
 * Main.cpp
 *
 *  Created on: Jul 31, 2022
 *      Author: nathan
 */

#include "Game.h"
#include<thread>

int main() {
  Game new_game;
  //thread
  std::thread game_window_manager_thread(&Game::start, new_game);
  std::thread info_window_manager_thread(&Game::user_type, new_game);
  //user input thread:
  game_window_manager_thread.join();
  return 0;
}


