#ifndef PARSE_H
#define PARSE_H

#include <vector>
#include <string>
#include <utility>
#include <fstream> 
#include <iostream>
#include <cassert>
#include <unordered_map>

/*
enum Direction{
  None,
  Left,
  Right,
  Down,
  Up
};
*/

std::vector<int> parse_line_table(std::string &line);
std::pair<int,float> parse_line_score(std::string &line);
std::vector<std::vector<std::vector<int>>>parse_tables();
//int here is going to be a stand in for Direction
std::vector<std::vector<std::pair<int,float>>>parse_scores();

//std::vector<std::vector<int>> make_table();
//std::vector<std::vector<std::pair<int,float>>> make_score();


#endif
