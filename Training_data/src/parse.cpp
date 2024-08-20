#include "parse.h"

std::vector<int> parse_line_table(std::string &line){
  std::vector<int> result;
  std::string clean_string = "";
  for (char c : line){
    if (c == '|'){
      result.push_back(std::stoi(clean_string));
      clean_string = "";
    }
    else if (c != '\n'){
      clean_string += c;
    }
  }
  return result;
}

std::pair<int,float> parse_line_score(std::string &line){
  static std::unordered_map<std::string,int> dic = {
    {"Left",1}, {"Right",2},{"Down",3}, {"Up",4}, {"UP",4}
  };

  int direction = 0;
  float score = 0;
  std::string str = "";
  for (char c : line){
    if (c == ':'){
      direction = dic[str];
      str = "";
    }
    else if(c !='\n'){
      str += c;
    }
  }
  score = std::stof(str);
  assert(score != 0 && direction != 0);
  return {direction,score};
}


std::vector<std::vector<std::vector<int>>>parse_tables(){
  std::ifstream file("tables.txt"); 
  std::vector<std::vector<std::vector<int>>> tables;
  std::vector<std::vector<int>> table;
   
  // String to store each line of the file. 
  std::string line; 

  if (file.is_open()) { 
      // Read each line from the file and store it in the 
      // 'line' variable. 
    while (getline(file, line)) { 
      if (line[0] != '-'){
        if (table.size() < 4){
          table.push_back(parse_line_table(line));
        }
        else{
          tables.push_back(table);
          table.clear();
          table.push_back(parse_line_table(line));        
        }
      }
    } 

    file.close(); 
  } 
  else { 
    std::cerr << "Unable to open file!" << "\n"; 
  } 
  assert(table.size() == 4 || table.size() == 0);
  if (table.size() == 4){
    tables.push_back(table);
  }
  
    return tables;  
}



std::vector<std::vector<std::pair<int,float>>>parse_scores(){
  std::ifstream file("scores.txt"); 

  std::vector<std::vector<std::pair<int,float>>> scores;
  std::vector<std::pair<int,float>> score;

  std::string line; 

  if (file.is_open()){  
      // Read each line from the file and store it in the 
      // 'line' variable. 
    while (getline(file, line)){
      if (line[0] != '-'){
          score.push_back(parse_line_score(line));
      }
      
      else{
          scores.push_back(score);
          score.clear();
          //score.push_back(parse_line_score(line));        
      }
    }
    file.close();
  }
  else { 
    std::cerr << "Unable to open file!" << "\n"; 
    return scores;
  }
  return scores;
}
