/*
 * Word.h
 *
 *  Created on: Jul 31, 2022
 *      Author: nathan
 */

#ifndef WORD_H_
#define WORD_H_

#include <string>

using namespace std;

class Word{
  public:

    //constructors
    Word(string& w);
    Word();
    //de
    ~Word();

    //functions:
    void increment_height(const int& i);
    int* get_height();


    //attributes:
    string word;
    int height;
    int* h = &height;
    int x;

  private:

};
#endif /* WORD_H_ */
