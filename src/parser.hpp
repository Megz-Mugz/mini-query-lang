#include <iostream>
#include "Tokenizer.hpp"
#include "debug.hpp"   
#include <vector> 

class Parser

{

public:

    using TokenStream = std::vector<Tokenizer::Token>;
    
    /**
     * @brief public method that 
     * 
     * @param query user inputted query that will be tokenized
     * @return the semantic validity of the inputted query
     */
    bool parse_tokens(const Tokenizer::Query& query){
        // TODO this will build out the AST
        // the AST will be used used for semantic analysis

        // 1. characters -> tokens
        tokenize_string(query);
        // 2. token -> parse tree 
        build_ast();
        // 3. parse tree -> ??
        semantic_analysis();
        return semantic_validity;
    }

    TokenStream get_tokens(){return tokens;}

    bool get_semantic_validity(){return semantic_validity;}
    

private:
    
    TokenStream tokens;
    bool semantic_validity = false;
    
    /**
     * @brief tokenizes the query and builds out the 'tokens' vector
     * 
     * @param query user inputted query that will be tokenized
     */
    void tokenize_string(const Tokenizer::Query& query){

        Tokenizer tokenizer(query);
        Tokenizer::Token next_token;

        while (true){
            // debugger;
            next_token = tokenizer.get_next_token();
            
            tokens.push_back(next_token);
            
            if (next_token.second == TokenType::EOL){break;}
            
        }
    }

    void build_ast(){

    }

    void semantic_analysis(){

    }

};