#pragma once

#include <cctype>
#include "TokenType.hpp"
#include "debug.hpp"   
#include <unordered_set>



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
        while (cursor < _query.size()){


            // skip over white space
            while (cursor < _query.size() &&  _query[cursor] == ' '){
                cursor += 1;
            }
            
            char current_letter = _query[cursor];

            // handle single character look up
            auto single_letter_lookup = single_words.find(current_letter);

            if (single_letter_lookup != single_words.end()){
                // debugger;
                auto token_type = determine_token_type();
                
                if (token_type == TokenType::QUOTE){
                    return handle_string_literal();
                }
                cursor++;
                
                return {std::string(1, current_letter), token_type};
            }

            // handle numbers
            if (std::isdigit(current_letter)){
                uint16_t start = cursor;

                while (start < _query.size() && std::isdigit(_query[start])){
                    start++;
                }
                
                size_t old_cursor_val = cursor;
                cursor = start;

                return {
                    _query.substr(old_cursor_val, start - old_cursor_val),
                    TokenType::NUMBER
                };
            }

            // handle keywords & identifiers
            // Note: userswhereid... should be tokenizable, but not parsable (it's too ambigious)
            // leverage alphaNum

            // handle keywords & identifiers (LONGEST MATCH)
            if (std::isalpha(static_cast<unsigned char>(_query[cursor])) || _query[cursor] == '_') {

                size_t start = cursor;
                
                // longest match possible 
                while (cursor < _query.size() && (std::isalnum(static_cast<unsigned char>(_query[cursor])) || _query[cursor] == '_')) {
                    cursor++;
                }

                Word word = _query.substr(start, cursor - start);

                auto it = keywords.find(word);
                if (it != keywords.end()) {
                    return { word, it->second };
                }

                return { word, TokenType::IDENTIFIER };
            }

        }

        return {"", TokenType::EOL};
    }

private:

    unsigned int cursor;
    int token_count;
    Query _query;

    std::unordered_set<char> single_words = {
        '+',
        '-',
        '*',
        '/',
        '<',
        '>',
        '=',
        '!',
        ',',
        '\'',
        ';'
    };

    TokenType determine_token_type() {
        
        switch (_query[cursor]) {

            case '+':
                return TokenType::PLUS;

            case '-':
                return TokenType::MINUS;

            case '*':
                return TokenType::STAR;

            case '/':
                return TokenType::SLASH;

            case '<':
                return TokenType::LESS;

            case '>':
                return TokenType::GREATER;

            case '=':
                return TokenType::EQUAL;

            case '!':
                return TokenType::NOT;
            
            case ',':
                return TokenType::COMMA;

            case ';':
                return TokenType::EOL;
            
            case '\'': 
                return TokenType::QUOTE;

            default:
                throw std::runtime_error("Unknown single-character token");
        }
    }


    Token handle_string_literal(){
        
        debugger;
        size_t starting_point = cursor;
        cursor++;

        while (_query[cursor] != '\''){
            cursor++;
        }
        cursor++;
        return {_query.substr(starting_point, cursor - starting_point), TokenType::STRING};
        
    }

};