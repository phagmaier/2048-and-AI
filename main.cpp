#include <random>
#include <iostream>
#include <vector>
#include <utility>
#include "raylib.h"

enum Direction{
  Left,
  Right,
  Down,
  Up,
  None
};

int get_random_int(){
    std::random_device rd;
    
    // Initialize the random number generator with the seed
    std::mt19937 gen(rd());
    
    // Define the range for the random integers
    std::uniform_int_distribution<> distrib(2, 4);
    return distrib(gen);
}

std::pair<int,int> get_pos(std::vector<std::pair<int,int>> &empties){
  //std::pair<int,int> position; 
  
  std::random_device rd;

  // Initialize the random number generator with the seed
  std::mt19937 gen(rd());

  // Define the range for the random index (0 to list.size() - 1)
  std::uniform_int_distribution<> indexes(0, empties.size() - 1);

  //std::uniform_int_distribution<> col_indexes(0, cols.size() - 1);

  return empties[indexes(gen)];
}

std::vector<std::pair<int,int>> get_empties(int *board[4]){
  std::vector<std::pair<int,int>> empties;
  for (int i=0;i<4; ++i){
    for (int x=0;x<4;++x){
      if (!board[i][x]){
        empties.push_back({i,x});
      }
    }
  }
  return empties;
}

bool check_left(int *board[4]){
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

bool check_right(int *board[4]){
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


bool check_up(int *board[4]){
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


bool check_down(int *board[4]){
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

void move_left(int *board[4]){
  for (int i=0;i<4;++i){
    if (board[i][0] + board[i][1] + board[i][2] + board[i][3]){
     for (int x=0;x<3;++x){
        if (!board[i][x]){
          for (int z=x;z<3;++z){
            board[i][z] = board[i][z+1];
          }
        }
      } 
      if (board[i][0] == board[i][1]){
        board[i][0] += board[i][1];
        board[i][1] = board[i][2];
        board[i][2] = board[i][3];
        board[i][3] = 0;
        if (board[i][1] == board[i][2]){
          board[i][1] += board[i][2];
          board[i][2] = 0;
        }
      }
      else if(board[i][1] == board[i][2]){
        board[i][1] += board[i][2];
        board[i][2] = board[i][3];
        board[i][3] = 0;
      }
      else if(board[i][2] == board[i][3]){
        board[i][2] += board[i][3];
        board[i][3] = 0;
      }
    }
  }
  std::vector<std::pair<int,int>> empties = get_empties(board);
  std::pair<int,int> pos = get_pos(empties);
  board[pos.first][pos.second] = get_random_int();
}


void move_right(int *board[4]){
  for (int i=0;i<4;++i){
    if (board[i][0] + board[i][1] + board[i][2] + board[i][3]){
     for (int x=3;x>0;--x){
        if (!board[i][x]){
          for (int z=x;z>0;--z){
            board[i][z] = board[i][z-1];
          }
        }
      } 
      if (board[i][0] == board[i][1]){
        board[i][1] += board[i][0];
        board[i][2] = board[i][1];
        board[i][3] = board[i][2];
        board[i][0] = 0;
        if (board[i][1] == board[i][2]){
          board[i][1] += board[i][2];
          board[i][1] = 0;
        }
      }
      else if(board[i][1] == board[i][2]){
        board[i][2] += board[i][1];
        board[i][3] = board[i][2];
        board[i][0] = 0;
      }
      else if(board[i][2] == board[i][3]){
        board[i][2] += board[i][3];
        board[i][0] = 0;
      }
    }
  }
  std::vector<std::pair<int,int>> empties = get_empties(board);
  std::pair<int,int> pos = get_pos(empties);
  board[pos.first][pos.second] = get_random_int();
}


void move_up(int *board[4]){
  for (int i=0;i<3;++i){
    if (board[0][i] + board[1][i] + board[2][i] + board[3][i]){
     for (int x=0;x<4;++x){
        if (!board[x][i]){
          for (int z=x;z<4;++z){
            board[z][i] = board[z+1][i];
          }
        }
      } 
      if (board[0][i] == board[1][i]){
        board[0][i] += board[1][i];
        board[1][i] = board[2][i];
        board[2][i] = board[3][i];
        board[3][i] = 0;
        if (board[1][i] == board[2][i]){
          board[1][i] += board[2][i];
          board[2][i] = 0;
        }
      }
      else if(board[1][i] == board[2][i]){
        board[1][i] += board[2][i];
        board[2][i] = board[3][i];
        board[3][i] = 0;
      }
      else if(board[2][i] == board[3][i]){
        board[2][i] += board[3][i];
        board[3][i] = 0;
      }
    }
  }
  std::vector<std::pair<int,int>> empties = get_empties(board);
  std::pair<int,int> pos = get_pos(empties);
  board[pos.first][pos.second] = get_random_int();
}


void move_down(int *board[4]){
  for (int i=1;i<4;++i){
    if (board[0][i] + board[1][i] + board[2][i] + board[3][i]){
     for (int x=3;x> -1;--x){
        if (!board[i][x]){
          for (int z=x;z> -1;--z){
            board[z][i] = board[z-1][i];
          }
        }
      } 
      if (board[0][i] == board[1][i]){
        board[1][i] += board[0][i];
        board[2][i] = board[1][i];
        board[3][i] = board[2][i];
        board[0][i] = 0;
        if (board[1][i] == board[2][i]){
          board[1][i] += board[2][i];
          board[1][i] = 0;
        }
      }
      else if(board[1][i] == board[2][i]){
        board[2][i] += board[1][i];
        board[3][i] = board[2][i];
        board[0][i] = 0;
      }
      else if(board[2][i] == board[3][i]){
        board[2][i] += board[3][i];
        board[0][i] = 0;
      }
    }
  }
  std::vector<std::pair<int,int>> empties = get_empties(board);
  std::pair<int,int> pos = get_pos(empties);
  board[pos.first][pos.second] = get_random_int();
}

bool is_legal_move(Direction dir, int *board[4]){
  if (dir == Left){
    return check_left(board);  
  }
  if (dir == Right){
    return check_right(board);
  }
  if (dir == Up){
    return check_up(board);
  }
  if (dir == Down){
    return check_down(board);
  }
  std::cout << "ERRROR this should never print\n";
  return false;
}





Direction get_dir(){
  if (IsKeyDown(KEY_LEFT)) {
    return Left;
  }
  if (IsKeyDown(KEY_RIGHT)) {
    return Right;
  }
  if (IsKeyDown(KEY_UP)) {
    return Up;
  }
  if (IsKeyDown(KEY_DOWN)) {
    return Down;
  }
  return None;
}


int main(){
  int board[4][4];

  return 0;
}
