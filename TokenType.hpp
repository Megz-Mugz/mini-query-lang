#pragma once

#include <iostream>
#include <unordered_map>

enum class TokenType {
    SELECT, 
    FROM, 
    WHERE, 
    INSERT, 
    VALUES,
    UPDATE, 
    SET,
    DELETE, 
    DROP,
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
    {"select", TokenType::SELECT}, 
    {"from", TokenType::FROM}, 
    {"where", TokenType::WHERE}, 
    {"insert", TokenType::INSERT}, 
    {"update", TokenType::UPDATE}, 
    {"values", TokenType::VALUES}, 
    {"set", TokenType::SET}, 
    {"delete", TokenType::DELETE}, 
    {"drop", TokenType::DROP}, 
    {"*", TokenType::STAR},
    {";", TokenType::EOL},
    {"<", TokenType::LT},
    {"<=", TokenType::LE},
    {">", TokenType::GT},
    {">=", TokenType::GE},
    {"=", TokenType::EQ},
    {"!=", TokenType::NE},
};

