//
// Created by Parker Hagmaier on 9/11/23.
//
#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

#include "value.h"
#include <cmath>
#include "value.h"

Value operator+(const float& left, Value& right);
Value operator*(const float& left, Value& right);
Value operator-(const float& left, Value& right);
//Value relu(Value& myVal);
//Value tan_h(Value& myVal);

#endif //CYTORCH_MYFUNCTIONS_H
