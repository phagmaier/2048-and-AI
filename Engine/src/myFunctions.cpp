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

Value relu(Value &val){
  Value out = val.val > 0 ? Value(val.val) : Value(0);
    
    // Establish child relationship
    out.children.insert(&val);
    
    // Define the backward function
    out.my_back = [&val, &out]() {
        if (val.val > 0) {
            val.grad += out.grad;
        }     
    };
    
  return out;
}

