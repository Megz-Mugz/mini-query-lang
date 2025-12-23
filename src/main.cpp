#include <iostream>
#include <string>
#include "parser.hpp"
#include "debug.hpp"  
#include "Tokenizer.hpp"

int main(){
    Tokenizer::Query user_query = "SELECT * FROM USERS WHERE ID >= 3;";
    Parser sql_parser;
    
    // does all the heavy lifting
    bool success = sql_parser.parse_tokens(user_query);

    if (success){
        std::cout << "parsed successfully" << std::endl;
    }

    Parser::TokenStream tokens = sql_parser.get_tokens();

    // print out tokens for debugging purposes
    for (const auto& tok : tokens){
        std::cout << '(' << tok.first << ", " << tok.second  << ')' << std::endl;
    }

    return 0;
}