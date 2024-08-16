//input layer 16
//hiden layer1 16
//hidden layer2 16
//output layer 4

#ifndef NN_H
#define NN_H 

#define ITERATIONS 10000
//#define ITERATIONS 100
#define LAYER_1 16
#define LAYER_2 16
#define OUTPUT_LAYER 4
#define SCALER .001
#define ALPHA 0.01
#define NN_NUMBER 10
#define RANDOM_INDEX 5

#define ROW1 4
#define COL1 4
#define ROW2 4
#define COL2 16
#define ROW3 4
#define COL3 16
#define ROW4 16
#define COL4 4
#define ROW5 4
#define COL5 4
#define ROW6 4
#define COL6 1
#define OUTROW 4
#define OUTCOL 1

#include <random>
#include "game.h"
#include <utility>
#include <limits>
#include <iostream>
#include <cassert>
#include <unordered_map>
#include <vector>

void copy_board(int board[4][4], int empty_board[4][4]);
void mat_mul(float *input, float *weights, float *output, int col);
using Weights = float*;
int get_max_square(int arr[4][4]);
inline void print_bools(bool b){b ? std::cout << "True" : std::cout << "false";}
float get_random_float();
float get_random_scaler();
void init_weights(float *arr, int size);
float *create_weights(int num);
void multiply_layers(float* input, float* weights, int row1, int col1, int row2, int col2, float* output);
void reset_arr(int *arr, int size);
float get_random_tile();
int get_scaled_num(int num);
void zero_arr(float *arr, int size);
void zero_arr(int *arr, int size);
Direction get_max(float *arr, int board[4][4]);
void update_layer(float *best_layer, float *worse_layer, int range);
void leaky_relu(float *inputs, int size);
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
Direction run_through_NN(float *inputs, float *w1, float *w2, float *w3, int board[4][4]);
int get_results(float *w1, float *w2, float *w3);
int run();//returns the best score
Direction get_max_move(std::vector<std::pair<float,Direction>> &vec);
std::vector<Direction> get_possible_moves(int board[4][4]);
Direction get_random_move(std::vector<Direction> &moves);
float get_move_score(int board[4][4], Direction dir);
Direction get_best_move(int board[4][4]);
int search();

#endif
