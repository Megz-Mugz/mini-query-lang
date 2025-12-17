#pragma once

#include <iostream>
#include <unordered_map>

enum class TokenType {
    SELECT, 
    FROM, 
    WHERE, 
    INSERT, 
    UPDATE, 
    IDENTIFIER, 
    EOL
};

const std::unordered_map<std::string, TokenType> keywords  = {
    {"select", TokenType::SELECT}, 
    {"from", TokenType::FROM}, 
    {"where", TokenType::WHERE}, 
    {"insert", TokenType::INSERT}, 
    {"update", TokenType::UPDATE}, 
    {";", TokenType::EOL}
};

