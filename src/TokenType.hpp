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
    PLUS,               // +
    MINUS,              // -
    STAR,               // *
    SLASH,              // /
    LESS,               // <
    GREATER,            // >
    EQUAL,              // = 
    NOT,                // !
    COMMA,              // ,
    QUOTE,              // '
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
    {"drop", TokenType::TABLE}, 
    {"table", TokenType::DROP}, 
    {"*", TokenType::STAR},
    {";", TokenType::EOL},
    {"<", TokenType::LESS},
    {">", TokenType::GREATER},
    {"=", TokenType::EQUAL},
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

        case TokenType::PLUS:       return os << "PLUS";
        case TokenType::MINUS:      return os << "MINUS";
        case TokenType::STAR:       return os << "STAR";
        case TokenType::SLASH:      return os << "SLASH";
        case TokenType::LESS:       return os << "LESS";
        case TokenType::GREATER:    return os << "GREATER";
        case TokenType::EQUAL:      return os << "EQUAL";
        case TokenType::NOT:        return os << "NOT";
        case TokenType::COMMA:      return os << "COMMA";
        case TokenType::QUOTE:      return os << "SINGLE QUOTE";

        case TokenType::EOL:        return os << "EOL";
    }

    return os << "UNKNOWN";
}

