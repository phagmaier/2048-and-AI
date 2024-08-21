#include "nn.h"

std::vector<PTR> convert_score(std::vector<std::pair<int,float>> &score){
  std::unordered_map<int,float> dic;
  std::vector<PTR> cleaned;
  for (std::pair<int,float> &i : score){
    dic[i.first] = i.second; 
    //cleaned.push_back({(Direction)i.first,i.second});
  }
  for (int i=1;i<5;++i){
    cleaned.push_back(make_ptr(dic[i]));
  }
  return cleaned;
}

std::vector<std::vector<PTR>> convert_table(std::vector<std::vector<int>> &table){
  assert(table.size() == 4 && table[0].size() == 4);
  std::vector<std::vector<PTR>> cleaned_table;
  for (int i=0;i<4;++i){
    std::vector<PTR> row;
    for (int x=0;x<4;++x){
      row.push_back(make_ptr((float)table[i][x]));
    }
    cleaned_table.push_back(row);
  }
  return cleaned_table;
}

Data_pair get_data(int num, TABLES &tables, SCORES &scores){
  int size = tables.size();
  Data_pair data;
  std::vector<std::vector<std::vector<PTR>>> rand_tables;
  std::vector<std::vector<PTR>> rand_scores;
  for (int i=0;i<num;++i){
    int num = get_random_index(size);
    rand_tables.push_back(convert_table(tables[num]));
    rand_scores.push_back(convert_score(scores[num]));
  }
  return {rand_tables,rand_scores};
}

Matrix make_weights(int rows, int cols){
  Matrix weights;
  for (int i=0;i<rows;++i){
    std::vector<PTR> row;
    for (int x=0;x<cols;++x){
      row.push_back(make_ptr(getRandomFloat()));
    }
    weights.push_back(row);
  }
  assert(weights.size() == rows && weights[0].size() == cols);
  return weights;
}

Matrix make_zeroes(int rows, int cols){
  Matrix mat;
  for (int i=0;i<rows;++i){
    std::vector<PTR> row;
    for (int x=0;x<cols;++x){
      row.push_back(make_ptr());
    }
    mat.push_back(row);
  }
  assert(mat.size() == rows && mat[0].size() == cols);
  return mat;
}

Matrix matMul(Matrix &inputs, Matrix &weights){
  int rows_input = inputs.size();
  int cols_input = inputs[0].size();
  int rows_weights = weights.size();
  int cols_weights = weights[0].size();
  assert(cols_input == rows_weights);

  Matrix results = make_zeroes(rows_input, cols_weights);
  for (int i = 0; i < rows_input; ++i) {
    for (int j = 0; j < cols_weights; ++j) {
      for (int k = 0; k < cols_input; ++k) {
        //PEM STANDS FOR PLUS EQUALS MULTIPLE
        //i.e += lhs * rhs
        results[i][j] = PEM(results[i][j], inputs[i][k], weights[k][j]);
      }
    }
  }
  return results;
}

void apply_bias_and_activation(Matrix &inputs, PTR &bias){
  for (int i=0;i<inputs.size(); ++i){
    for (int x=0;x<inputs[0].size(); ++x){
      //PTR temp = inputs[i][x] + bias;
      //PTR temp2 = relu(inputs[i][x]);
      //inputs[i][x] = temp2;
      inputs[i][x] = inputs[i][x] + bias;
      inputs[i][x] = relu(inputs[i][x]);
    }
  }
}

PTR get_error(Matrix &results, std::vector<PTR> &targets){
  PTR total = make_ptr();
  int count =0;
  assert(targets.size() == 4);
  assert(results.size() * results[0].size() == targets.size());
  for (int i=0;i<results.size();++i){
    for (int x=0;x<results[0].size();++x){
      PTR temp = make_ptr(ALPHA);
      PTR diff = targets[count] - results[i][x];
      PTR squared_diff = pow(diff, 2);
      PTR error = temp * squared_diff; 
      total = total + error;
      ++count;
    }
  }
  return total;
}

Matrix update_weights(Matrix &vec){
  Matrix weights;
  for (std::vector<PTR> &i : vec){
    std::vector<PTR> row;
    for (PTR &x : i){
      row.push_back(make_ptr(x->val + (x->grad * ALPHA)));
    }
    weights.push_back(row);
  }
  return weights;
  }


void main_loop(){
  const int w1_rows = 4;
  const int w1_cols= 4;

  const int w2_rows = 4;
  const int w2_cols= 4;

  const int w3_rows = 4;
  const int w3_cols= 1;
  //should result in a 4 X 1 matrix
  std::vector<std::vector<std::vector<int>>> tables = parse_tables();
  std::vector<std::vector<std::pair<int,float>>> scores = parse_scores();
  Data_pair data = get_data(1,tables,scores);

  std::vector<std::vector<PTR>> input = data.first[0];
  std::vector<PTR> target = data.second[0];
  Matrix w1 = make_weights(w1_rows, w1_cols);
  Matrix w2 = make_weights(w2_rows, w2_cols);
  Matrix w3 = make_weights(w3_rows, w3_cols);
  
  PTR b1 = make_ptr(getRandombias());
  PTR b2 = make_ptr(getRandombias());
  PTR b3 = make_ptr(getRandombias());

  Matrix h1 = matMul(input, w1);
  apply_bias_and_activation(h1,b1);
  Matrix h2 = matMul(h1,w2);
  apply_bias_and_activation(h2,b2);

  Matrix output = matMul(h2,w3);
  apply_bias_and_activation(output,b3);
  PTR error  = get_error(output, target);

  w1 = update_weights(w1);
  w2 = update_weights(w2);
  w3 = update_weights(w3);
  b1 = update_bias(b1);
  b2 = update_bias(b2);
  b3 = update_bias(b3);

}
