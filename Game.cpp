/*
 * Game.cpp
 *
 *  Created on: Jul 31, 2022
 *      Author: nathan
 */

#include "Game.h"

#include <unistd.h>//sleep
#include <fstream>//fstream
#include <iostream>


//const
Game::Game() {
  initscr();
  refresh();
  //setup
  setup();
  refresh();
  //start game manager thread:
}
//de
Game::~Game() { endwin(); delwin(win_info);delwin(win_game);}

//ncurses setup
void Game::setup()
{
  // get max x and y
  int max_y, max_x = 10;
  getmaxyx(stdscr, max_y, max_x);
  // apply window height vars
  game_win_height = max_y * 0.75;
  game_win_width = max_x;
  info_win_height = max_y * 0.25;
  info_win_width = max_x;
  // create windows
  win_game = newwin(game_win_height, game_win_width, 0, 0);
  refresh();
  box(win_game, 0, 0);
  win_info = newwin(info_win_height, info_win_width, game_win_height + 1, 0);
  refresh();
  box(win_info, 0, 0);
  refresh();
  //wprintw(win_info, "HI");
  //wmove(win_game, 0, 0);
 // wprintw(win_game, "%s", "SETTING UP");
  //refresh
  wrefresh(win_info);
  wrefresh(win_game);
}

//read words from file
std::vector<Word> Game:: read_file(int level)
{
  refresh_screen();
  wmove(win_info, 0, 0);
 // wprintw(win_info, "%s", "READING");
  wrefresh(win_info);
  //initialise vars
  string word;
  vector<Word> word_vector;
  //switch on what level they are on
  //read file 1
  fstream file;
  try
  {
      file.open("/home/nathan/Documents/code/c++/typing_game_2/word_list_1.txt");
      while(file >> word)
      {
          //cout<< word <<endl;
          Word new_word(word);
          word_vector.push_back(new_word);
      }
      file.close();
  }
  catch(const std::exception& e)
  {
      std::cerr << e.what() << '\n';
  }
  //cout << word_vector.size() << endl;
  return word_vector;
}

void Game::refresh_screen()
{
    wclear(win_game);
    //wclear(win_info);
    box(win_game, 0, 0);
    //box(win_info, 0, 0);
}

//start game
void Game::start()
{
  //std::cout << "START" << std::endl;
  refresh_screen();
  wmove(win_info, 0, 0);
  //wprintw(win_info, "%s", "STARTING");
  wrefresh(win_info);
  //printf("starting");
  vector<Word> word_list = read_file(1);
  //copy vector
  for (int i=0; i<word_list.size(); i++) 
      (*word_list_copy).push_back(word_list[i]); 

  Word processed_words[word_list.size()];
  int count =0;

  for (Word &current_word : word_list)
  {
    refresh_screen();
    //process and draw curent word
    int random_x = 1 + (rand() % game_win_width);
    current_word.x = random_x;
    wmove(win_game, current_word.height, current_word.x);
    wprintw(win_game, "%s", current_word.word.c_str());
    current_word.height++;
    wrefresh(win_game);

    //add to processed words
    processed_words[count] = current_word;
    //mvwprintw(win_info,0,0,"%s", processed_words[count].word.c_str());
    //draw previous words
    for (Word &w : processed_words)
    {
      //move
      w.height++;
      //w.increment_height(increment);
      wmove(win_game, w.height, w.x);
      //wprintw(win_game, "%d", w.height);
      //wprintw(win_game, "%i", w.height);
      wprintw(win_game, "%s", w.word.c_str());
      //cout << w.height << endl;
      wrefresh(win_game);
      //log
      //mvwprintw(win_info,0,0,"%s", (to_string(sizeof(processed_words))).c_str());
      //mvwprintw(win_info,0,0,"%s", w.word.c_str());
      //wrefresh(win_info);
    }
    wrefresh(win_info);
    count++;
    sleep(2);
  }
  finished = true;
}

void Game::user_type()
{
  int pos = 0;
  char* chars_in = (char*)malloc(sizeof(char));
  while(!finished)
  {
    char in = getchar();
    wmove(win_info, 5, 5+pos);
    wprintw(win_info, "%c", in);
    wrefresh(win_info);
    //store input
    chars_in[pos] = in;
    chars_in = (char*)realloc(chars_in, pos+1);//add space for another
    //check correct?
    Word& current_word = (*word_list_copy)[0];
    string str(chars_in);
    //log:
    wmove(win_info, 8, 5);
    wprintw(win_info, "%i", (int)sizeof(chars_in) );
    wmove(win_info, 8, 7);
    wprintw(win_info, "%i", (int)(*word_list_copy).size());
    wrefresh(win_info);
    if(str==current_word.word)
    {
      //user typed correctlty
      
      wmove(win_info, 7, 5);
      wprintw(win_info, "%s", "CORRECT!!!");
      wrefresh(win_info);
    }
    else
    {
      //user typed incorrectlty
      wmove(win_info, 8, 5);
      wprintw(win_info, "%s", "INCORRECT!");
      wrefresh(win_info);
    }
    //increment
    pos++;
  }
  chars_in[pos] = '\0';
  free(chars_in);
}