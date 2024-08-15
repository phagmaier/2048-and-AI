#include "game.h"

void print_board(int arr[4][4]){
  for (int i=0;i<4;++i){
    for (int x=0; x<4; ++x){
      std::cout << arr[i][x] << "| ";
    }
    std::cout << "\n";
  }
}

int get_random_int() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> distrib(1, 10);
    if (distrib(gen) > 1) {
        return 2;
    }
    return 4;
}


std::pair<int, int> get_pos(std::vector<std::pair<int, int>> &empties) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> indexes(0, empties.size() - 1);
    return empties[indexes(gen)];
}

std::vector<std::pair<int, int>> get_empties(int board[4][4]) {
    std::vector<std::pair<int, int>> empties;
    for (int i = 0; i < 4; ++i) {
        for (int x = 0; x < 4; ++x) {
            if (!board[i][x]) {
                empties.push_back({i, x});
            }
        }
    }
    return empties;
}

bool check_left(int board[4][4]) {
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


bool check_right(int board[4][4]) {
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



bool check_up(int board[4][4]) {
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



bool check_down(int board[4][4]) {
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

void clean_row_left(int board[4]){
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

void clean_row_right(int board[4]){
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



void move_left(int board[4][4]) {
    for (int i = 0; i < 4; ++i) {
        clean_row_left(board[i]);
        for (int x = 0; x < 3; ++x) {
            if (board[i][x] > 0 && board[i][x] == board[i][x + 1]) {
                board[i][x] *= 2;
                board[i][x + 1] = 0;
            }
        }
        clean_row_left(board[i]);
    }
    std::vector<std::pair<int, int>> empties = get_empties(board);
    if (empties.size()) {
        std::pair<int, int> pos = get_pos(empties);
        board[pos.first][pos.second] = get_random_int();
    }
}

void move_right(int board[4][4]) {
    for (int i = 0; i < 4; ++i) {
        clean_row_right(board[i]);
        for (int x = 3; x > 0; --x) {
            if (board[i][x] > 0 && board[i][x] == board[i][x - 1]) {
                board[i][x] *= 2;
                board[i][x - 1] = 0;
            }
        }
        clean_row_right(board[i]);
    }
    std::vector<std::pair<int, int>> empties = get_empties(board);
    if (empties.size()) {
        std::pair<int, int> pos = get_pos(empties);
        board[pos.first][pos.second] = get_random_int();
    }
}


void clean_column_up(int board[4][4], int col){
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

void clean_column_down(int board[4][4], int col){
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

void move_up(int board[4][4]) {
    for (int col = 0; col < 4; ++col) {
        clean_column_up(board, col);
        for (int row = 0; row < 3; ++row) {
            if (board[row][col] > 0 && board[row][col] == board[row + 1][col]) {
                board[row][col] *= 2;
                board[row + 1][col] = 0;
            }
        }
        clean_column_up(board, col);
    }
    std::vector<std::pair<int, int>> empties = get_empties(board);
    if (empties.size()) {
        std::pair<int, int> pos = get_pos(empties);
        board[pos.first][pos.second] = get_random_int();
    }
}

void move_down(int board[4][4]) {
    for (int col = 0; col < 4; ++col) {
        clean_column_down(board, col);
        for (int row = 3; row > 0; --row) {
            if (board[row][col] > 0 && board[row][col] == board[row - 1][col]) {
                board[row][col] *= 2;
                board[row - 1][col] = 0;
            }
        }
        clean_column_down(board, col);
    }
    std::vector<std::pair<int, int>> empties = get_empties(board);
    if (empties.size()) {
        std::pair<int, int> pos = get_pos(empties);
        board[pos.first][pos.second] = get_random_int();
    }
}

bool is_legal_move(Direction dir, int board[4][4]){
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



void start_game(int board[4][4]){
  std::vector<std::pair<int,int>> empties = get_empties(board);
  std::pair<int,int> pos = get_pos(empties);
  board[pos.first][pos.second] = get_random_int();

  empties = get_empties(board);
  pos = get_pos(empties);
  board[pos.first][pos.second] = get_random_int();

}

void move(Direction dir,int board[4][4]){
  switch (dir){
    case Left:
      move_left(board);
      break;
    case Right:
      move_right(board);
      break;
    case Up:
      move_up(board);
      break;
    case Down:
      move_down(board);
      break;
    case None:
      std::cout << "ERROR THIS SHOULD NEVER BE CALLED WANTS TO MOVE NONE\n";
      //std::cout << "";
      break;
    default:
      std::cout << "ERROR THIS SHOULD NEVER BE CALLED\n";
      break;
      
  }
}

bool is_over(int board[4][4]){
  if (is_legal_move(Left, board)){
    return false;
  }
  if (is_legal_move(Right,board)){
    return false;
  }
  if (is_legal_move(Up, board)){
    return false;
  }
    return !is_legal_move(Down,board);
}


int get_score(int board[4][4]){
  int score = 0;
  for (int i=0; i<4; ++i){
    for (int x=0;x<4;++x){
      score += board[i][x];
    }
  }
  return score;
}


void new_game(int board[4][4]){
  for (int i=0; i<4;++i){
    for (int x=0;x<4;++x){
      board[i][x] = 0;
    }
  }
  start_game(board);
}

