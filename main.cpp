#include <iostream>
#include "tokenizer.hpp"
#include "utils.hpp"
#include "parser.hpp"

using namespace std;

void print_tokens(const vector<Token>& tokens) {
    for (Token _token : tokens) {
        cout << "<";
        switch (_token.type) {
            case TokenType::TOKEN_STRING:       cout << "STRING";       break;
            case TokenType::TOKEN_NUMBER:       cout << "NUMBER";       break;
            case TokenType::TOKEN_TRUE:         cout << "TRUE";         break;
            case TokenType::TOKEN_FALSE:        cout << "FALSE";        break;
            case TokenType::TOKEN_NULL:         cout << "NULL";         break;
            case TokenType::TOKEN_OBJECT_OPEN:  cout << "OBJECT_OPEN";  break;
            case TokenType::TOKEN_OBJECT_CLOSE: cout << "OBJECT_CLOSE"; break;
            case TokenType::TOKEN_ARRAY_OPEN:   cout << "ARRAY_OPEN";   break;
            case TokenType::TOKEN_ARRAY_CLOSE:  cout << "ARRAY_CLOSE";  break;
            case TokenType::TOKEN_COLUMN:       cout << "COLUMN";       break;
            case TokenType::TOKEN_COMMA:        cout << "COMMA";        break;
        }
        cout << ": '" << _token.value << "'> ";
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        utils::show_help();
        return 1;
    }
    vector<Token> tokens = tokenize_json_file(argv[1]);
    Parser parser = Parser(tokens);
    Node* parse_tree = parser.parse_json();
    string json = "";
    parser.create_json(parse_tree, json);
    cout << json << endl;
    return 0;
}
