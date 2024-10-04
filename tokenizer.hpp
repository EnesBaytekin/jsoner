#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string>
#include <vector>

enum class TokenizerState {
    STATE_NORMAL,
    STATE_STRING,
    STATE_NUMBER,
    STATE_WORD,
};

enum class TokenType {
    TOKEN_STRING,
    TOKEN_NUMBER,
    TOKEN_TRUE,
    TOKEN_FALSE,
    TOKEN_NULL,
    TOKEN_OBJECT_OPEN,
    TOKEN_OBJECT_CLOSE,
    TOKEN_ARRAY_OPEN,
    TOKEN_ARRAY_CLOSE,
    TOKEN_COLUMN,
    TOKEN_COMMA,
};

struct Token {
    TokenType type;
    std::string value;
};

std::vector<Token> tokenize_json_file(const std::string& file_name);

#endif
