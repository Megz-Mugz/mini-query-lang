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
        std::string new_token = "";
        
        while (cursor < _query.size()){
            

            while (curr_char_is_space()){
                debugger; 
                cursor += 1;
            }

            if (curr_char_is_eol()){ 
                debugger; 
                return {";", TokenType::EOL}; 
            };

            // one character look ahead for space or EOL
            if (next_char_is_space() || next_char_is_eol()){
                debugger;
                return build_token(new_token);
            } 
            
            new_token += static_cast<char>(
                std::tolower(static_cast<unsigned char>(_query[cursor++]))
            );
        }

        return {"", TokenType::EOL};
    }

private:

    unsigned int cursor;
    int token_count;
    Query _query;

    bool curr_char_is_space(){

        return std::isspace(static_cast<unsigned char>(_query[cursor]));
    }

    bool curr_char_is_eol(){
        return _query[cursor] == ';';
    }

    bool next_char_is_space(){

        return std::isspace(static_cast<unsigned char>(_query[cursor+1]));
    }

    bool next_char_is_eol(){
        return _query[cursor+1] == ';';
    }

    Token build_token(std::string& new_token){
        new_token += _query[cursor++]; // push the current char into the word
        Word completed_token = new_token;
        
        new_token.erase();

        auto it = keywords.find(completed_token);
        debugger;
        if (it != keywords.end()){
            return {completed_token, it->second};
        } else {
            return {completed_token, TokenType::IDENTIFIER};
        }

    }

};