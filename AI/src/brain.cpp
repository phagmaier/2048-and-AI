#include "brain.h"

float generateRandomFloat() {
    // Seed with a real random value, if available
    static std::random_device rd;

    // Initialize random number generator
    static std::mt19937 gen(rd());

    // Define the range
    static std::uniform_real_distribution<> dis(0.1,1);

    // Generate the random number
    return dis(gen);
}

int gen_score(int board[4][4]){
  int total=0;
  for (int i=0;i<4;++i){
    for (int x=0;x<4;++x){
      total+= board[i][x];
    }
  }
  return total;
}

void copy_arr(int source[4][4], int destination[4][4]){
  for (int i=0; i<4; ++i){
    for (int x=0; x<4; ++x){
      destination[i][x] = source[i][x];
    }
  }
}

int get_random_num(){
  static std::random_device rd;
  
  static std::mt19937 gen(rd());
  
  static std::uniform_int_distribution<> distrib(1,10);
  if (distrib(gen) <10){
    return 2;
  }
  return 4;
}

//remeber to delete when done
int * make_col_arr(int num, int board[4][4]){
  int *arr = new int[4];
  for (int i=0;i<4;++i){
    arr[i] = board[i][num];
  }
  return arr;
}

int get_real_num(int num) {
    int original = num;
    int count = 0;
    int number = 2;

    // Check if num is a power of 2
    if ((num & (num - 1)) != 0) {
        std::cout<< "Error: The input number is not a power of 2.\n";
        return -1;
    }

    while (number < num) {
        number *= 2;
        ++count;
    }

    return count;
}


float standard_deviation(float total, int board[4], int count) {
    float sum = 0;
    float mean = total / 4.0;
    for (int i = 0; i < 4; ++i) {
        sum += std::pow(board[i] - mean, 2);
    }
    return std::sqrt(sum / 4.0);
}
//will return both how unform the numbers are 
//and the differences in size
//gives the largest number of same blocks
//and also gives the std
std::pair<int,float> row_uniformity(int board[4]){

  int count = 0;
  int total = 0;
  std::unordered_map<int,int> dic;
  for (int i=0;i<4;++i){
      dic[board[i]] +=1;
      if (board[i]){
        total += get_real_num(board[i]);
        //total += board[i];
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

float get_distance(int board[4][4]){
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

int get_num_free_squares(int board[4][4]){
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




std::pair<int,int> get_random_pos(std::vector<std::pair<int,int>> &empties){
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<> indexes(0, empties.size() - 1);
  return empties[indexes(gen)];
}

std::vector<std::pair<int,int>> get_avaliable_options(int board[4][4]){
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
  std::vector<std::pair<int,int>> empties;
  for (int i=0;i<4;++i){
    for (int x=0;x<4;++x){
      board[i][x] = 0;
      empties.push_back({i,x});
    }
  }

  std::pair<int,int> pos = get_random_pos(empties);
  board[pos.first][pos.second] = get_random_num();

  empties = get_avaliable_options(board);
  pos = get_random_pos(empties);
  board[pos.first][pos.second] = get_random_num();

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


void adjust_strat(float strat[6], float best[6], int iterations){
  //float diff = bad_score/ good_score;
  for (int i=0;i<6;++i){
    if (!strat[i]){
      strat[i] = .001;
    }
    if (best[i] >= strat[i]){
      strat[i]+= strat[i] * (1.0/(iterations*10));
    }
    else{
      strat[i] -= strat[i] * (1.0/(iterations*10));
      if (strat[i] <=0){
        strat[i] = 0.001;
      }
      //strat[i] = strat[i] < 0 ? 0 : strat[i];
    }
  }
}




void gen_random_strats(float strat[6]){
  for (int i=0;i<6;++i){
    strat[i] = generateRandomFloat();
  }
}

bool check_l(int board[4][4]) {
  for (int i = 0; i < 4; ++i) {
    for (int x = 0; x < 3; ++x) {
        if (board[i][x] == 0 && board[i][x+1] != 0) {
            return true;
        }
        if (board[i][x] == board[i][x+1] && board[i][x] != 0) {
            return true;
        }
    }
  }
  return false;
}


bool check_r(int board[4][4]) {

  for (int i = 0; i < 4; ++i) {
        for (int x = 3; x > 0; --x) {
            if (board[i][x] == 0 && board[i][x-1] != 0) {
                return true;
            }
            if (board[i][x] == board[i][x-1] && board[i][x] != 0) {
                return true;
            }
        }
    }
    return false;
}

bool check_u(int board[4][4]) {
  for (int i = 0; i < 3; ++i) {
        for (int x = 0; x < 4; ++x) {
            if (board[i][x] == 0 && board[i+1][x] != 0) {
                return true;
            }
            if (board[i][x] == board[i+1][x] && board[i][x] != 0) {
                return true;
            }
        }
    }
    return false;
}

bool check_d(int board[4][4]) {
  for (int i = 3; i > 0; --i) {
        for (int x = 0; x < 4; ++x) {
            if (board[i][x] == 0 && board[i-1][x] != 0) {
                return true;
            }
            if (board[i][x] == board[i-1][x] && board[i][x] != 0) {
                return true;
            }
        }
    }
    return false;
}

void clean_row_l(int board[4]){
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

void clean_row_r(int board[4]){
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




void move_l(int board[4][4]) {
    for (int i = 0; i < 4; ++i) {
        clean_row_l(board[i]);
        for (int x = 0; x < 3; ++x) {
            if (board[i][x] > 0 && board[i][x] == board[i][x + 1]) {
                board[i][x] *= 2;
                board[i][x + 1] = 0;
            }
        }
        clean_row_l(board[i]);
    }
    std::vector<std::pair<int, int>> empties = get_avaliable_options(board);
    if (empties.size()) {
        std::pair<int, int> pos = get_random_pos(empties);
        board[pos.first][pos.second] = get_random_num();
    }
}


void move_r(int board[4][4]){
  print_board(board);
  for (int i = 0; i < 4; ++i) {
        clean_row_r(board[i]);
        for (int x = 3; x > 0; --x) {
            if (board[i][x] > 0 && board[i][x] == board[i][x - 1]) {
                board[i][x] *= 2;
                board[i][x - 1] = 0;
            }
        }
        clean_row_r(board[i]);
    }
    std::vector<std::pair<int, int>> empties = get_avaliable_options(board);
    if (empties.size()) {
        std::pair<int, int> pos = get_random_pos(empties);
        board[pos.first][pos.second] = get_random_num();
    }
}


void clean_up(int board[4][4], int col){
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
  print_board(board);
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
    std::vector<std::pair<int, int>> empties = get_avaliable_options(board);
    if (empties.size()) {
        std::pair<int, int> pos = get_random_pos(empties);
        board[pos.first][pos.second] = get_random_num();
    }
}


void move_d(int board[4][4]){
  print_board(board);
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
    std::vector<std::pair<int, int>> empties = get_avaliable_options(board);
    if (empties.size()) {
        std::pair<int, int> pos = get_random_pos(empties);
        board[pos.first][pos.second] = get_random_num();
    }

}


bool is_legal_move(Dir dir, int board[4][4]){
  if (dir == L){
    return check_l(board);  
  }
  if (dir == R){
    return check_r(board);
  }
  if (dir == U){
    return check_u(board);
  }
  if (dir == D){
    return check_d(board);
  }
  std::cout << "ERRROR this should never print\n";
  return false;
}


void get_move(Dir dir, int board[4][4]){
  if (dir == L){
    move_l(board);
  }
  else if (dir == R){
    move_r(board);
  }
  else if(dir == U){
    move_u(board);
  }
  else{
    move_d(board);
  }
}

float get_eval(float strats[6], int board[4][4]){
  float same_total_row=0;
  float same_total_col = 0;
  float std_total_row =0;
  float std_total_col = 0;
  for (int i=0; i<4; ++i){
    std::pair<int,float> temp = row_uniformity(board[i]);
    //same_total_row += temp.first;
    //std_total_row += temp.second;
    same_total_row += std::isnan(temp.first) ? 0 : temp.first;
    std_total_row += std::isnan(temp.second) ? 0 : temp.second;
    int *arr = make_col_arr(i,board);
    std::pair<int,float> temp2 = row_uniformity(arr);
    same_total_col += std::isnan(temp2.first) ? 0 : temp2.first;
    std_total_col += std::isnan(temp2.second) ? 0 : temp2.second;
    delete arr;
  }
  //need to actually make the rows into col arrays
  //that also need to be freed
  int num_free = get_num_free_squares(board);
  float dis = get_distance(board);
  dis = std::isnan(dis) ? 0 : dis;
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


float monte_carlo(float strats[6], int board[4][4], Dir dir){
  float totals = 0;
  int cp_arr[4][4];
  for (int i=0;i<10;++i){
    copy_arr(board,cp_arr);
    get_move(dir,cp_arr);
    totals += get_eval(strats, cp_arr);
  }
  return totals/10;
}

Dir get_maxx(std::unordered_map<Dir,float> &dic){
  float maxx = std::numeric_limits<float>::lowest();
  Dir dir = N;
  for (auto &i : dic){
    if (i.second > maxx){
      maxx = i.second;
      dir = i.first;
    }
  }
  return dir;float minFloat = std::numeric_limits<float>::lowest();
}

void print_dir(Dir dir){
  if (dir == N){
    std::cout << "NONE\n";
    return;
  }
  if (dir == L){
    std::cout << "LEFT\n";
    return;
  }
  if (dir == R){
    std::cout << "RIGHT\n";
    return;
  }
  if (dir == U){
    std::cout << "UP\n";
    return;
  }
  if (dir == D){
    std::cout << "DOWN\n";
  }

}

void print_strat(float strats[6]){
  for (int i=0;i<6;++i){
    std::cout << strats[i] << "\n";
  }
}

//gonna leave scores as 0 and just not gonna count them
int loop(float strats[6]){
  int count = 0;
  int board[4][4];
  init_game(board);
  bool keep_going = false;
  while(true){
    ++count;
    std::unordered_map<Dir,float> scores;
    if (is_legal_move(L,board)){
      scores[L] = monte_carlo(strats,board,L);
      keep_going = true;
    } 
    if (is_legal_move(R,board)){
      scores[R] = monte_carlo(strats,board,R);
      keep_going = true;
    } 
    if (is_legal_move(U,board)){
      scores[U] = monte_carlo(strats,board,U);
      keep_going = true;

    } 
    if (is_legal_move(D,board)){
      scores[D] = monte_carlo(strats,board,D);
      keep_going = true;
    } 
    if (!keep_going){
      print_board(board);
      return gen_score(board);
    }
    else{
      Dir dir = get_maxx(scores);
      //print_dir(dir);
      //print_strat(strats);
      get_move(dir,board);
      keep_going = false;
    }
  }
}

void adjust(float a[6], float b[6], float c[6], int s1, int s2, int s3, int iterations){
  if (s1 >= s2 && s1 >= s3){
    adjust_strat(b,a,iterations);
    adjust_strat(c,a,iterations);
  }
  else if (s2 >= s1 && s2 >= s3){
    adjust_strat(a,b,iterations);
    adjust_strat(c,b,iterations);
  }
  else{
    adjust_strat(b,c,iterations);
    adjust_strat(a,c,iterations);
  }
}

void print_strats(float strats[6], float avg_score, std::unordered_map<int,std::string> &dic){
  std::cout << "THE AVERAGE SCORE WITH THE BEST STRAT IS: ";
  std::cout << avg_score << "\n";
  std::cout << "HERE IS THE STRATEGY:\n";
  for (int i=0; i<6; ++i){
    std::cout << dic[i] << "\n" << strats[i] << "\n";
    std::cout << "-----------------------------\n";
  }
}

void get_best_strat(){
  std::unordered_map<int,std::string> dic;
  dic[0] = "Number of free squares";
  dic[1] = "Distance of largest square from the center";
  dic[2] = "AVERAGE Number of squares that share the same number in a ROW";
  dic[3] = "AVERAGE Number of squares that share the same number in a COL";
  dic[4] = "AVERAGE Standard deviation in a ROW";
  dic[5] = "AVERAGE Standard deviation in a COL";
  
  float one[6];
  float two[6];
  float three[6];
  int final_one = 0;
  int final_two = 0;
  int final_three = 0;
  gen_random_strats(one);
  gen_random_strats(two);
  gen_random_strats(three);
  int count = 0;

  //for (int i=0; i<ITERATIONS; ++i){
    for (int i=0; i<3; ++i){
    int a = loop(one);
    int b = loop(two);
    int c = loop(three);
    adjust(one,two,three,a,b,c,i+1);
    std::cout << "FINISHED ITERATION " << count << "\n";
    ++count;
  }
  //for (int i=0; i<100; ++i){
    for (int i=0; i<1; ++i){
    final_one += loop(one);
    final_two += loop(two);
    final_three += loop(three);
  }

  if (final_one >= final_two && final_one >= final_three){
    print_strats(one, final_one/100.0,dic);
  }
  else if(final_two >= final_one && final_two >= final_three){
    print_strats(two, final_two/100.0,dic);
  }
  else{
    print_strats(three, final_three/100.0,dic);
  }

}

int main(){
  get_best_strat();
  return 0;
}

