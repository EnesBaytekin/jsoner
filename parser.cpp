#include "parser.hpp"
#include <iostream>

void debug(const std::string& message) {
    std::cout << message << std::endl;
}

std::string get_node_type_str(NodeType node_type) {
    switch (node_type) {
        case NodeType::JSON:      return "JSON";
        case NodeType::ELEMENTS:  return "ELEMENTS";
        case NodeType::ELEMENT:   return "ELEMENT";
        case NodeType::MEMBERS:   return "MEMBERS";
        case NodeType::MEMBER:    return "MEMBER";
        case NodeType::TOKEN:     return "TOKEN";
    }
}

std::string get_token_type_str(TokenType token_type) {
    switch (token_type) {
        case TokenType::TOKEN_STRING:       return "STRING";
        case TokenType::TOKEN_NUMBER:       return "NUMBER";
        case TokenType::TOKEN_TRUE:         return "TRUE";
        case TokenType::TOKEN_FALSE:        return "FALSE";
        case TokenType::TOKEN_NULL:         return "NULL";
        case TokenType::TOKEN_OBJECT_OPEN:  return "OBJECT_OPEN";
        case TokenType::TOKEN_OBJECT_CLOSE: return "OBJECT_CLOSE";
        case TokenType::TOKEN_ARRAY_OPEN:   return "ARRAY_OPEN";
        case TokenType::TOKEN_ARRAY_CLOSE:  return "ARRAY_CLOSE";
        case TokenType::TOKEN_COLUMN:       return "COLUMN";
        case TokenType::TOKEN_COMMA:        return "COMMA";
    }
}

///////////////////

Node::Node(NodeType _type) : type(_type) {
    children = std::vector<Node*>();
}
Node::Node(Token token) : type(NodeType::TOKEN) {
    children = token;
}

Parser::Parser(const std::vector<Token>& _tokens) : tokens(_tokens) {
    index = 0;
}

Node* Parser::match(const TokenType& token_type) {
    debug("matching... "+get_token_type_str(tokens[index].type)+" == "+get_token_type_str(token_type));
    if (index < tokens.size()
    && tokens[index].type == token_type) {
        debug(" . matched <"+get_token_type_str(tokens[index].type)+": '"+tokens[index].value+"'>, index: "+std::to_string(index+1));
        return new Node(tokens[index++]);
    }
    return nullptr;
}

Node* Parser::parse_json() {
    int checkpoint = index;
    if (Node* element = parse_element()) {
        Node* node = new Node(NodeType::JSON);
        std::get<std::vector<Node*>>(node->children).push_back(element);
        return node;
    }
    index = checkpoint;
    return nullptr;
}

Node* Parser::parse_elements() {
    if (Node* element = parse_element()) {
    int checkpoint = index;
    if (Node* comma = match(TokenType::TOKEN_COMMA)) {
    if (Node* elements = parse_elements()) {
        Node* node = new Node(NodeType::ELEMENTS);
        std::get<std::vector<Node*>>(node->children).push_back(element);
        std::get<std::vector<Node*>>(node->children).push_back(comma);
        std::get<std::vector<Node*>>(node->children).push_back(elements);
        return node;
    }}
    index = checkpoint;
    Node* node = new Node(NodeType::ELEMENTS);
    std::get<std::vector<Node*>>(node->children).push_back(element);
    return node;
    }
    return nullptr;
}

Node* Parser::parse_element() {
    int checkpoint = index;
    if (Node* string = match(TokenType::TOKEN_STRING)) {
        Node* node = new Node(NodeType::ELEMENT);
        std::get<std::vector<Node*>>(node->children).push_back(string);
        return node;
    }
    index = checkpoint;
    if (Node* number = match(TokenType::TOKEN_NUMBER)) {
        Node* node = new Node(NodeType::ELEMENT);
        std::get<std::vector<Node*>>(node->children).push_back(number);
        return node;
    }
    index = checkpoint;
    if (Node* _true = match(TokenType::TOKEN_TRUE)) {
        Node* node = new Node(NodeType::ELEMENT);
        std::get<std::vector<Node*>>(node->children).push_back(_true);
        return node;
    }
    index = checkpoint;
    if (Node* _false = match(TokenType::TOKEN_FALSE)) {
        Node* node = new Node(NodeType::ELEMENT);
        std::get<std::vector<Node*>>(node->children).push_back(_false);
        return node;
    }
    index = checkpoint;
    if (Node* _null = match(TokenType::TOKEN_NULL)) {
        Node* node = new Node(NodeType::ELEMENT);
        std::get<std::vector<Node*>>(node->children).push_back(_null);
        return node;
    }
    index = checkpoint;
    if (Node* object_open = match(TokenType::TOKEN_OBJECT_OPEN)) {
    if (Node* members = parse_members()) {
    if (Node* object_close = match(TokenType::TOKEN_OBJECT_CLOSE)) {
        Node* node = new Node(NodeType::ELEMENT);
        std::get<std::vector<Node*>>(node->children).push_back(object_open);
        std::get<std::vector<Node*>>(node->children).push_back(members);
        std::get<std::vector<Node*>>(node->children).push_back(object_close);
        return node;
    }}}
    index = checkpoint;
    if (Node* object_open = match(TokenType::TOKEN_OBJECT_OPEN)) {
    if (Node* object_close = match(TokenType::TOKEN_OBJECT_CLOSE)) {
        Node* node = new Node(NodeType::ELEMENT);
        std::get<std::vector<Node*>>(node->children).push_back(object_open);
        std::get<std::vector<Node*>>(node->children).push_back(object_close);
        return node;
    }}
    index = checkpoint;
    if (Node* array_open = match(TokenType::TOKEN_ARRAY_OPEN)) {
    if (Node* elements = parse_elements()) {
    if (Node* array_close = match(TokenType::TOKEN_ARRAY_CLOSE)) {
        Node* node = new Node(NodeType::ELEMENT);
        std::get<std::vector<Node*>>(node->children).push_back(array_open);
        std::get<std::vector<Node*>>(node->children).push_back(elements);
        std::get<std::vector<Node*>>(node->children).push_back(array_close);
        return node;
    }}}
    index = checkpoint;
    if (Node* array_open = match(TokenType::TOKEN_ARRAY_OPEN)) {
    if (Node* array_close = match(TokenType::TOKEN_ARRAY_CLOSE)) {
        Node* node = new Node(NodeType::ELEMENT);
        std::get<std::vector<Node*>>(node->children).push_back(array_open);
        std::get<std::vector<Node*>>(node->children).push_back(array_close);
        return node;
    }}
    index = checkpoint;
    return nullptr;
}

Node* Parser::parse_members() {
    if (Node* member = parse_member()) {
    int checkpoint = index;
    if (Node* comma = match(TokenType::TOKEN_COMMA)) {
    if (Node* members = parse_members()) {
        Node* node = new Node(NodeType::ELEMENT);
        std::get<std::vector<Node*>>(node->children).push_back(member);
        std::get<std::vector<Node*>>(node->children).push_back(comma);
        std::get<std::vector<Node*>>(node->children).push_back(members);
        return node;
    }}
    index = checkpoint;
    Node* node = new Node(NodeType::ELEMENT);
    std::get<std::vector<Node*>>(node->children).push_back(member);
    return node;
    }
    return nullptr;
}

Node* Parser::parse_member() {
    int checkpoint = index;
    if (Node* string = match(TokenType::TOKEN_STRING)) {
    if (Node* column = match(TokenType::TOKEN_COLUMN)) {
    if (Node* element = parse_element()) {
        Node* node = new Node(NodeType::ELEMENT);
        std::get<std::vector<Node*>>(node->children).push_back(string);
        std::get<std::vector<Node*>>(node->children).push_back(column);
        std::get<std::vector<Node*>>(node->children).push_back(element);
        return node;
    }}}
    index = checkpoint;
    return nullptr;
}

void Parser::print_tree(Node* node, std::string indent) {
    if (!node) return;
    std::cout << indent << "{type: " << get_node_type_str(node->type);
    if (node->type == NodeType::TOKEN) {
        std::cout << ", token: ";
        Token token = std::get<Token>(node->children);
        std::cout << get_token_type_str(token.type) << "]}" << std::endl;
    } else {
        std::cout << ", children: [" << std::endl;
        std::vector<Node*> children = std::get<std::vector<Node*>>(node->children);
        for (const auto& child : children) {
            print_tree(child, indent+"  ");
            std::cout;
        }
        std::cout << indent << "]}" << std::endl;
    }
}
