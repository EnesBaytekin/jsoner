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
    tokenizer_state state = STATE_NORMAL;
    std::string value;
    std::vector<Token> tokens;
    while (file.get(character)) {
        switch (state) {
            case STATE_NORMAL: {
                if (character == '"') {
                    state = STATE_STRING;
                    value = "";
                } else if (isdigit(character) || character == '-') {
                    state = STATE_NUMBER;
                    value = character;
                } else if (isalpha(character)) {
                    state = STATE_WORD;
                    value = character;
                } else if (character == ',') {
                    Token new_token = {TOKEN_COMMA, std::string(1, character)};
                    tokens.push_back(new_token);
                } else if (character == ':') {
                    Token new_token = {TOKEN_COLUMN, std::string(1, character)};
                    tokens.push_back(new_token);
                } else if (character == '{') {
                    Token new_token = {TOKEN_OBJECT_OPEN, std::string(1, character)};
                    tokens.push_back(new_token);
                } else if (character == '}') {
                    Token new_token = {TOKEN_OBJECT_CLOSE, std::string(1, character)};
                    tokens.push_back(new_token);
                } else if (character == '[') {
                    Token new_token = {TOKEN_ARRAY_OPEN, std::string(1, character)};
                    tokens.push_back(new_token);
                } else if (character == ']') {
                    Token new_token = {TOKEN_ARRAY_CLOSE, std::string(1, character)};
                    tokens.push_back(new_token);
                }
                break;
            }
            case STATE_STRING: {
                if (character == '"') {
                    state = STATE_NORMAL;
                    Token new_token = {TOKEN_STRING, value};
                    tokens.push_back(new_token);
                    break;
                } else {
                    value += character;
                    break;
                }
                break;
            }
            case STATE_NUMBER: {
                if (isdigit(character) || character == '.') {
                    value += character;
                } else {
                    state = STATE_NORMAL;
                    Token new_token = {TOKEN_NUMBER, value};
                    tokens.push_back(new_token);
                    file.unget();
                }
                break;
            }
            case STATE_WORD: {
                if (isalpha(character) || character == '.') {
                    value += character;
                } else {
                    Token new_token;
                    if      (value == "true")  new_token = {TOKEN_TRUE,  value};
                    else if (value == "false") new_token = {TOKEN_FALSE, value};
                    else if (value == "null")  new_token = {TOKEN_NULL,  value};
                    else {
                        utils::show_error("Error: undefined word: '"+value+"'");
                    }
                    state = STATE_NORMAL;
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