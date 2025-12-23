#pragma once

#include <cctype>
#include "TokenType.hpp"
#include "debug.hpp"   



class Tokenizer

{
    
public:

    using Query = std::string;
    using Word = std::string;

    using Token = std::pair<Word, TokenType>;
    
    Tokenizer(const Query& query) {
        cursor = 0;
        token_count = 0;
        _query = query;
    }

    Token get_next_token(){
        // TODO implement it properly
    }

private:

    unsigned int cursor;
    int token_count;
    Query _query;

};