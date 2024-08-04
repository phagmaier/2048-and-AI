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

//I need to move this over to main
//I'm literally just copying functions and renaiming them

float get_eval(float *strats, int board[4][4]);

float monte_carlo(float *strats, int board[4][4]);


void gameLoop(float strats[6]);





#endif
