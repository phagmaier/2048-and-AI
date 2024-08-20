#ifndef NN_H
#define NN_H

#include "value.h"
#include "game.h"
#include "parse.h"
#include <memory>
#include <vector>
#include <iostream>
#include <cassert>
#include <random>
#include <utility>
#include <unordered_map>

#define ALPHA 0.01

using Matrix = std::vector<std::vector<std::shared_ptr<Value>>>;
using PTR = std::shared_ptr<Value>;
using Data_pair = std::pair<std::vector<std::vector<std::vector<PTR>>>, std::vector<std::vector<PTR>>>;
using TABLES = std::vector<std::vector<std::vector<int>>>;
using SCORES = std::vector<std::vector<std::pair<int,float>>>;


std::vector<PTR> convert_score(std::vector<std::pair<int,float>> &score);
inline float getRandomFloat(){
  static std::random_device rd; 
  static std::mt19937 gen(rd());
  static std::uniform_real_distribution<float> dist(0.0f, 1.0f);
  return dist(gen);
}
inline float getRandombias(){
  static std::random_device rd; 
  static std::mt19937 gen(rd());
  static std::uniform_real_distribution<float> dist(0.0f, 10.0f);
  return dist(gen);
}

std::vector<std::vector<PTR>> convert_table(std::vector<std::vector<int>> &score);

Matrix matMul(Matrix &inputs, Matrix &weights);
void apply_bias_and_activation(Matrix &inputs, PTR &bias);
PTR get_error(Matrix &results, Matrix &targets);
Matrix update_weights(Matrix &vec);
inline PTR make_ptr(float val){return std::make_shared<Value>(val);}
inline PTR make_ptr(){return std::make_shared<Value>();}
Matrix make_weights(int rows, int cols);
//need to be able to get the training data i

Data_pair get_data(int num, int vec_size);
Matrix make_zeroes(int rows, int cols);

//need to shuffle the index size because you need to keep 
//track of scores and tables
inline int get_random_index(int vec_size){
  static std::random_device rd; 
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(0.0, vec_size);
  return dist(gen);
}

inline PTR update_bias(PTR &bias){return make_ptr(bias->val + bias->grad * ALPHA);}

void main_loop();


#endif
