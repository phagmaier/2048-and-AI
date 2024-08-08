#ifndef NN_H
#define NN_H

#include "value.h"
#include "myFunctions.h"
#include <random>

inline int get_index(int x, int y){return x*y;}
void unroll(int arr[4][4], int vec[16]);
void nn(int arr[4][4]);
void max_output(Value);
float intit_weights(int num, Value *weights);
void matMul(int num1, int num2, Value *mat1, Value *mat2, Value *results);
void apply_activation(int num, Value *arr, Value *results);

#endif

