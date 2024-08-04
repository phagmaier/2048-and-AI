#ifndef BRAIN_H
#define BRAIN_H 

/*
*NOTE
*Currently not counting 0's for standard deviation of row
*
*/

//euclidian distance (gonna use for distance from center
//of the board or distance from either row 1 col 1,
//row 1 col 2, or row 2 col 1 row 2 col 2)
//FORMULA:
//sqrt((x2-x1)^2 + (y2-y1)^2)


//STANDARD DEVIATION FORMULA:
//sqrt(1/n * sum(xi-mean)^2) -> n = number samples

#include <random>
#include <iostream>
#include <utility>
#include <unordered_map>
#include <cmath>
#include <vector>

enum Dir{
  None,
  Left,
  Right,
  Up,
  Down
};

int break_tie(int num);

//first number = how many the same the second is standard deviation
std::pair<int,float> row_uniformity(int board[4]);
int get_real_num(int num);

float standard_deviation(float total, int board[4], int count);

int * get_col_arr(int num, int board[4][4]);

float euclid(std::pair<int,int> cords, int midX, int midY);
float distance(int board[4][4]);

int free_squares(int board[4][4]);


std::pair<int,int> get_random_square(std::vector<std::pair<int,int>> &empties);

std::vector<std::pair<int,int>> get_free_squares(int board[4][4]);

int get_number();

void init_game();

void get_movment(Dir dir, int board[4][4]);

//I need to move this over to main
//I'm literally just copying functions and renaiming them

float get_eval(float *strats, int board[4][4]);

float monte_carlo(float *strats, int board[4][4]);

void copy_arr(int source[4][4], int destination[4][4]);

int gameLoop(float strats[6]);

int get_result(int board[4][4]);

Dir get_maxx(std::unordered_map<Dir,float> &dic);

int gen_score(int board[4][4]);

float generateRandomFloat();


void gen_random_strats(float strat[6]);

void adjust_strat(float strat[6], float best[6]);

void get_best_strat(float one[6], float two[6], float three[6]);



float *get_smart();







#endif
