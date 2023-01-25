#include "bitset.hpp"

Bitset::Bitset() {
    N = 8;
    bits = new int[N];
}

Bitset::Bitset(intmax_t size) {
    if(size > 0){
        N = size;
        bits = new int[size];
    }
    else{
        valid = false;
    }
}

Bitset::Bitset(const std::string & value) {
    bits = new int[value.length()];
    N = value.length();
    for(int i = 0; i < value.length(); i++){
        if(value.at(i) == '0' || value.at(i) == '1'){
            *(bits + i) = (value.at(i) - '0');
        }
        else{
            valid = false;
            break;
        }
    }
}

// TODO COMMENT
Bitset::~Bitset(){
    delete bits;
}

//@param : returns size of bitset, no params
intmax_t Bitset::size() const{
    //@return : length of bitset
    return N;
}

//@param : returns validty of bitset, no params
bool Bitset::good() const{
    //@return : validity
    return valid;
}

//@param : changes nth bit to 1, takes in bit position
void Bitset::set(intmax_t index){
    int lastBit = N - 1;
    if(!(index < 0 && index > lastBit)){
        *(bits + index) = 1;
    }
    else{
        valid = false;
    }
}

//@param : changes nth bit to 0, takes in bit position
void Bitset::reset(intmax_t index){
    int lastBit = N - 1;
    if(!(index < 0 && index > lastBit)){
        *(bits + index) = 0;
    }
    else{
        valid = false;
    }
}

//@param : toggles nth bit, takes in bit position
void Bitset::toggle(intmax_t index){
    if(index > 0 && index < N){
        *(bits + index) == 1 ? *(bits + index) = 0 : *(bits + index) = 1;
    }
    else{
        valid = false;
    }
}

//@param : gets nth bit truth, takes in bit position
bool Bitset::test(intmax_t index){
    int lastBit = N - 1;
    if(index < 0 || index > lastBit){
        valid = false;
        return false;
    }
    else{
        return *(bits + index);
    }
}

//@param : gets bitset as string, no params
std::string Bitset::asString() const{
    std::string result = "";
    for(int i = 0; i < N; i++){
        result.append(std::to_string(*(bits + i)));
    }
    return result;
}