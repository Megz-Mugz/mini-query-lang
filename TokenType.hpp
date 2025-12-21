#pragma once

#include <iostream>
#include <unordered_map>

enum class TokenType {
    CREATE,
    SELECT, 
    FROM, 
    WHERE, 
    INSERT, 
    VALUES,
    UPDATE, 
    SET,
    DELETE, 
    DROP,
    TABLE,
    IDENTIFIER, 
    PLUS,           // +
    MINUS,          // -
    STAR,           // *
    SLASH,          // /
    LT,             // <
    LE,             // <= 
    GT,             // >
    GE,             // >=
    EQ,             // = 
    NE,             // != 
    EOL
};

const std::unordered_map<std::string, TokenType> keywords = {
    {"create", TokenType::CREATE},
    {"select", TokenType::SELECT}, 
    {"from", TokenType::FROM}, 
    {"where", TokenType::WHERE}, 
    {"insert", TokenType::INSERT}, 
    {"update", TokenType::UPDATE}, 
    {"values", TokenType::VALUES}, 
    {"set", TokenType::SET}, 
    {"delete", TokenType::DELETE}, 
    {"drop", TokenType::TABLE}, 
    {"table", TokenType::DROP}, 
    {"*", TokenType::STAR},
    {";", TokenType::EOL},
    {"<", TokenType::LT},
    {"<=", TokenType::LE},
    {">", TokenType::GT},
    {">=", TokenType::GE},
    {"=", TokenType::EQ},
    {"!=", TokenType::NE},
};


#include <ostream>

inline std::ostream& operator<<(std::ostream& os, TokenType type) {
    switch (type) {
        case TokenType::CREATE:     return os << "CREATE";
        case TokenType::SELECT:     return os << "SELECT";
        case TokenType::FROM:       return os << "FROM";
        case TokenType::WHERE:      return os << "WHERE";
        case TokenType::INSERT:     return os << "INSERT";
        case TokenType::VALUES:     return os << "VALUES";
        case TokenType::UPDATE:     return os << "UPDATE";
        case TokenType::SET:        return os << "SET";
        case TokenType::DELETE:     return os << "DELETE";
        case TokenType::DROP:       return os << "DROP";
        case TokenType::TABLE:      return os << "TABLE";
        case TokenType::IDENTIFIER: return os << "IDENTIFIER";

        case TokenType::PLUS:       return os << "PLUS";
        case TokenType::MINUS:      return os << "MINUS";
        case TokenType::STAR:       return os << "STAR";
        case TokenType::SLASH:      return os << "SLASH";

        case TokenType::LT:         return os << "LT";
        case TokenType::LE:         return os << "LE";
        case TokenType::GT:         return os << "GT";
        case TokenType::GE:         return os << "GE";
        case TokenType::EQ:         return os << "EQ";
        case TokenType::NE:         return os << "NE";

        case TokenType::EOL:        return os << "EOL";
    }

    return os << "UNKNOWN";
}

