#pragma once

#include <cctype>
#include "TokenType.hpp"

class Tokenizer

{
    
public:

    Tokenizer(const std::string& query) {
        cursor = 0;
        token_count = 0;
        _query = query;
    }

    std::pair<std::string, TokenType> get_next_token(){
        std::string new_token = "";
        
        while (cursor < _query.size()) {
            char c = _query[cursor];

            // 1. Whitespace → flush token, then skip
            if (std::isspace(static_cast<unsigned char>(c))) {
                if (!new_token.empty()) {
                    auto it = keywords.find(new_token);
                    if (it != keywords.end()) {
                        std::cout << "keyword: " << new_token << std::endl;
                        return std::make_pair(new_token, it->second);
                    } else {
                        std::cout << "identifier: " << new_token << std::endl;
                        return std::make_pair(new_token, TokenType::IDENTIFIER);
                    }
                    new_token.clear();
                }
                cursor++;
                continue;
        }

        new_token += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        cursor++;
        }

        if (!new_token.empty()) {
            auto it = keywords.find(new_token);
            if (it != keywords.end()) {
                std::cout << "keyword: " << new_token << std::endl;
                return std::make_pair(new_token, it->second);
            } else {
                std::cout << "identifier: " << new_token << std::endl;
                return std::make_pair(new_token, TokenType::IDENTIFIER);
            }
        }
    }

private:

    unsigned int cursor;
    int token_count;
    std::string _query;


    

};