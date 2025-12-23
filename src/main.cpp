#include <iostream>
#include <string>
#include "parser.hpp"
#include "debug.hpp"  
#include "Tokenizer.hpp"

int main(){
    Tokenizer::Query user_query = "select * from users";
    Parser sql_parser;
    
    debugger;
    
    // does all the heavy lifting
    sql_parser.parse_tokens(user_query);

    Parser::TokenStream tokens = sql_parser.get_tokens();

    // print out tokens for debugging purposes
    for (const auto& tok : tokens){
        std::cout << '(' << tok.first << ", " << tok.second  << ')' << std::endl;
    }

    return 0;
}