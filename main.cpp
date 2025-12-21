#include <iostream>
#include <string>
#include "parser.hpp"
#include "debug.hpp"  
#include "Tokenizer.hpp"


int main(){
    
    Tokenizer::Query user_query = "select * from users where id >= 333;";

    Parser::TokenStream tokens = Parser::get_tokens(user_query);

    debugger;
    std::cout << "successfully parsed" << std::endl;

    for (const auto& tok : tokens){
        debugger;
        std::cout << tok.first << " " << tok.second << std::endl;
    }

    return 0;
}