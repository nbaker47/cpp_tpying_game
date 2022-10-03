/*
 * Word.cpp
 *
 *  Created on: Jul 31, 2022
 *      Author: nathan
 */

#include "Word.h"

Word::Word(string& w) {
	this->word=w; this->height=1; this->x=1;
}

Word::Word() {
	this->word=""; this->height=1; this->x=1;
}


Word::~Word() {
	// TODO Auto-generated destructor stub
}

//broken
void Word::increment_height(const int& i)
{
  height+=i ;
};
int* Word::get_height(){
  return h;
};

