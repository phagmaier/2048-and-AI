#include <random>
#include <iostream>
#include <vector>
#include <utility>
#include "raylib.h"
#include <string>

enum Direction{
  None,
  Left,
  Right,
  Down,
  Up
};

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


Direction get_dir(int key_pressed){
  if (key_pressed == KEY_LEFT) {
    return Left;
  }
  if (key_pressed == KEY_RIGHT) {
    return Right;
  }
  if (key_pressed == KEY_UP) {
    return Up;
  }
  if (key_pressed == KEY_DOWN) {
    return Down;
  }
  return None;
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
      std::cout << "ERROR THIS SHOULD NEVER BE CALLED\n";
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

void new_game(int board[4][4]){
  for (int i=0; i<4;++i){
    for (int x=0;x<4;++x){
      board[i][x] = 0;
    }
  }
  start_game(board);
}


void game_over(float screenW, float screenH, int score, int board[4][4]) {
    float boxW = screenW - 20;
    float boxH = screenH - 20;
    Rectangle rec = {10, 10, boxW, boxH};
    Rectangle reset = {screenW / 2 - 100, screenH / 2 + 50, 200, 50};

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangleRec(rec, LIGHTGRAY);
        DrawRectangleLines(rec.x, rec.y, boxW, boxH, BLACK);
        DrawText("GAME OVER", screenW / 2 - MeasureText("GAME OVER", 100) / 2, screenH / 2 - 100, 100, BLACK);

        DrawRectangleRec(reset, LIGHTGRAY);
        DrawRectangleLines(reset.x, reset.y, reset.width, reset.height, BLACK);
        DrawText("RESET", reset.x + reset.width / 2 - MeasureText("RESET", 30) / 2, reset.y + reset.height / 2 - 15, 30, BLACK);

        std::string text = "Score: " + std::to_string(score);
        DrawText(text.c_str(), screenW / 2 - MeasureText(text.c_str(), 50) / 2, screenH / 2, 50, BLACK);

        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            if (CheckCollisionPointRec(mousePos, reset)) {
                new_game(board);
                return;
            }
        }
    }
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

//at some point need to add a check at the end to see 
//if there are any remaining legal moves

int main(){
  
  bool over = false;
  int board[4][4];
  for (int i=0;i<4;++i){
    for (int x=0;x<4;++x){
      board[i][x] = 0;
    }
  }
  start_game(board);
  //board[0][0] = 2;
  //board[0][1] = 2;
  int key_pressed = 0;

  InitWindow(0,0,"2048");
  float screenW = GetScreenWidth() * .5;
  float screenH = GetScreenHeight() * .5;
  SetWindowSize(screenW, screenH);
  SetTargetFPS(40);

  float boxW = screenW / 4;
  float boxH = screenH / 4;

  Rectangle boxes[4][4];
  for (int i=0; i<4;++i){
    for (int x=0;x<4;++x){
      boxes[i][x] = Rectangle{boxW * x, boxH * i, boxW, boxH};
    }
  }

  
  while (!WindowShouldClose()){
    if (!over){

    key_pressed = GetKeyPressed();
    if (key_pressed){
      Direction dir = get_dir(key_pressed);
      key_pressed =0;
        if (dir){
          if (is_legal_move(dir, board)){
            move(dir,board); 
        }
        
        }
    }
    BeginDrawing();
    ClearBackground(RAYWHITE);
    for (int i=0; i<4; ++i){
      for (int x=0;x<4;++x){
        DrawRectangleRec(boxes[i][x], BEIGE);
        DrawRectangleLines(boxes[i][x].x,boxes[i][x].y, boxW,boxH,BLACK);
        std::string text = board[i][x] ? std::to_string(board[i][x]) : "";
        DrawText(text.c_str(), boxes[i][x].x+ boxW/2,boxes[i][x].y+boxH/2, 50, BLACK);
      }
    }
   EndDrawing();
   over = is_over(board);
    
  }
    else{
      int score = get_score(board);
      game_over(screenW,screenH,score,board);
      over = false;
    }
  }

  CloseWindow();


  return 0;
}





