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
    using MaybeToken = std::optional<Token>;
    
    Tokenizer(const Query& query) {
        cursor = 0;
        token_count = 0;
        _query = query;
    }

    Token get_next_token() {
        skip_whitespace();

        if (cursor >= _query.size()) {
            return {"", TokenType::EOL};
        }

        if (auto token = try_single_char()) return *token;
        if (auto token = try_number())      return *token;
        if (auto token = try_identifier())  return *token;

        throw std::runtime_error(
            std::string("Unexpected character: ") + _query[cursor]
        );
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

    Token handle_string_literal() {
        // skipping opening quote
        cursor++;
        size_t start = cursor;

        while (cursor < _query.size() && _query[cursor] != '\'') {
            cursor++;
        }

        if (cursor >= _query.size()) {
            throw std::runtime_error("Unterminated string literal");
        }

        std::string value = _query.substr(start, cursor - start);
        cursor++;

        return Token{value, TokenType::STRING};
    }

    void skip_whitespace(){
        while (cursor < _query.size() &&  _query[cursor] == ' '){
                cursor += 1;
        }

        if (cursor >= _query.size()) {
            throw std::runtime_error("Unterminated string literal");
        }
    }

    MaybeToken try_single_char() {

        if (single_words.find(_query[cursor]) == single_words.end()) {
            return std::nullopt;
        }

        auto token_type = determine_token_type();

        if (token_type == TokenType::QUOTE) {
            return handle_string_literal();
        }

        if (token_type == TokenType::GREATER &&
            cursor + 1 < _query.size() &&
            _query[cursor + 1] == '=') {
            cursor += 2;
            return Token{">=", TokenType::GREATER_EQ};
        }

        if (token_type == TokenType::LESS &&
            cursor + 1 < _query.size() &&
            _query[cursor + 1] == '=') {
            cursor += 2;
            return Token{"<=", TokenType::LESS_EQ};
        }

        char c = _query[cursor];
        cursor++;

        return Token{std::string(1, c), token_type};
    }

    MaybeToken try_number(){
        
        if (std::isdigit(_query[cursor])){
            size_t start = cursor;

            while (start < _query.size() && std::isdigit(static_cast<unsigned char>(_query[start]))){
                start++;
            }
            
            size_t old_cursor_val = cursor;
            cursor = start;

            return Token{
                _query.substr(old_cursor_val, start - old_cursor_val),
                TokenType::NUMBER
            };
        }

        return std::nullopt;
    }

    MaybeToken try_identifier(){
        if (std::isalpha(static_cast<unsigned char>(_query[cursor])) || _query[cursor] == '_') {

            size_t start = cursor;
            
            // longest match possible 
            while (cursor < _query.size() && (std::isalnum(static_cast<unsigned char>(_query[cursor])) || _query[cursor] == '_')) {
                cursor++;
            }

            Word word = _query.substr(start, cursor - start);

            std::string lowered = word;
            std::transform(lowered.begin(), lowered.end(), lowered.begin(),
                        [](unsigned char c){ return std::tolower(c); });

            auto it = keywords.find(lowered);
            if (it != keywords.end()) {
                return Token{ word, it->second };
            }

            return Token{ word, TokenType::IDENTIFIER };
        }

        return std::nullopt;
    }
};