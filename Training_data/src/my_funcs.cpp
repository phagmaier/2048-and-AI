#include "my_funcs.h"
//std::mutex file_mutex;


/*
*MOST OF THIS IS USELESS 'REAL CODE' (STILL SHIT)
*STARTS AT LIKE 319 THIS WAS JUST ME PLAYING AROUND
*EXPERIMENTING & AND BEING LAZY AND STUPID
*
*/




void copy_board(int board[4][4], int empty_board[4][4]){
  for (int i=0;i<4;++i){
    for (int x=0;x<4;++x){
      empty_board[i][x] = board[i][x];
    }
  }
}


int get_scaled_num(int num) {
    if (!num){
      return 0;
    }
    int original = num;
    int count = 0;
    int number = 2;
    while (number < num) {
        number *= 2;
        ++count;
    }
    return count+1;
}

std::string dir_to_string(Direction dir){
  switch (dir){
    case Left:
      return "Left";
      break;
    case Right:
      return "Right";
      break;
    case Down:
      return "Down";
      break;
    case Up:
      return "Up";
      break;
    default:
      std::cout << "THIS SHOULD ABSOLUTLEY NEVER PRINT\n";
      return "";
      break;
  }
}

void write_board(int board[4][4]){
  std::ofstream outputFile("data.txt", std::ios::app);
  // Check if the file is open
  if (outputFile.is_open()) {
    for (int i=0;i<4;++i){
      for (int x=0;x<4;++x){
        outputFile << get_scaled_num(board[i][x]) << "|";
      }
      outputFile << "\n";
    }
    outputFile.close();
  } 
  else {
    std::cout<< "Unable to open file." << std::endl;
  }
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

//useless as of now
void zero_arr(int *arr, int size){
  for (int i=0;i<size;++i){
    arr[i] = 0;
  }
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


//START OF THE BAD STUFF BUT THE BAD STUFF THAT SOLVES THE GAME

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


void write_moves_scores(std::vector<std::pair<float,Direction>> &scores){
  std::ofstream outputFile("data.txt", std::ios::app); 
  for (std::pair<float, Direction> &i : scores){
    outputFile << dir_to_string(i.second) << ":" << i.first << "\n";
  }
}



Direction get_best_move(int board[4][4]){
  write_board(board);
  std::vector<Direction> moves = get_possible_moves(board);
  std::vector<std::pair<float,Direction>> scores;
  for (Direction dir : moves){
    scores.push_back({get_move_score(board, dir),dir});
  }
  write_moves_scores(scores);
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
