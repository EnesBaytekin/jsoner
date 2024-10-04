#ifndef PARSER_HPP
#define PARSER_HPP

#include "tokenizer.hpp"
#include <vector>
#include <variant>

enum class NodeType {
    JSON,
    ELEMENTS,
    ELEMENT,
    MEMBERS,
    MEMBER,
    TOKEN,
};

struct Node {
    NodeType type;
    std::variant<std::vector<Node*>, Token> children;
    Node(NodeType _type);
    Node(Token token);
};

class Parser {
private:
    int index;
    const std::vector<Token>& tokens;
public:
    Parser(const std::vector<Token>& _tokens);
    Node* match(const TokenType& token_type);
    Node* parse_json();
    Node* parse_elements();
    Node* parse_element();
    Node* parse_members();
    Node* parse_member();
    void print_tree(Node* node, std::string indent);
};

#endif