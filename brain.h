#ifndef BRAIN_H
#define BRAIN_H 
#define ITERATIONS 1000
#include <random>
#include <utility>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <iostream>
#include <limits>
#include <string>

enum Dir{
  N,
  L,
  R,
  D,
  U
};


float generateRandomFloat();
int gen_score(int board[4][4]);
void copy_arr(int source[4][4], int destination[4][4]);
int get_random_num();
int * make_col_arr(int num, int board[4][4]);
int get_real_num(int num);
float standard_deviation(float total, int board[4], int count);
std::pair<int,float> row_uniformity(int board[4]);
float get_distance(int board[4][4]);
float euclid(std::pair<int,int> cords, int x, int y);
int get_num_free_squares(int board[4][4]);
std::pair<int,int> get_random_pos(std::vector<std::pair<int,int>> &empties);
std::vector<std::pair<int,int>> get_avaliable_options(int board[4][4]);
void init_game(int board[4][4]);
void print_board(int board[4][4]);
void adjust_strat(float strat[6], float best[6],int iterations);
void gen_random_strats(float strat[6]);
bool check_l(int board[4][4]);
bool check_r(int board[4][4]);
bool check_u(int board[4][4]);
bool check_d(int board[4][4]);
void clean_row_l(int board[4]);
void clean_row_r(int board[4]);
void move_l(int board[4][4]);
void move_r(int board[4][4]);
void clean_up(int board[4][4], int col);
void clean_down(int board[4][4], int col);
void move_u(int board[4][4]);
void move_d(int board[4][4]);
bool is_legal_move(Dir dir, int board[4][4]);
float get_eval(float strats[6], int board[4][4]);
void get_move(Dir dir, int board[4][4]);
float monte_carlo(float strats[6], int board[4][4], Dir dir);
int loop(float strats[6]);
Dir get_maxx(std::unordered_map<Dir,float> &dic);
void adjust(float a[6], float b[6], float c[6], int s1, int s2, int s3, int iterations);
void print_strats(float strats[6], float avg_score, std::unordered_map<int,std::string> &dic);
void get_best_strat();
void print_dir(Dir dir);
void print_strat(float strats[6]);
#endif
