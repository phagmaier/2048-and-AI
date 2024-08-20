#include "my_funcs.h"
#include "parse.h"
#include <vector>
#include <iostream>
#include <cassert>
#include <utility>
#include <unordered_map>

#define ITERATIONS 5 

void print_scores(std::vector<std::pair<int,float>> &scores){
  static std::unordered_map<int,std::string> dic = {
    {1,"Left"}, {2,"Right"},{3,"Down"}, {4,"Up"}
  };

  for (std::pair<int,float> &i : scores){
    std::cout << dic[i.first] << ":" << i.second << "\n";
  }
}

void print_table(std::vector<std::vector<int>> &table){
  assert(table.size() == 4 && table[0].size() == 4);  
  for (std::vector<int> &i : table){
    for (int x : i){
      std::cout << x << "|";
    }
    std::cout <<"\n";
  }
}

int main(){
  /*
  for (int i=0;i<ITERATIONS;++i){
    search();
    std::cout << "FINISHED ITERATION: " << i+1<<"\n";
  }
  */

  std::vector<std::vector<std::vector<int>>>tables = parse_tables();
  for (int i=0;i<5;++i){
    print_table(tables[i]);
    std::cout << "\n";
  }
  std::cout << "\n\n\n\n";

  std::vector<std::vector<std::pair<int,float>>> scores =parse_scores();
  for (int i=200;i<210;++i){
    print_scores(scores[i]);
    std::cout << "----------------\n";
  }


  return 0;
}


