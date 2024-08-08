#include "NN.h"

void unroll(int arr[4][4], Value vec[16]){
  int count = 0;
  for (int i=0; i<4;++i){
    for (int x=0; x<4;++i){
      vec[count].val = arr[i][x];
      vec[count].grad = 0;
    }
  }
}

float get_random_float(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> dis(-1.0, 1.0);
    return dis(gen);
}

void init_weights(int num, Value *weights){
  for (int i=0; i<num; ++i){
    weights[i] = Value(get_random_float());
    weights[i].grad = 0;
  }
}

//num1 tells you how many nodes in previous section
//num2 tells you how many nodes we need to make
//need to make sure you init all of them to 0 first
//or whatever the value of the square is
void matMul(int num1, int num2, Value *mat1, Value *mat2, Value *results){
  const int limit = num1*num2;
  int n1 = 0;
  int n2 = 0;
  int count = 0;
  for (int i=0; i< limit; ++i){
    if (count < num1){
      Value temp = mat1[n1] * mat2[i];
      results[n2] = results[n2] + temp;
      ++count;
      ++n1;
    }
    else{
      count = 0; 
      n1=0;
      ++n2;
      Value temp = mat1[n1] * mat2[i];
      results[n2] = results[n2] + temp;
    }
  }
}


void apply_activation(int num, Value *arr, Value *results){
  for (int i=0; i<num;++i){
    results[i] = arr[i].relu();
  }
}

//will have to return the weights at some point
void nn(int original[4][4]){
  const int ONE = 16;
  const int TWO = ONE * ONE;
  const int THREE = ONE * 4;
  Value arr[ONE] = {Value()};
  unroll(original,arr);
  Value W1[TWO];
  Value W2[THREE];
  init_weights(TWO, W1);
  init_weights(THREE,W2);
  Value inter1[ONE];
  Value act1[ONE];
  Value inter2[4];
  Value final[4];
   
}
