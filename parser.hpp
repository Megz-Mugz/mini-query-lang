#include <iostream>
#include "Tokenizer.hpp"
#include "debug.hpp"   
#include <vector> 

class Parser

{

    public:
    
    using TokenStream = std::vector<Tokenizer::Token>;
    
    static const TokenStream& get_tokens(Tokenizer::Query user_query){
        Parser::parse(user_query);
        return tokens;
    }

private:
    inline static TokenStream tokens;

    static TokenStream parse(const Tokenizer::Query& query){
        
        Tokenizer tokenizer(query);
        Tokenizer::Token next_token;
        
        auto first_word = tokenizer.get_next_token();
        tokens.push_back(first_word);

        switch (first_word.second) {
            
            
            case (TokenType::SELECT):
                
                // debugger;
                
                while (true){
                    next_token = tokenizer.get_next_token();
                    tokens.push_back(next_token);

                    if (next_token.second == TokenType::EOL){
                        break;
                    }

                    continue;
                }

                break;
            
            default:
                break;

        }
        
        
        // std::cout << "finished tokenizing" << std::endl;
        return tokens;
    }

};