#include "value.h"

Value::Value(float v): val{v}, grad{0} {}
Value::Value() : val{0}, grad{0}{}

float Value::get_grad() const{
    return grad;
}

float Value::get_value(){
    return grad;
}

Value Value::operator+(Value& other) {
    Value out{val + other.val};
    out.children.insert(this);
    out.children.insert(&other);
    out.my_back = [this,&other,&out](){
        this->grad += out.grad;
        other.grad += out.grad;
    };
    return out;
}

Value Value::operator+(const float& other) {
    Value val_other{other};
    return *this + val_other;
}

Value Value::operator*(Value& other) {
    Value out{val * other.val};
    out.children.insert(this);
    out.children.insert(&other);

    out.my_back = [this,&other,&out](){
        this->grad += other.val * out.grad;
        other.grad += this->val * out.grad;

    };
    return out;
}

Value Value::relu(){
  float t = val > 0 ? val : 0;
    Value out{t};
    out.children.insert(this);
    out.my_back = [this, &out, t](){
        //this->grad += (1 - (t * t)) * out.grad;
    this->grad += t > 0 ? 1 : 0;
    };
    return out;}

Value Value::operator*(const float& other) {
    Value val_other{other};
    return *this * val_other;
}

Value Value::operator-() {
    return *this * -1;
}

Value Value::operator-(Value& other) {
    return {-other + *this};
}

Value Value::operator-(float& other) {
    Value val_other{other};
    return *this - val_other;
}

Value power(Value& value, const float& power_to) {
    Value out = Value{std::pow(value.val, power_to)};
    out.children.insert(&value);
    value.my_back = [&value, &out, &power_to]() {
        value.grad += (power_to * std::pow(value.val, (power_to - 1))) * out.grad;
    };
    return out;
}

Value Value::operator/(Value& other) {
    Value temp{power(*this, -1)};
    return power(*this, -1) * other;
}

void Value::build_topo(Value* v, std::vector<Value*>& topo,
                       std::set<Value*>& visited){
    if (visited.find(v) == visited.end()){
        visited.insert(v);
        for (const auto& child : v->children){
            build_topo(child, topo,visited);
        }
        topo.push_back(v);
    }
}

//NOTE: if not a value in memory pass copy to lambda func
//Should probably try and impliment it as a function as well
Value Value::tanh_h() {
    float t = std::tanh(val);
    Value out{t};
    out.children.insert(this);
    out.my_back = [this, &out, t](){
        this->grad += (1 - (t * t)) * out.grad;
    };
    return out;
}

void Value::backward() {
   std::vector<Value*> topo;
   std::set<Value*> visited;

   build_topo(this,topo,visited);

   this->grad = 1;
   std::reverse(topo.begin(),topo.end());

   for (auto v: topo){
       v->my_back();
   }
}

std::ostream& operator<<(std::ostream& os, const Value& myVal) {
    os << "Value: " << myVal.val << " Grad: " << myVal.grad << "\n";
    return os; // You need to return the ostream object.
}
