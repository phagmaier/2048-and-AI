#include "brain.h"

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

float standard_deviation(float total, int board[4]){
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
  int total = 0;
  std::unordered_map<int,int> dic;
  for (int i=0;i<4;++i){
      dic[board[i]] +=1;
      total += get_real_num(board[i]);
  }
  int max = 0;
  for (auto &i : dic){
    if (i.second > max){
      max = i.second;
    }
  }
  return {max, standard_deviation(total,board)};
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
