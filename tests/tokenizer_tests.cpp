#include "parser.hpp"
#include <gtest/gtest.h>

class TokenizerTest : public ::testing::Test {
protected:
    Parser sql_parser;
};

TEST_F(TokenizerTest, BasicSelectStar) {
    sql_parser.parse_tokens("select * from users;");
    auto tokens = sql_parser.get_tokens();

    ASSERT_EQ(tokens.size(), 5);

    EXPECT_EQ(tokens[0], (Tokenizer::Token{"select", TokenType::SELECT}));
    EXPECT_EQ(tokens[1], (Tokenizer::Token{"*", TokenType::STAR}));
    EXPECT_EQ(tokens[2], (Tokenizer::Token{"from", TokenType::FROM}));
    EXPECT_EQ(tokens[3], (Tokenizer::Token{"users", TokenType::IDENTIFIER}));
    EXPECT_EQ(tokens[4], (Tokenizer::Token{";", TokenType::EOL}));
}

TEST_F(TokenizerTest, WhereClause) {
    sql_parser.parse_tokens("SELECT * FROM users WHERE id = 1;");
    auto tokens = sql_parser.get_tokens();

    EXPECT_EQ(tokens[4], (Tokenizer::Token{"WHERE", TokenType::WHERE}));
    EXPECT_EQ(tokens[5], (Tokenizer::Token{"id", TokenType::IDENTIFIER}));
    EXPECT_EQ(tokens[6], (Tokenizer::Token{"=", TokenType::EQUAL}));
    EXPECT_EQ(tokens[7], (Tokenizer::Token{"1", TokenType::NUMBER}));
}

TEST_F(TokenizerTest, ArithmeticExpression) {
    sql_parser.parse_tokens("select * from users where id = 1 + 2;");
    auto tokens = sql_parser.get_tokens();

    EXPECT_EQ(tokens[7], (Tokenizer::Token{"1", TokenType::NUMBER}));
    EXPECT_EQ(tokens[8], (Tokenizer::Token{"+", TokenType::PLUS}));
    EXPECT_EQ(tokens[9], (Tokenizer::Token{"2", TokenType::NUMBER}));
}


TEST_F(TokenizerTest, MixedArithmeticExpression) {
    sql_parser.parse_tokens(
        "SELECT name, age, dob from customers where age >= 1 * 5 / 3 + 1000;"
    );

    auto tokens = sql_parser.get_tokens();

    ASSERT_GE(tokens.size(), 17); // sanity check

    EXPECT_EQ(tokens[0],  (Tokenizer::Token{"SELECT", TokenType::SELECT}));
    EXPECT_EQ(tokens[1],  (Tokenizer::Token{"name", TokenType::IDENTIFIER}));
    EXPECT_EQ(tokens[2],  (Tokenizer::Token{",", TokenType::COMMA}));
    EXPECT_EQ(tokens[3],  (Tokenizer::Token{"age", TokenType::IDENTIFIER}));
    EXPECT_EQ(tokens[4],  (Tokenizer::Token{",", TokenType::COMMA}));
    EXPECT_EQ(tokens[5],  (Tokenizer::Token{"dob", TokenType::IDENTIFIER}));
    EXPECT_EQ(tokens[6],  (Tokenizer::Token{"from", TokenType::FROM}));
    EXPECT_EQ(tokens[7],  (Tokenizer::Token{"customers", TokenType::IDENTIFIER}));
    EXPECT_EQ(tokens[8],  (Tokenizer::Token{"where", TokenType::WHERE}));
    EXPECT_EQ(tokens[9],  (Tokenizer::Token{"age", TokenType::IDENTIFIER}));
    EXPECT_EQ(tokens[10], (Tokenizer::Token{">=", TokenType::GREATER_EQ}));

    EXPECT_EQ(tokens[11], (Tokenizer::Token{"1", TokenType::NUMBER}));
    EXPECT_EQ(tokens[12], (Tokenizer::Token{"*", TokenType::STAR}));
    EXPECT_EQ(tokens[13], (Tokenizer::Token{"5", TokenType::NUMBER}));
    EXPECT_EQ(tokens[14], (Tokenizer::Token{"/", TokenType::SLASH}));
    EXPECT_EQ(tokens[15], (Tokenizer::Token{"3", TokenType::NUMBER}));
    EXPECT_EQ(tokens[16], (Tokenizer::Token{"+", TokenType::PLUS}));
    EXPECT_EQ(tokens[17], (Tokenizer::Token{"1000", TokenType::NUMBER}));

    EXPECT_EQ(tokens.back(), (Tokenizer::Token{";", TokenType::EOL}));
}

