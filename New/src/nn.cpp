#include "nn.h"


void print_dir(Direction dir){
  switch (dir){
    case None:
      std::cout << "NONE\n";
      break;
    case Left:
      std::cout << "LEFT\n";
      break;
    case Right:
      std::cout << "RIGHT\n";
      break;
    case Down:
      std::cout << "DOWN\n";
      break;
    case Up:
      std::cout << "UP\n";
      break;
    default:
      std::cout << "THIS SHOULD ABSOLUTLEY NEVER PRINT\n";
  }
}

void zero_arr(float *arr, int size){
  for (int i=0;i<size;++i){
    arr[i] = 0;
  }
}

void zero_arr(int *arr, int size){
  for (int i=0;i<size;++i){
    arr[i] = 0;
  }
}

float get_random_float(){
  static std::default_random_engine generator;
  std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);
  return distribution(generator);
}

float *create_weights(int num){
  float *arr = new float[num];
  for (int i=0; i<num;++i){
    arr[i] = get_random_float();
  }
  return arr;
}


float get_random_scaler(){
static std::default_random_engine generator;
  std::uniform_real_distribution<float> distribution(0.9f, 0.01);
  return distribution(generator);
}

float get_random_tile(){
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_int_distribution<> distrib(1, 10);
  if (distrib(gen) > 1) {
    return 2;
  }
  return 4;
}

void init_weights(float *arr, int size){
  for (int i=0;i<size;++i){
    arr[i] = get_random_float();
  }
}

void leaky_relu(float *inputs, int size){
    for (int i=0; i<size; ++i) {
        inputs[i] = (inputs[i] > 0) ? inputs[i] : ALPHA * inputs[i];
    }
}

//arr1 will be the values arr2 will be the weights
void multiply_layers(float *input, float *weights, int in_size, int weights_size, float *output){
  for (int i=0; i<weights_size; ++i){
    for (int x=0;x<in_size;++x){
      output[i] += input[x] * weights[i];
    }
  }
}

int get_scaled_num(int num) {
    int original = num;
    int count = 0;
    int number = 2;
    while (number < num) {
        number *= 2;
        ++count;
    }
    return count+1;
}

Direction get_max(float *arr, int board[4][4]){
  static std::unordered_map<int,Direction> dic = {
  {0,Left},{1,Right}, {2,Down}, {3,Up}
  };
  Direction dir = None;
  float maxx = -std::numeric_limits<float>::infinity();
  for (int z=0;z<4;++z){
    if (is_legal_move(dic[z], board)){
      if (arr[z] > maxx){
        maxx = arr[z];
        dir = dic[z];
      }
    }
  }
  assert(dir !=None);

  return dir;
}

//at first going to try and just update it by .01
void update_layer(float *best_layer, float *worse_layer, int range){
  for (int i=0; i<range;++i){
    if (worse_layer[i] >= 0){
      worse_layer[i] += best_layer[i] > worse_layer[i] ? worse_layer[i] * SCALER : -worse_layer[i] * SCALER;
    }
    else{
      worse_layer[i] -= best_layer[i] > worse_layer[i] ? worse_layer[i] * SCALER : -worse_layer[i] * SCALER;
    }
  }
}

void convert_2d_to_one(int two_d[4][4], float *one_d){
  for (int i=0; i<4;++i){
    for (int x=0;x<4;++x){
      one_d[convert_cords(i,x)] = (float)two_d[i][x];
    }
  }
}

void update(int board[4][4], float *my_board){
  for (int i=0;i<4;++i){
    for (int x=0;x<4;++x){
      if (board[i][x]){
      my_board[convert_cords(i,x)] = board[i][x];
      }
      else{
        my_board[convert_cords(i,x)] = 0;
      }
    }
  }
}

Direction run_through_NN(float *inputs, float *w1, float *w2, float *w3, int board[4][4]){
  float hidden1[16];
  float hidden2[16];
  float outputs[4];
  zero_arr(hidden1, 16);
  zero_arr(hidden2, 16);
  zero_arr(outputs, 4);
  multiply_layers(inputs, w1,LAYER_1,LAYER_1,hidden1);
  //for now not gonna use the relu activation function
  //leaky_relu()
  multiply_layers(hidden1,w2, LAYER_1, LAYER_2, hidden2);
  //for now not gonna use the relu activation function
  //leaky_relu()
  multiply_layers(hidden2,w3, LAYER_2, OUTPUT_LAYER, outputs);
  //for now not gonna use the relu activation function
  //leaky_relu()
  return get_max(outputs, board);
}
int get_best_weights(int arr[NN_NUMBER]){
  int maxx = -1;
  int index = -1;
  for (int i=0;i<NN_NUMBER; ++i){
    if (arr[i] > maxx){
      index = i;
      maxx = arr[i];
    }
  }
  return index;
}

//this actually needs to take in all the weights
int get_results(float *w1, float *w2, float *w3){
  //float *inputs, float *w1, float *w2, float *w3
  int twoD[4][4];
  float oneD[LAYER_1];
  //float w1[LAYER_1];
  //float w2[LAYER_2];
  //float w3[OUTPUT_LAYER];
  new_game(twoD);
  update(twoD,oneD);
  init_weights(w1, LAYER_1);
  init_weights(w2, LAYER_2);
  init_weights(w3, OUTPUT_LAYER);
  while (!is_over(twoD)){
    Direction dir = run_through_NN(oneD,w1,w2,w3, twoD);
    move(dir, twoD);
    update(twoD,oneD);
  }
  return get_score(twoD);
}

//5 of the arrays are going to be completley random each time
int run(){
  int scores[NN_NUMBER];
  zero_arr(scores, NN_NUMBER);
  Weights w1s[NN_NUMBER];
  Weights w2s[NN_NUMBER];
  Weights w3s[NN_NUMBER];
  for (int i=0; i<NN_NUMBER; ++i){
    w1s[i] = create_weights(LAYER_1);
    w2s[i] = create_weights(LAYER_2);
    w3s[i] = create_weights(OUTPUT_LAYER);
  }

  for (int i=0; i<ITERATIONS; ++i){
    std::cout << "ON ITERATION " << i << "\n";
    std::cout << "---------------------------\n";
    int best_index = 0;
    for (int x=0;x<NN_NUMBER;++x){
      scores[x] = get_results(w1s[x],w2s[x],w3s[x]);
    }
    best_index = get_best_weights(scores);
    for (int x=0; x<RANDOM_INDEX;++x){
      if (x!=best_index){
        update_layer(w1s[best_index], w1s[x], LAYER_1);
        update_layer(w2s[best_index], w2s[x], LAYER_2);
        update_layer(w3s[best_index], w3s[x], OUTPUT_LAYER);
      }
    }

    for (int x=RANDOM_INDEX; x<NN_NUMBER;++x){
      if (x!=best_index){
        init_weights(w1s[x],LAYER_1);
        init_weights(w2s[x],LAYER_2);        
        init_weights(w3s[x],OUTPUT_LAYER);
      }
    }
  }

  for (int i=0;i<NN_NUMBER;++i){
    delete w1s[i];
    delete w2s[i];
    delete w3s[i];
  }

  int best_index = get_best_weights(scores);
  for(int i=0;i<NN_NUMBER;++i){
    scores[i] = get_results(w1s[i],w2s[i],w3s[i]);

    best_index = get_best_weights(scores);
  }
  return scores[best_index];
}




