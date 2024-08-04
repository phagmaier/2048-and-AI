#include "brain.h"

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
    num *=2;
    ++count;
  }
  return count;
}

float standard_deviation(float total, int board[4], int count){
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
  std::vector<std::pair<int,int>> empties = get_free_squares(board);
  std::pair<int,int> pos = get_random_square(empties);
  board[pos.first][pos.second] = get_number();

  empties = get_free_squares(board);
  pos = get_random_square(empties);
  board[pos.first][pos.second] = get_number();

}


float get_eval(float *strats, int board[4][4]){
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
  return total/10; //will have to do this with left right up and down (if possible to make all those choices)
}

//should probably do a random sample
//score after going right and after going left

//row std 
//row number of same vals
//col stdd 
//col number of same vals 
//number of empty squares
//euclidian distance largest tile from the center square
void gameLoop(float strats[6]){
  bool over = false;
  int board[4][4];
  for (int i=0;i<4;++i){
    for (int x=0;x<4;++x){
      board[i][x] = 0;
    }
  }
  init_game(board);

  /*
  //make move
  //shift board accordingly but don't 
  //add the new number to board will be doing that in 
  //game_loop

  while (!over){

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
    }
  */
}
