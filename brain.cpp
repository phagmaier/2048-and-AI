#include "brain.h"

float generateRandomFloat() {
    // Seed with a real random value, if available
    std::random_device rd;

    // Initialize random number generator
    std::mt19937 gen(rd());

    // Define the range
    std::uniform_real_distribution<> dis(0.1, 0.9);

    // Generate the random number
    return dis(gen);
}

int gen_score(int board[4][4]){

  std::cout << "generating scores\n";
  int total=0;
  for (int i=0;i<4;++i){
    for (int x=0;x<4;++x){
      total+= board[i][x];
    }
  }
  return total;
}

void copy_arr(int source[4][4], int destination[4][4]){

  std::cout << "copying an array\n";
  for (int i=0; i<4; ++i){
    for (int x=0; x<4; ++x){
      destination[i][x] = source[i][x];
    }
  }
}

int get_number(){
  std::random_device rd;
  
  std::mt19937 gen(rd());
  
  std::uniform_int_distribution<> distrib(0, 1);
  if (distrib(gen)){
    return 2;
  }
  return 4;
}

int break_tie(int num){
  std::random_device rd;
  
  std::mt19937 gen(rd());
  
  std::uniform_int_distribution<> distrib(0, num-1);
  return distrib(gen);
}

//remeber to delete when done
int * get_col_arr(int num, int board[4][4]){

  std::cout << "making a col\n";
  int *arr = new int[4];
  for (int i=0;i<4;++i){
    arr[i] = board[i][num];
  }
  return arr;
}

int get_real_num(int num){
  int count = 0;
  int number = 2;
  while (number != num){
    number *=2;
    ++count;
  }
  return count;
}

float standard_deviation(float total, int board[4], int count){

  std::cout << "CALCULATED STD\n";
  float sum =0;
  float mean = total /4;
  for (int i=0;i<4;++i){
    sum += std::pow(2,board[i] - mean);
  }
  return sum * (1.0/4.0);
}

//will return both how unform the numbers are 
//and the differences in size
//gives the largest number of same blocks
//and also gives the std
std::pair<int,float> row_uniformity(int board[4]){

  std::cout << "GETTING ROW UNIFORMITY\n";
  int count = 0;
  int total = 0;
  std::unordered_map<int,int> dic;
  for (int i=0;i<4;++i){
      dic[board[i]] +=1;
      if (board[i]){
        total += get_real_num(board[i]);
        ++count;
      }
  }
  int max = 0;
  for (auto &i : dic){
    if (i.second > max){
      max = i.second;
    }
  }
  float deviation = count ? standard_deviation(total,board,count) : 0;
  return {max, deviation};
}

float euclid(std::pair<int,int> cords, int x, int y){
  return std::pow(2,std::sqrt(cords.first - x)) + std::pow(2,std::sqrt(cords.second- y));
}

float distance(int board[4][4]){
  std::cout << "GETTING DISTANCES\n";
  std::pair<int,int> pos;
  int max = 0;
  for (int i=0;i<4;++i){
    for (int x=0; x<4; ++x){
      if (board[i][x] > max){
        max = board[i][x];
        pos.first = i;
        pos.second = x;
      }
    }
  }
  if (pos.first <2){
    if (pos.second < 2){
      return euclid(pos, 1,1);
    }
    else{
      return euclid(pos,1,2);
    }
  }
  if (pos.second < 2){
    return euclid(pos,2,1);
  }
  return euclid(pos,2,2);
}

int free_squares(int board[4][4]){
  std::cout << "GETTING NUMBER OF SQUARES\n";
  int total = 0;
  for (int i=0; i<4;++i){
    for (int x=0;x<4;++x){
      if (!board[i][x]){
        ++total;
      }
    }
  }
  return total;
}


std::pair<int,int> get_random_square(std::vector<std::pair<int,int>> &empties){
  //std::pair<int,int> position; 
  
  std::random_device rd;

  // Initialize the random number generator with the seed
  std::mt19937 gen(rd());

  // Define the range for the random index (0 to list.size() - 1)
  std::uniform_int_distribution<> indexes(0, empties.size() - 1);

  //std::uniform_int_distribution<> col_indexes(0, cols.size() - 1);

  return empties[indexes(gen)];
}

std::vector<std::pair<int,int>> get_free_squares(int board[4][4]){
  std::cout << "GETTING OPEN POSITIONS \n";
  std::vector<std::pair<int,int>> empties;
  for (int i=0;i<4;++i){
    for (int x=0;x<4;++x){
      if (!board[i][x]){
        empties.push_back({i,x});
      }
    }
  }
  return empties;
}


void init_game(int board[4][4]){
  std::cout << "INITIALIZING THE GAME\n";
  for (int i=0;i<4;++i){
    for (int x=0;x<4;++x){
      board[i][x] = 0;
    }
  }

  std::vector<std::pair<int,int>> empties = get_free_squares(board);
  std::pair<int,int> pos = get_random_square(empties);
  board[pos.first][pos.second] = get_number();

  empties = get_free_squares(board);
  pos = get_random_square(empties);
  board[pos.first][pos.second] = get_number();

}


float get_eval(float *strats, int board[4][4]){
  std::cout << "GETTING THE EVALUATIOn\n";
  float same_total_row=0;
  float same_total_col = 0;
  float std_total_row =0;
  float std_total_col = 0;
  for (int i=0; i<4; ++i){
    std::pair<int,float> temp = row_uniformity(board[i]);
    same_total_row += temp.first;
    std_total_row += temp.second;

    int *arr = get_col_arr(i,board);
    std::pair<int,float> temp2 = row_uniformity(arr);
    same_total_col += temp2.first;
    std_total_col += temp2.second;
    delete arr;
  }
  //need to actually make the rows into col arrays
  //that also need to be freed
  int num_free = free_squares(board);
  float dis = distance(board);
  same_total_row/=4;
  same_total_col/=4;
  std_total_row/=4;
  std_total_col/=4;
  float results = 0;
  results += num_free * strats[0];
  results += dis * strats[1];
  results += same_total_row * strats[2];
  results += same_total_col * strats[3];
  results += std_total_row * strats[4];
  results += std_total_col * strats[5];
  return results;
}



//pretending the move was made and now we are evaluating 
//the score given 10 random numbers in random places
//in the gameloop we will then pick the option 
//of whatever gets the highest score
//at first strats will start out uniform
float monte_carlo(float *strats, int board[4][4]){
  std::cout << "STARTING MONTE CARLO\n";
  std::cout<< "THE PROBLEM IS IN MONTE CARLO SOMEWHERE CAN'T GET OPEN SQUARES FOR SOME REASON\n";
  float total=0;
  for (int iterations=0;iterations<10;++iterations){
    int new_board[4][4]; 
    for (int i=0;i<4;++i){
      for (int x=0;x<4;++x){
        new_board[i][x] = board[i][x];
      }
    }
    std::vector<std::pair<int,int>> empites = get_free_squares(new_board);
    std::pair<int,int> pos = get_random_square(empites);
    new_board[pos.first][pos.second] = get_number();
    total+= get_eval(strats,new_board);
  }
  std::cout << "IF THIS PRINTS THE PROBLEM ISN'T IN MONTE CARLO\n";
  return total/10; //will have to do this with left right up and down (if possible to make all those choices)
}



bool check_l(int board[4][4]){
  std::cout << "STARTING L CHECK\n";
  for (int i=0; i<4; ++i){
    for (int x=0; x<3; ++x){
      if (board[i][x] == 0 || board[i][x] == board[i][x+1]){
        if (board[i][x] || board[i][x+1]){
          return true;
        }
      }
    }
  }
  return false;
}

bool check_r(int board[4][4]){
  std::cout << "STARTING R CHECK\n";
  for (int i=0; i<4; ++i){
    for (int x=0; x<3; ++x){
      if (board[i][x+1] == 0 || board[i][x+1] == board[i][x]){
        if (board[i][x] || board[i][x+1]){
          return true;
        }

      }
    }
  }
  return false;
}


bool check_u(int board[4][4]){
  std::cout << "STARTING U CHECK\n";
  for (int i=0; i<3; ++i){
    for (int x=0; x<4; ++x){
      if (board[x][i] == 0 || board[x][i+1] == board[x][i]){
        if (board[i][x] || board[i][x+1]){
          return true;
        }
      }
    }
  }
  return false;
}


bool check_d(int board[4][4]){
  std::cout << "STARTING D CHECK\n";
  for (int i=0; i<3; ++i){
    for (int x=0; x<4; ++x){
      if (board[x][i+1] == 0 || board[x][i+1] == board[x][i]){
        if (board[i][x] || board[i][x+1]){
          return true;
        }
      }
    }
  }
  return false;
}

void clean_left(int board[4]){
  std::cout << "CLEANING LEFT\n";
  int count = 0;
  for (int i=0; i<4; ++i){
    if (board[i]){
      board[count] = board[i];
      ++count;
    }
  }
  for (; count<4; ++count){
    board[count] = 0; 
  }
}

void clean_right(int board[4]){
  std::cout << "CLEANING RIGHT\n";
  int count = 3;
  for (int i=3; i> -1; --i){
    if (board[i]){
      board[count] = board[i];
      --count;
    }
  }
  for (; count> -1; --count){
    board[count] = 0; 
  }
}



void move_l(int board[4][4]){
  std::cout << "MOVING LEFT\n";
  for (int i=0;i<4;++i){
    clean_left(board[i]);
    for (int x=0; x<3; ++x){
      if (board[i][x] > 0 && board[i][x] == board[i][x+1]){
        board[i][x] *=2;
        board[i][x+1] = 0;
      }
    }
    clean_left(board[i]);
  }
  /*
  std::vector<std::pair<int,int>> empties = get_free_squares(board);
  std::pair<int,int> pos = get_random_square(empties);
  board[pos.first][pos.second] = get_number();
  */
}


void move_r(int board[4][4]){
  std::cout << "MOVING right\n";
  for (int i=0;i<4;++i){
    clean_right(board[i]);
    for (int x=3; x>0; --x){
      if (board[i][x] > 0 && board[i][x] == board[i][x-1]){
        board[i][x] *=2;
        board[i][x-1] = 0;
      }
    }
    clean_right(board[i]);
  }
  /*
  std::vector<std::pair<int,int>> empties = get_free_squares(board);
  std::pair<int,int> pos = get_random_square(empties);
  board[pos.first][pos.second] = get_number();
  */
}


void clean_up(int board[4][4], int col){
  std::cout << "CLEANING UP\n";
  int count = 0;
  for (int i = 0; i < 4; ++i) {
    if (board[i][col]) {
      board[count][col] = board[i][col];
      ++count;
    }
  }
  for (; count < 4; ++count) {
    board[count][col] = 0;
  }
}

void clean_down(int board[4][4], int col){
  std::cout << "CLEANING DOWN\n";
  int count = 3;
  for (int i = 3; i >= 0; --i) {
    if (board[i][col]) {
      board[count][col] = board[i][col];
      --count;
    }
  }
  for (; count >= 0; --count) {
    board[count][col] = 0;
  }
}

void move_u(int board[4][4]){
  std::cout << "MOVING UP\n";
  for (int col = 0; col < 4; ++col) {
    clean_up(board, col);
    for (int row = 0; row < 3; ++row) {
      if (board[row][col] > 0 && board[row][col] == board[row + 1][col]) {
        board[row][col] *= 2;
        board[row + 1][col] = 0;
      }
    }
    clean_up(board, col);
  }
  /*
  std::vector<std::pair<int, int>> empties = get_free_squares(board);
  if (!empties.empty()) {
    std::pair<int, int> pos = get_random_square(empties);
    board[pos.first][pos.second] = get_number();
  }
  */
}

void move_d(int board[4][4]){
  std::cout << "MOVING DOWN\n";
  for (int col = 0; col < 4; ++col) {
    clean_down(board, col);
    for (int row = 3; row > 0; --row) {
      if (board[row][col] > 0 && board[row][col] == board[row - 1][col]) {
        board[row][col] *= 2;
        board[row - 1][col] = 0;
      }
    }
    clean_down(board, col);
  }
  /*
  std::vector<std::pair<int, int>> empties = get_free_squares(board);
  if (!empties.empty()) {
    std::pair<int, int> pos = get_random_square(empties);
    board[pos.first][pos.second] = get_number();
  }
  */
}


void get_movment(Dir dir, int board[4][4]){
  std::cout << "GETTING MOVMENT TO MAKE \n";
  if (dir == L){
    move_l(board);
    return;
  }
  if (dir == R){
    move_r(board);
    return;
  }
  if (dir == U){
    move_u(board);
    return;
  }
  move_d(board);
}

int get_result(int board[4][4]){
  std::cout << "GETTING RESULTS\n";
  int total = 0;
  for (int i=0;i<4;++i){
    for (int x=0;x<4;++x){
      total += board[i][x];
    }
  }
  return total;
}



Dir get_maxx(std::unordered_map<Dir, float> &dic) {
  std::cout << "GETTING MAXX\n";
    Dir dir = N;
    //float maxx = -1; // Initialize maxx to a very low value
    float maxx = -std::numeric_limits<float>::infinity();
    for (auto &i : dic) {
        if (i.second > maxx) {
            maxx = i.second;
            dir = i.first;
        }
    }
    return dir;
}

void print_board(int board[4][4]){
  for (int i=0;i<4;++i){
    for (int x=0;x<4;++x){
      std::cout << board[i][x] << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n\n\n\n\n";
}

//should probably do a random sample
//score after going right and after going left

//row std 
//row number of same vals
//col stdd 
//col number of same vals 
//number of empty squares
//euclidian distance largest tile from the center square

int gameLoop(float strats[6]) {
    bool over = false;
    int board[4][4];
    init_game(board);

    while (!over) {
        std::unordered_map<Dir, float> scores;

        bool left = check_l(board);
        bool right = check_r(board);
        bool up = check_u(board);
        bool down = check_d(board);
        if (left) {
            int l_board[4][4];
            copy_arr(board, l_board);
            move_l(l_board);
            scores[L] = monte_carlo(strats, l_board);
        }
        else{
          scores[L] = -std::numeric_limits<float>::infinity();
        }
        if (right) {
            int r_board[4][4];
            copy_arr(board, r_board);
            move_r(r_board);
            scores[R] = monte_carlo(strats, r_board);
        }
        else{
          scores[R] = -std::numeric_limits<float>::infinity();
        }
        if (up) {
            int u_board[4][4];
            copy_arr(board, u_board);
            move_u(u_board);
            scores[U] = monte_carlo(strats, u_board);
        }
        else{
          scores[U] = -std::numeric_limits<float>::infinity();
        }
        if (down) {
            int d_board[4][4];
            copy_arr(board, d_board);
            move_d(d_board);
            scores[D] = monte_carlo(strats, d_board);
        }
        else{
          scores[D] =-std::numeric_limits<float>::infinity();
        }

        Dir dir = get_maxx(scores);
        if (dir != N) {
            get_movment(dir, board);
            std::vector<std::pair<int, int>> empties = get_free_squares(board);
            if (!empties.empty()) {
                std::pair<int, int> pos = get_random_square(empties);
                board[pos.first][pos.second] = get_number();
            }
        } else {
            //print_board(board);
            return gen_score(board);
        }
    }
    std::cout << "ERROR THIS SHOULD NEVER PRINT ERROR IN GAME LOOP\n";
    return -1;
}



void adjust_strat(float strat[6], float best[6]){
  std::cout << "ADJUSTING STRAT\n";
  for (int i=0;i<6;++i){
    if (best[i] > strat[i]){
      strat[i]+= strat[i] * generateRandomFloat();
    }
    else{
      strat[i] -= strat[i] * generateRandomFloat();
    }
  }
}

void get_best_strat(float one[6], float two[6], float three[6]){
  std::cout << "GETTING BEST STRAT\n";
  if (one >= two && one >= three){
    adjust_strat(two,one);
    adjust_strat(three,one);
  }
  if (two >= one && two >= three){
    adjust_strat(one,two);
    adjust_strat(three,two);
  }
  else{
    adjust_strat(one,three);
    adjust_strat(two,three);
  }
}



void gen_random_strats(float strat[6]){
  std::cout << "GENERATING RANDOM STRAT\n";
  for (int i=0;i<6;++i){
    strat[i] = generateRandomFloat();
  }
}

float *get_smart(){
  std::cout << "GETTING SMART \n";
  float one[6];
  for (int i=0;i<6;++i){
    one[i] = 1.0/6.0;
  }
  float two[6];
  float three[6];
  gen_random_strats(two);
  gen_random_strats(three);
  
  for (int i=0;i<1000;++i){
    float score_one = gameLoop(one);
    float score_two = gameLoop(two);
    float score_three = gameLoop(three);
    get_best_strat(one,two,three);
  }

    float score_one = gameLoop(one);
    float score_two = gameLoop(two);
    float score_three = gameLoop(three);

    if (score_one >= score_two && score_one >= score_three){
      float *final = new float[6];
      for (int i=0;i<6;++i){
        final[i] = one[i];
      }
      return final;
    }

    if (score_two >= score_one && score_one >= score_three){
      float *final = new float[6];
      for (int i=0;i<6;++i){
        final[i] = two[i];
      }
      return final;
    }

  float *final = new float[6];
      for (int i=0;i<6;++i){
        final[i] = three[i];
      }
      return final;
}
