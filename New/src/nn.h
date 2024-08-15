//input layer 16
//hiden layer1 16
//hidden layer2 16
//output layer 4

#ifndef NN_H
#define NN_H 

#define ITERATIONS 10000
#define LAYER_1 16
#define LAYER_2 16
#define OUTPUT_LAYER 4
#define SCALER .01
#define ALPHA 0.01
#define NN_NUMBER 10
#define RANDOM_INDEX 5

#include <random>
#include "game.h"
#include <utility>
#include <limits>
#include <iostream>
#include <cassert>
#include <unordered_map>

using Weights = float*;
inline void print_bools(bool b){b ? std::cout << "True" : std::cout << "false";}
float get_random_float();
float get_random_scaler();
void init_weights(float *arr, int size);
float *create_weights(int num);
void multiply_layers(float *arr1, float *arr2, int size1, int size2, float *output_arr);
void reset_arr(int *arr, int size);
float get_random_tile();
int get_scaled_num(int num);
void zero_arr(float *arr, int size);
void zero_arr(int *arr, int size);
Direction get_max(float *arr, int board[4][4]);
void update_layer(float *best_layer, float *worse_layer, int range);
void leaky_relu(float *inputs, int size);
void convert_2d_to_one(int two_d[4][4], float *one_d);
inline int convert_cords(int pos1, int pos2){
  return pos1 * 4 + pos2;
}
inline void update_board(int num, int cord1, int cord2, float *board){
  board[convert_cords(cord1,cord2)] = get_scaled_num(num);
}

void update(int board[4][4], float *my_board);
int get_best_weights(int arr[10]);
Direction run_through_NN(float *inputs, float *w1, float *w2, float *w3, int board[4][4]);
int get_results(float *w1, float *w2, float *w3);
//returns the best score
int run();

#endif
