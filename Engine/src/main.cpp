#include <iostream>
#include "nn.h"
#include "game.h"
#include <vector>
#define ITERS 100
int main(){
  /*
  int final_score = run();
  std::cout << "THE FINAL SCORE YOU GOT AFTER TRAINING IS ";
  std::cout << final_score << "\n";
  */
  int scores[ITERS];
  for (int i=0;i<ITERS;++i){

    //int score = search();
    scores[i] = search();
    /*
    std::cout << "THE SCORE FOR ITERATION: " << i;
    std::cout << " WAS: " << score << "\n";
    std::cout << "-----------------------\n";
    */
  }
  int sum = 0;
  int maxx = 0;
  for (int i=0;i<ITERS;++i){
    sum += scores[i];
    if (scores[i] > maxx){
      maxx = scores[i];
    }
  }
  float avg = (float)sum/(float)ITERS;
  std::cout << "THE AVERAGE SCORE IS: " << avg << "\n";
  std::cout << "THE BEST SCORE YOU GOT WAS: " << maxx << "\n";
  
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
