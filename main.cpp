#include <iostream>
#include <string>
#include "parser.hpp"
#include "debug.hpp"  


int main(){
    
    Tokenizer::Query user_query = "select * from users;";

    Parser::parse(user_query);

    debugger;
    std::cout << "successfully parsed" << std::endl;

    return 0;
}