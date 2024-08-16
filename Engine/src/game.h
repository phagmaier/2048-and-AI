#ifndef GAME_H
#define GAME_H

#include <random>
#include <iostream>
#include <vector>
#include <utility>
#include <string>


enum Direction{
  None,
  Left,
  Right,
  Down,
  Up
};
void print_board(int arr[4][4]);
void print_dir(Direction dir);
int get_random_int();
std::pair<int, int> get_pos(std::vector<std::pair<int, int>> &empties);
std::vector<std::pair<int, int>> get_empties(int board[4][4]);
bool check_left(int board[4][4]);
bool check_right(int board[4][4]);
bool check_up(int board[4][4]);
bool check_down(int board[4][4]);
void clean_row_left(int board[4]);
void clean_row_right(int board[4]);
void move_left(int board[4][4]);
void move_right(int board[4][4]);
void clean_column_up(int board[4][4], int col);
void clean_column_down(int board[4][4], int col);
void move_up(int board[4][4]);
void move_down(int board[4][4]);
bool is_legal_move(Direction dir, int board[4][4]);
void start_game(int board[4][4]);
void move(Direction dir,int board[4][4]);
bool is_over(int board[4][4]);
int get_score(int board[4][4]);
void new_game(int board[4][4]);
#endif
