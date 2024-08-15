#include <iostream>
#include "nn.h"
//#include "game.cpp"
int main(){
  int final_score = run();
  std::cout << "THE FINAL SCORE YOU GOT AFTER TRAINING IS ";
  std::cout << final_score << "\n";
  
 /* 
  int bored[4][4] = {
  {2,2,2,0},
  {4,4,8,2},
  {8,8,2,16},
  {2,2,4,2}};

  bool a = is_legal_move(Left,bored);
  std::cout << a << "\n";
  */
  return 0;
}
