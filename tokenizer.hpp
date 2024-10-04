#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string>
#include <vector>

typedef enum {
    STATE_NORMAL,
    STATE_STRING,
    STATE_NUMBER,
    STATE_WORD,
} tokenizer_state;

typedef enum {
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
} token_type;

typedef struct {
    token_type type;
    std::string value;
} token;

std::vector<token> tokenize_json_file(const std::string& file_name);

#endif
