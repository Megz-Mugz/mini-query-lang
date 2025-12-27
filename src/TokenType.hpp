#pragma once

#include <iostream>
#include <unordered_map>

enum class TokenType {
    CREATE,
    SELECT, 
    FROM, 
    WHERE, 
    INSERT, 
    INTO,
    VALUES,
    UPDATE, 
    SET,
    DELETE, 
    DROP,
    TABLE,
    IDENTIFIER, 
    NUMBER,
    FLOAT,
    STRING,             
    PLUS,               // +
    MINUS,              // -
    STAR,               // *
    SLASH,              // /
    LESS,               // <
    LESS_EQ,            // >=
    GREATER,            // >
    GREATER_EQ,         // >=
    EQUAL,              // = 
    NOT,                // !
    COMMA,              // ,
    QUOTE,              // '
    LPAREN,             // (
    RPAREN,             // )
    EOL                 // ;
};

const std::unordered_map<std::string, TokenType> keywords = {
    {"create", TokenType::CREATE},
    {"select", TokenType::SELECT}, 
    {"from", TokenType::FROM}, 
    {"where", TokenType::WHERE}, 
    {"insert", TokenType::INSERT}, 
    {"into", TokenType::INTO}, 
    {"update", TokenType::UPDATE}, 
    {"values", TokenType::VALUES}, 
    {"set", TokenType::SET}, 
    {"delete", TokenType::DELETE}, 
    {"drop", TokenType::DROP}, 
    {"table", TokenType::TABLE}, 
    {"*", TokenType::STAR},
    {";", TokenType::EOL},
    {"<", TokenType::LESS},
    {">", TokenType::GREATER},
    {"=", TokenType::EQUAL},
    {"(", TokenType::LPAREN},
    {")", TokenType::RPAREN},
    {"!", TokenType::NOT},
};


#include <ostream>

inline std::ostream& operator<<(std::ostream& os, TokenType type) {
    switch (type) {
        case TokenType::CREATE:     return os << "CREATE";
        case TokenType::SELECT:     return os << "SELECT";
        case TokenType::FROM:       return os << "FROM";
        case TokenType::WHERE:      return os << "WHERE";
        case TokenType::INSERT:     return os << "INSERT";
        case TokenType::INTO:       return os << "INTO";
        case TokenType::VALUES:     return os << "VALUES";
        case TokenType::UPDATE:     return os << "UPDATE";
        case TokenType::SET:        return os << "SET";
        case TokenType::DELETE:     return os << "DELETE";
        case TokenType::DROP:       return os << "DROP";
        case TokenType::TABLE:      return os << "TABLE";

        case TokenType::IDENTIFIER: return os << "IDENTIFIER";
        case TokenType::NUMBER:     return os << "NUMBER";
        case TokenType::FLOAT:     return os << "FLOAT";
        case TokenType::STRING:     return os << "STRING";

        case TokenType::PLUS:       return os << "PLUS";
        case TokenType::MINUS:      return os << "MINUS";
        case TokenType::STAR:       return os << "STAR";
        case TokenType::SLASH:      return os << "SLASH";
        case TokenType::LESS:       return os << "LESS";
        case TokenType::GREATER:    return os << "GREATER";
        case TokenType::GREATER_EQ: return os << "GREATER_EQ";
        case TokenType::LESS_EQ:    return os << "LESS_EQ";
        case TokenType::EQUAL:      return os << "EQUAL";
        case TokenType::NOT:        return os << "NOT";
        case TokenType::COMMA:      return os << "COMMA";
        case TokenType::QUOTE:      return os << "SINGLE QUOTE";

        case TokenType::LPAREN:      return os << "LEFT PAREN";
        case TokenType::RPAREN:      return os << "RIGHT PAREN";

        case TokenType::EOL:        return os << "EOL";
    }

    return os << "UNKNOWN";
}

