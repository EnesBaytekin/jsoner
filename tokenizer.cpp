#include "tokenizer.hpp"
#include "utils.hpp"
#include <fstream>
#include <iostream>

std::vector<Token> tokenize_json_file(const std::string& file_name) {
    std::ifstream file(file_name);
    if (!file) {
        utils::show_error("Error: Could not open file '"+file_name+"'");
        exit(1);
    }
    char character;
    TokenizerState state = TokenizerState::STATE_NORMAL;
    std::string value;
    std::vector<Token> tokens;
    while (file.get(character)) {
        switch (state) {
            case TokenizerState::STATE_NORMAL: {
                if (character == '"') {
                    state = TokenizerState::STATE_STRING;
                    value = "";
                } else if (isdigit(character) || character == '-') {
                    state = TokenizerState::STATE_NUMBER;
                    value = character;
                } else if (isalpha(character)) {
                    state = TokenizerState::STATE_WORD;
                    value = character;
                } else if (character == ',') {
                    Token new_token = {TokenType::TOKEN_COMMA, std::string(1, character)};
                    tokens.push_back(new_token);
                } else if (character == ':') {
                    Token new_token = {TokenType::TOKEN_COLUMN, std::string(1, character)};
                    tokens.push_back(new_token);
                } else if (character == '{') {
                    Token new_token = {TokenType::TOKEN_OBJECT_OPEN, std::string(1, character)};
                    tokens.push_back(new_token);
                } else if (character == '}') {
                    Token new_token = {TokenType::TOKEN_OBJECT_CLOSE, std::string(1, character)};
                    tokens.push_back(new_token);
                } else if (character == '[') {
                    Token new_token = {TokenType::TOKEN_ARRAY_OPEN, std::string(1, character)};
                    tokens.push_back(new_token);
                } else if (character == ']') {
                    Token new_token = {TokenType::TOKEN_ARRAY_CLOSE, std::string(1, character)};
                    tokens.push_back(new_token);
                }
                break;
            }
            case TokenizerState::STATE_STRING: {
                if (character == '"') {
                    state = TokenizerState::STATE_NORMAL;
                    Token new_token = {TokenType::TOKEN_STRING, value};
                    tokens.push_back(new_token);
                    break;
                } else {
                    value += character;
                    break;
                }
                break;
            }
            case TokenizerState::STATE_NUMBER: {
                if (isdigit(character) || character == '.') {
                    value += character;
                } else {
                    state = TokenizerState::STATE_NORMAL;
                    Token new_token = {TokenType::TOKEN_NUMBER, value};
                    tokens.push_back(new_token);
                    file.unget();
                }
                break;
            }
            case TokenizerState::STATE_WORD: {
                if (isalpha(character) || character == '.') {
                    value += character;
                } else {
                    Token new_token;
                    if      (value == "true")  new_token = {TokenType::TOKEN_TRUE,  value};
                    else if (value == "false") new_token = {TokenType::TOKEN_FALSE, value};
                    else if (value == "null")  new_token = {TokenType::TOKEN_NULL,  value};
                    else {
                        utils::show_error("Error: undefined word: '"+value+"'");
                    }
                    state = TokenizerState::STATE_NORMAL;
                    tokens.push_back(new_token);
                    file.unget();
                }
                break;
            }
        }
    }
    file.close();
    return tokens;
}