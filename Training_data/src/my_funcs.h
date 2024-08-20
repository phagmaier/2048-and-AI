
#ifndef MY_FUNCS_H
#define MY_FUNCS_H 

//#define ITERATIONS 10000
//#define ITERATIONS 100
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
#include <random>
#include <utility>
#include <limits>
#include <iostream>
#include <cassert>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <thread>
#include <mutex>

//using Weights = float*;

extern std::mutex file_mutex;
void write_board(int board[4][4]);
std::string dir_to_string(Direction dir);
void print_dir(Direction dir);
void copy_board(int board[4][4], int empty_board[4][4]);
int get_scaled_num(int num);
void zero_arr(int *arr, int size);
Direction get_max(float *arr, int board[4][4]);
Direction get_max_move(std::vector<std::pair<float,Direction>> &vec);
std::vector<Direction> get_possible_moves(int board[4][4]);
Direction get_random_move(std::vector<Direction> &moves);
float get_move_score(int board[4][4], Direction dir);
Direction get_best_move(int board[4][4]);
int search();

#endif

