#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>

using namespace std;

void show_help() {
    cout << "Usage:" << endl;
    cout << "    jsoner <file> <element_path>" << endl;
}

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
    string value;
} token;

vector<token> tokenize_json_file(const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        cout << "Error: Vould not open file '" << file_name << "'" << endl;
        exit(1);
    }
    char character;
    tokenizer_state state = STATE_NORMAL;
    string value;
    vector<token> tokens;
    while (file.get(character)) {
        switch (state) {
            case STATE_NORMAL: {
                if (character == '"') {
                    state = STATE_STRING;
                    value = "";
                } else if (isdigit(character) || character == '-') {
                    state = STATE_NUMBER;
                    value = character;
                }
                break;
            }
            case STATE_STRING: {
                if (character == '"') {
                    state = STATE_NORMAL;
                    token new_token = {TOKEN_STRING, value};
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
                    token new_token = {TOKEN_NUMBER, value};
                    tokens.push_back(new_token);
                    file.unget();
                }
                break;
            }
            case STATE_WORD: {

                break;
            }
        }
    }
    file.close();
    return tokens;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        show_help();
        exit(1);
    }
    vector<token> tokens = tokenize_json_file(argv[1]);
    for (token t : tokens) {
        cout << "<";
        switch (t.type) {
            case 0:  cout << "STRING";           break;
            case 1:  cout << "NUMBER";           break;
            case 2:  cout << "TRUE";             break;
            case 3:  cout << "FALSE";            break;
            case 4:  cout << "NULL";             break;
            case 5:  cout << "OBJECT_OPEN";      break;
            case 6:  cout << "OBJECT_CLOSE";     break;
            case 7:  cout << "ARRAY_OPEN";       break;
            case 8:  cout << "ARRAY_CLOSE";      break;
            case 9:  cout << "COLUMN";           break;
            case 10: cout << "COMMA";            break;
        }
        cout << ": " << t.value << "> ";
    }
    return 0;
}
