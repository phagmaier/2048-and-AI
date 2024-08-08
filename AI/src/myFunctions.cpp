#include "myFunctions.h"
#include <cmath>

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

/*

Value power(Value& value, const float& power_to) {
    Value out = Value{std::pow(value.val, power_to)};
    out.children.insert(&value);
    value.my_back = [&value, &out, &power_to]() {
        value.grad += (power_to * std::pow(value.val, (power_to - 1))) * out.grad;
    };
    return out;
}
*/
