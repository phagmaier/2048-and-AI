#include "nn.h"

void copy_board(int board[4][4], int empty_board[4][4]){
  for (int i=0;i<4;++i){
    for (int x=0;x<4;++x){
      empty_board[i][x] = board[i][x];
    }
  }
}

int get_max_square(int arr[4][4]){
  int maxx = 0;
  for (int i=0;i<4;++i){
    for (int x=0;x<4;++x){
      if (arr[i][x] > maxx){
        maxx = arr[i][x];
      }
    }
  }
  return maxx;
}


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

float get_random_float() {
    static std::random_device rd;
    static std::default_random_engine generator(rd());
    static std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);  // Static distribution
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

void relu(float *inputs, int size) {
    for (int i = 0; i < size; ++i) {
        inputs[i] = std::max(0.0f, inputs[i]);
    }
}

void leaky_relu(float *inputs, int size){
    for (int i=0; i<size; ++i) {
        inputs[i] = (inputs[i] > 0) ? inputs[i] : ALPHA * inputs[i];
    }
}

//this is wrong
//arr1 will be the values arr2 will be the weights

/*
void multiply_layers(float *input, float *weights, int in_size, int weights_size, float *output){
  for (int i=0; i<weights_size; ++i){
    for (int x=0;x<in_size;++x){
      output[i] += input[x] * weights[i];
    }
  }
}

//all out matrixes are going to be flat but are technically '2d'
void multiply_layers(float *input, float *weights, int row1, int col1, int row2, 
                     int col2, float *output){
  int count = 0;
  for (int i=0; i<row1;++i){
    for (int x=0;x<col2; ++i){
      output[count++] += input[(convert_cords(i,x,col1))] * weights[(convert_cords(i,x,col2))];
    }
  }
}

*/

void multiply_layers(float* input, float* weights, int row1, int col1, int row2, int col2, float* output) {
    // Check for dimension compatibility: col1 must be equal to row2
    if (col1 != row2) {
        std::cerr << "Matrix dimensions do not match for multiplication!" << std::endl;
        return;
    }

    for (int i = 0; i < row1; ++i) {
        for (int j = 0; j < col2; ++j) {
            float sum = 0;
            for (int k = 0; k < col1; ++k) {
                sum += input[convert_cords(i, k, col1)] * weights[convert_cords(k, j, col2)];
            }
            output[convert_cords(i, j, col2)] = sum;
        }
    }
}




/*
void multiply_layers(float *input, float *weights, int in_size, int weights_size, float *output) {
    // Initialize the output array to zero
    //std::fill_n(output, weights_size, 0);

    // Compute the weighted sum for each output neuron
    for (int i = 0; i < weights_size; ++i) {
      output[i] = 0;
        for (int j = 0; j < in_size; ++j) {
            output[i] += input[j] * weights[i * in_size + j];
        }
    }
}
*/

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
  //static int row2 =-1;
  float hidden1[ROW3 * COL3];
  float hidden2[ROW5 * COL5];
  float outputs[OUTPUT_LAYER];
  zero_arr(hidden1, LAYER_1);
  zero_arr(hidden2, LAYER_2);
  zero_arr(outputs, OUTPUT_LAYER);

  multiply_layers(inputs, w1,ROW1,COL1,ROW2,COL2,hidden1);
  //leaky_relu(hidden1,LAYER_1);
  relu(hidden1, ROW3 * COL3);
  multiply_layers(hidden1,w2,ROW3,COL3,ROW4,COL4, hidden2);
  //leaky_relu(hidden2,LAYER_2);
  relu(hidden2, ROW5 * COL6);
  multiply_layers(hidden2,w3,ROW4,COL4,ROW5,COL5,outputs);
  //leaky_relu(outputs,OUTPUT_LAYER);
  relu(outputs, OUTPUT_LAYER);
  return get_max(outputs, board);
}
int get_best_weights(float arr[NN_NUMBER]){
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
  //init_weights(w1, LAYER_1);
  //init_weights(w2, LAYER_2);
  //init_weights(w3, OUTPUT_LAYER);
  while (!is_over(twoD)){
    Direction dir = run_through_NN(oneD,w1,w2,w3, twoD);
    move(dir, twoD);
    update(twoD,oneD);
  }
  //print_board(twoD);
  //std::cout << "\n\n";
  return get_score(twoD);
  //return get_max_square(twoD);
}

//5 of the arrays are going to be completley random each time

int run() {
    float scores[NN_NUMBER];
    zero_arr(scores, NN_NUMBER);
    Weights w1s[NN_NUMBER];
    Weights w2s[NN_NUMBER];
    Weights w3s[NN_NUMBER];
    
    for (int i = 0; i < NN_NUMBER; ++i) {
        w1s[i] = create_weights(ROW2 * COL2);
        w2s[i] = create_weights(ROW4 * COL4);
        w3s[i] = create_weights(OUTPUT_LAYER);
    }

    for (int i = 0; i < ITERATIONS; ++i) {
        //std::cout << "ON ITERATION " << i << "\n";
        //std::cout << "---------------------------\n";
        int best_index = 0;
        for (int x = 0; x < NN_NUMBER; ++x) {
          scores[x] = 0;
          for (int z=0;z<10;++z){
            scores[x] += get_results(w1s[x], w2s[x], w3s[x]);
          }
            scores[x] /= 10;
        }
        best_index = get_best_weights(scores);
        if ((i+1) %100 == 0){
          std::cout << "THE BEST SCORE AFTER " << i+1 << " ITERATIONS IS: \n";
          std::cout << scores[best_index] << "\n";
          std::cout << "--------------------------------------\n";
        }
        for (int x = 0; x < RANDOM_INDEX; ++x) {
            if (x != best_index) {
                update_layer(w1s[best_index], w1s[x], LAYER_1);
                update_layer(w2s[best_index], w2s[x], LAYER_2);
                update_layer(w3s[best_index], w3s[x], OUTPUT_LAYER);
            }
        }

        for (int x = RANDOM_INDEX; x < NN_NUMBER; ++x) {
            if (x != best_index) {
                init_weights(w1s[x], LAYER_1);
                init_weights(w2s[x], LAYER_2);        
                init_weights(w3s[x], OUTPUT_LAYER);
            }
        }
    }

    // Deallocate memory at the end when no longer needed
    for (int i = 0; i < NN_NUMBER; ++i) {
        delete[] w1s[i];
        delete[] w2s[i];
        delete[] w3s[i];
    }

    // Determine best index and return score
    int best_index = get_best_weights(scores);
    return scores[best_index];
}

std::vector<Direction> get_possible_moves(int board[4][4]){
  std::vector<Direction> moves;
  if (check_left(board)){
    moves.push_back(Left);
  }
  if (check_right(board)){
    moves.push_back(Right);
  }
  if (check_up(board)){
    moves.push_back(Up);
  }
  if (check_down(board)){
    moves.push_back(Down);
  }
  return moves;
}

Direction get_max_move(std::vector<std::pair<float, Direction>> &vec) {
  float maxx = 0;
  Direction dir;
  for (std::pair<float, Direction> &i : vec) {
    if (i.first > maxx){
      maxx = i.first;
      dir = i.second;
    } 
  }
  return dir;
}


Direction get_random_move(std::vector<Direction> &moves){
  static std::random_device rd; 
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(0, moves.size() - 1); 
  return moves[distr(gen)];
}


float get_move_score(int board[4][4], Direction dir){
  static const int iters = 100;
  float score = 0;
  int arr[4][4];
  copy_board(board,arr);
  move(dir, arr);
  for (int i=0;i<iters;++i){
    int arr2[4][4];
    copy_board(arr,arr2);
    while (!is_over(arr2)){
      //print_board(arr2);
      std::vector<Direction> moves = get_possible_moves(arr2);
      move(get_random_move(moves), arr2);
    }
    score += ((float)get_score(arr2));
  }
  return (float)score/(float)iters;
}


Direction get_best_move(int board[4][4]){
  std::vector<Direction> moves = get_possible_moves(board);
  std::vector<std::pair<float,Direction>> scores;
  for (Direction dir : moves){
    scores.push_back({get_move_score(board, dir),dir});
  }
  return get_max_move(scores);
}

int search(){
  int board[4][4];
  new_game(board);
  while(!is_over(board)){
    move(get_best_move(board),board);
    //print_board(board);
  }
  //print_board(board);
  return get_score(board);
}
