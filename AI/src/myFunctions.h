#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

#include "value.h"
#include <cmath>

//btw the gradient for relu is 1 for x > 0 and 0  for all
//0 values < 0

Value operator+(const float& left, Value& right);
Value operator*(const float& left, Value& right);
Value operator-(const float& left, Value& right);
//Value power(Value& value, const float& power_to);
//Value relu(Value& myVal);
//Value tan_h(Value& myVal);

#endif 
