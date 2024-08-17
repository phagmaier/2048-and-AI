#include "myFunctions.h"

Value operator+(const float& left, Value& right) {
    Value val_other{left};
    return val_other + right;
}

Value operator*(const float& left, Value& right) {
    Value val_other{left};
    return val_other * right;
}

Value operator-(const float& left, Value& right) {
    Value val_other(left);
    return val_other - right;
}

