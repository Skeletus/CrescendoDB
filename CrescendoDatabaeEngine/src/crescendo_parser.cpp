#include "crescendo_parser.h"
#include <cctype> // Para funciones de manejo de caracteres como isdigit, isalpha
#include <iostream>
#include <unordered_set>

namespace Crescendo {

// Conjunto de palabras clave de SQL
const std::unordered_set<std::string> SQL_KEYWORDS = {
    "SELECT", "FROM", "WHERE", "INSERT", "INTO", "VALUES",
    "UPDATE", "SET", "DELETE", "CREATE", "TABLE", "DROP"
};

CrescendoParser::CrescendoParser(const std::string& query) : query_(query), current_pos_(0) {}

std::vector<Token> CrescendoParser::tokenize() {
    std::vector<Token> tokens;
    
    while (current_pos_ < query_.length()) {
        skipWhitespace(); // Omitir espacios en blanco

        if (current_pos_ >= query_.length()) {
            break;
        }

        Token token = extractToken();
        tokens.push_back(token);

        if (token.type == TokenType::END_OF_FILE) {
            break;
        }
    }

    return tokens;
}

char CrescendoParser::peek() const {
    return (current_pos_ < query_.length()) ? query_[current_pos_] : '\0';
}

char CrescendoParser::get() {
    return (current_pos_ < query_.length()) ? query_[current_pos_++] : '\0';
}

void CrescendoParser::skipWhitespace() {
    while (std::isspace(peek())) {
        get();
    }
}

Token CrescendoParser::extractToken() {
    char current = peek();

    if (std::isalpha(current)) {
        // Extraer una palabra clave o identificador
        std::string word;
        while (std::isalnum(peek()) || peek() == '_') {
            word += get();
        }

        if (isKeyword(word)) {
            return {TokenType::KEYWORD, word};
        } else {
            return {TokenType::IDENTIFIER, word};
        }
    } else if (std::isdigit(current)) {
        // Extraer un número
        std::string number;
        while (std::isdigit(peek())) {
            number += get();
        }
        return {TokenType::NUMBER, number};
    } else if (current == '\'') {
        // Extraer un literal de cadena
        std::string str_literal;
        get(); // Consumir el carácter de apertura de la cadena
        while (peek() != '\'' && peek() != '\0') {
            str_literal += get();
        }
        get(); // Consumir el carácter de cierre de la cadena
        return {TokenType::STRING, str_literal};
    } else if (current == '(') {
        get();
        return {TokenType::PAREN_OPEN, "("};
    } else if (current == ')') {
        get();
        return {TokenType::PAREN_CLOSE, ")"};
    } else if (current == ',') {
        get();
        return {TokenType::COMMA, ","};
    } else if (current == ';') {
        get();
        return {TokenType::SEMICOLON, ";"};
    } else if (current == '\0') {
        return {TokenType::END_OF_FILE, ""};
    } else {
        // Token desconocido o no manejado
        get();
        return {TokenType::UNKNOWN, std::string(1, current)};
    }
}

bool CrescendoParser::isKeyword(const std::string& word) const {
    return SQL_KEYWORDS.find(word) != SQL_KEYWORDS.end();
}

// Añadir al final del archivo sql_parser.cpp
ASTNode* CrescendoParser::parse() {
    tokens_ = tokenize();
    current_token_index_ = 0;

    // Por ahora, solo analizamos consultas SELECT
    if (peekToken().type == TokenType::KEYWORD && peekToken().value == "SELECT") {
        return parseSelect();
    } else {
        std::cerr << "Error: solo se soportan consultas SELECT por ahora." << std::endl;
        return nullptr;
    }
}

Token CrescendoParser::nextToken() {
    return (current_token_index_ < tokens_.size()) ? tokens_[current_token_index_++] : Token{TokenType::END_OF_FILE, ""};
}

Token CrescendoParser::peekToken() const {
    return (current_token_index_ < tokens_.size()) ? tokens_[current_token_index_] : Token{TokenType::END_OF_FILE, ""};
}

ASTNode* CrescendoParser::parseSelect() {
    ASTNode* root = new ASTNode(TokenType::KEYWORD, "SELECT");

    nextToken(); // Consumir la palabra clave SELECT

    // Agregar columnas seleccionadas al AST
    while (peekToken().type != TokenType::KEYWORD && peekToken().value != "FROM") {
        root->children.push_back(new ASTNode(TokenType::IDENTIFIER, nextToken().value));
        if (peekToken().type == TokenType::COMMA) {
            nextToken(); // Consumir la coma
        }
    }

    if (peekToken().value != "FROM") {
        std::cerr << "Error: se esperaba 'FROM' después de SELECT." << std::endl;
        delete root;
        return nullptr;
    }

    // Añadir la tabla de origen
    nextToken(); // Consumir 'FROM'
    if (peekToken().type == TokenType::IDENTIFIER) {
        root->children.push_back(new ASTNode(TokenType::IDENTIFIER, nextToken().value));
    } else {
        std::cerr << "Error: se esperaba un nombre de tabla después de 'FROM'." << std::endl;
        delete root;
        return nullptr;
    }

    // TODO: Agregar lógica para WHERE, JOIN, ORDER BY, etc.

    return root;
}

} // namespace Crescendo
