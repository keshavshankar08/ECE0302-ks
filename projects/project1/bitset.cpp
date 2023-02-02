#include "bitset.hpp"

//@param : constructs bitset default, no params
Bitset::Bitset() {
    bits = new int[N];

    for(int i = 0; i < N; i++){
        *(bits + i) = 0;
    }
}

//@param : constructs bitset using size, takes in int value
Bitset::Bitset(intmax_t size) {
    //@pre : for input size
    //@post : create bitset with that size if valid, else set invalid bitset
    N = size;
    if(size > 0){
        bits = new int[size];
        for(int i = 0; i < N; i++){
            *(bits + i) = 0;
        }
    }
    else{
      //  bits = new int[0];
        valid = false;
    }
}

//@param : constructs bitset using string, takes in string value
Bitset::Bitset(const std::string & value) {
    //@pre : for each char in string input
    //@post : copy over all bits to bitset if valid, else set as invalid bitset
    N = value.length();
    bits = new int[value.length()];
    for(int i = 0; i < value.length(); i++){
        if(value.at(i) == '0' || value.at(i) == '1'){
            *(bits + i) = (value.at(i) - '0');
        }
        else{
            valid = false;
            N = 0;
        }
    }
}

//@param : destructs bitset, no params
Bitset::~Bitset(){
    delete [] bits;
}

//@param : returns size of bitset, no params
intmax_t Bitset::size() const{
    //@return : length of bitset
    return N;
}

//@param : returns validty of bitset, no params
bool Bitset::good() const{
    //@return : validity of bitset
    return valid;
}

//@param : changes nth bit to 1, takes in bit position
void Bitset::set(intmax_t index){
    //@pre : for input index
    //@post : set index bit to 1 if in bounds of bitset, else set invalid bitset
    int lastBit = N - 1;
    if(index >= 0 && index <= lastBit){
        *(bits + index) = 1;
    }
    else{
        valid = false;
    }
}

//@param : changes nth bit to 0, takes in bit position
void Bitset::reset(intmax_t index){
    //@pre : for input index
    //@post : set index bit to 0 if in bounds of bitset, else set invalid bitset
    int lastBit = N - 1;
    if(index >= 0 && index <= lastBit){
        *(bits + index) = 0;
    }
    else{
        valid = false;
    }
}

//@param : toggles nth bit, takes in bit position
void Bitset::toggle(intmax_t index){
    //@pre : for input index
    //@post : toggle index bit if in bounds of bitset, else set invalid bitset
    int lastBit = N - 1;
    if(index >= 0 && index <= lastBit){
        *(bits + index) == 1 ? *(bits + index) = 0 : *(bits + index) = 1;
    }
    else{
        valid = false;
    }
}

//@param : checks if nth bit is set, takes in bit position
bool Bitset::test(intmax_t index){
    //@pre : for input index
    //@post : test if index bit set if in bounds of bitset, else set invalid bitset
    int lastBit = N - 1;
    bool truth;
    if(index >= 0 && index <= lastBit){
        *(bits + index) == 1 ? truth = true : truth = false;
        //@return : bit set/not set
        return truth;
    }
    else{
        valid = false;
        //@return : bit is not set
        return false;
    }
}

//@param : gets bitset as string, no params
std::string Bitset::asString() const{
    //@pre : for each bit in bitset
    //@post : append each bit in order to the string
    std::string result;
    for(int i = 0; i < N; i++){
        result.append(std::to_string(*(bits + i)));
    }
    //@return : string equivalent of bitset
    return result;
}