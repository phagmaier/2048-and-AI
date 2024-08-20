#ifndef NN_H
#define NN_H 

//#define ITERATIONS 10000
#define ITERATIONS 100
#define ALPHA 0.01
#define NN_NUMBER 10
#define IN_ROWS 4
#define IN_COLS 4
#define W1_ROWS 4
#define W1_COLS 4
#define H1_ROWS 4
#define H1_COLS 16
#define W2_ROWS 16
#define W2_COLS 6
#define H2_ROWS 4
#define H2_COLS 4
#define W3_ROWS 4
#define W3_COLS 1
#define OUTPUT_LAYER 4

#include "game.h"
#include "value.h"
#include <random>
#include <utility>
#include <limits>
#include <iostream>
#include <cassert>
#include <unordered_map>
#include <vector>

using Weights = float*;
void copy_board(int board[4][4], int empty_board[4][4]);
void mat_mul(float *input, float *weights, float *output, int col);
inline void print_bools(bool b){b ? std::cout << "True" : std::cout << "false";}
float get_random_float();
void init_weights(float *arr, int size);
float *create_weights(int num);
void multiply_layers(Value *input, Value *weights, int row1, int col1, int row2, int col2, Value *output);
void reset_arr(int *arr, int size);
int get_scaled_num(int num);
void zero_arr(Value *arr, int size);
void zero_arr(int *arr, int size);
Direction get_max(float *arr, int board[4][4]);
void update_layer(Value *weights, int rows, int cols);
void convert_2d_to_one(int two_d[4][4], float *one_d);
inline int convert_cords(int row, int col){
  return row * 4 + col;
}
inline int convert_cords(int row, int col, int num_cols){
  return row * num_cols + col;
}

inline void update_board(int num, int cord1, int cord2, float *board){
  board[convert_cords(cord1,cord2)] = get_scaled_num(num);
}

void update(int board[4][4], float *my_board);
int get_best_weights(int arr[10]);
Direction run_through_NN(Value *inputs, Value *w1, Value *w2, Value *w3, int board[4][4]);
int get_results(float *w1, float *w2, float *w3);
int run();//returns the best score
Direction get_max_move(std::vector<std::pair<float,Direction>> &vec);
std::vector<Direction> get_possible_moves(int board[4][4]);
Direction get_random_move(std::vector<Direction> &moves);
float get_move_score(int board[4][4], Direction dir);
Direction get_best_move(int board[4][4]);
int search();

#endif
