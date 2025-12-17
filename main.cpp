#include <iostream>
#include <string>
#include "parser.hpp"


int main(){
    
    std::string user_query = "select * from users";

    Parser::parse(user_query);

    return 0;
}