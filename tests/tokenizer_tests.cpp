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

    ASSERT_GE(tokens.size(), 17);

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

TEST_F(TokenizerTest, InsertIntoBasic) {
    sql_parser.parse_tokens("INSERT INTO users VALUES (1, 2);");
    auto tokens = sql_parser.get_tokens();

    ASSERT_GE(tokens.size(), 9);

    EXPECT_EQ(tokens[0], (Tokenizer::Token{"INSERT", TokenType::INSERT}));
    EXPECT_EQ(tokens[1], (Tokenizer::Token{"INTO", TokenType::INTO}));
    EXPECT_EQ(tokens[2], (Tokenizer::Token{"users", TokenType::IDENTIFIER}));
    EXPECT_EQ(tokens[3], (Tokenizer::Token{"VALUES", TokenType::VALUES}));
    EXPECT_EQ(tokens[4], (Tokenizer::Token{"(", TokenType::LPAREN}));
    EXPECT_EQ(tokens[5], (Tokenizer::Token{"1", TokenType::NUMBER}));
    EXPECT_EQ(tokens[6], (Tokenizer::Token{",", TokenType::COMMA}));
    EXPECT_EQ(tokens[7], (Tokenizer::Token{"2", TokenType::NUMBER}));
    EXPECT_EQ(tokens[8], (Tokenizer::Token{")", TokenType::RPAREN}));

    EXPECT_EQ(tokens.back(), (Tokenizer::Token{";", TokenType::EOL}));
}

TEST_F(TokenizerTest, UpdateBasicSet) {
    sql_parser.parse_tokens("UPDATE users SET age = 21;");
    auto tokens = sql_parser.get_tokens();

    ASSERT_GE(tokens.size(), 7);

    EXPECT_EQ(tokens[0], (Tokenizer::Token{"UPDATE", TokenType::UPDATE}));
    EXPECT_EQ(tokens[1], (Tokenizer::Token{"users", TokenType::IDENTIFIER}));
    EXPECT_EQ(tokens[2], (Tokenizer::Token{"SET", TokenType::SET}));
    EXPECT_EQ(tokens[3], (Tokenizer::Token{"age", TokenType::IDENTIFIER}));
    EXPECT_EQ(tokens[4], (Tokenizer::Token{"=", TokenType::EQUAL}));
    EXPECT_EQ(tokens[5], (Tokenizer::Token{"21", TokenType::NUMBER}));

    EXPECT_EQ(tokens.back(), (Tokenizer::Token{";", TokenType::EOL}));
}

TEST_F(TokenizerTest, UpdateWithWhere) {
    sql_parser.parse_tokens("UPDATE users SET age = 21 WHERE id = 5;");
    auto tokens = sql_parser.get_tokens();

    ASSERT_GE(tokens.size(), 11);

    EXPECT_EQ(tokens[0], (Tokenizer::Token{"UPDATE", TokenType::UPDATE}));
    EXPECT_EQ(tokens[1], (Tokenizer::Token{"users", TokenType::IDENTIFIER}));
    EXPECT_EQ(tokens[2], (Tokenizer::Token{"SET", TokenType::SET}));
    EXPECT_EQ(tokens[3], (Tokenizer::Token{"age", TokenType::IDENTIFIER}));
    EXPECT_EQ(tokens[4], (Tokenizer::Token{"=", TokenType::EQUAL}));
    EXPECT_EQ(tokens[5], (Tokenizer::Token{"21", TokenType::NUMBER}));
    EXPECT_EQ(tokens[6], (Tokenizer::Token{"WHERE", TokenType::WHERE}));
    EXPECT_EQ(tokens[7], (Tokenizer::Token{"id", TokenType::IDENTIFIER}));
    EXPECT_EQ(tokens[8], (Tokenizer::Token{"=", TokenType::EQUAL}));
    EXPECT_EQ(tokens[9], (Tokenizer::Token{"5", TokenType::NUMBER}));

    EXPECT_EQ(tokens.back(), (Tokenizer::Token{";", TokenType::EOL}));
}

TEST_F(TokenizerTest, DropTable) {
    sql_parser.parse_tokens("DROP TABLE users;");
    auto tokens = sql_parser.get_tokens();

    ASSERT_EQ(tokens.size(), 4);

    EXPECT_EQ(tokens[0], (Tokenizer::Token{"DROP", TokenType::DROP}));
    EXPECT_EQ(tokens[1], (Tokenizer::Token{"TABLE", TokenType::TABLE}));
    EXPECT_EQ(tokens[2], (Tokenizer::Token{"users", TokenType::IDENTIFIER}));
    EXPECT_EQ(tokens[3], (Tokenizer::Token{";", TokenType::EOL}));
}

TEST_F(TokenizerTest, ValidIntegerLiteral) {
    sql_parser.parse_tokens("SELECT * FROM users WHERE id = 42;");
    auto tokens = sql_parser.get_tokens();

    ASSERT_GE(tokens.size(), 8);

    EXPECT_EQ(tokens[7], (Tokenizer::Token{"42", TokenType::NUMBER}));
}

TEST_F(TokenizerTest, ValidFloatLiteral) {
    sql_parser.parse_tokens("SELECT * FROM users WHERE score = 0.92;");
    auto tokens = sql_parser.get_tokens();

    ASSERT_GE(tokens.size(), 8);

    EXPECT_EQ(tokens[7], (Tokenizer::Token{"0.92", TokenType::FLOAT}));
}

TEST_F(TokenizerTest, InvalidLeadingDotFloat) {

    EXPECT_THROW(
        sql_parser.parse_tokens(
            "SELECT * FROM users WHERE score = .92;"
        ),
        std::runtime_error
    );
}

TEST_F(TokenizerTest, InvalidFloatLiteralMultipleDots) {
    EXPECT_THROW(
        sql_parser.parse_tokens(
            "SELECT * FROM users WHERE score = 1292992.1919.11991;"
        ),
        std::runtime_error
    );
}