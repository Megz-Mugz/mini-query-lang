#include <iostream>
#include "Tokenizer.hpp"
#include "debug.hpp"    

class Parser

{

public:

    static void parse(const std::string& query){
        Tokenizer tokenizer(query);
        auto select = tokenizer.get_next_token();
        debugger;
        auto star = tokenizer.get_next_token();
        auto from = tokenizer.get_next_token();
        auto users = tokenizer.get_next_token();

        std::cout << "finished" << std::endl;
    }

};