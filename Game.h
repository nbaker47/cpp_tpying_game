/*
 * Game.h
 *
 *  Created on: Jul 31, 2022
 *      Author: nathan
 */
#ifndef GAME_H_
#define GAME_H_

#include "Word.h"
#include <ncurses.h>
#include <vector>

class Game {
  private:
    bool game_over;
    int game_win_height;
    int game_win_width;
    int info_win_height;
    int info_win_width;

    WINDOW *win_game;
    WINDOW *win_info;
    const int& increment = 1;

    void refresh_screen();


  public:
    Game();
    ~Game();
    void setup();
    std::vector<Word> read_file(int i);
    void start();
    void user_type();
    bool finished = false;

    vector<Word> word_list_c;
    vector<Word>* word_list_copy = &word_list_c;
};

#endif /* GAME_H_ */
