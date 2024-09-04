#ifndef CRESCENDO_PARSER_H
#define CRESCENDO_PARSER_H

#include <string>
#include <vector>

namespace Crescendo {

    // Enumeración de tipos de tokens posibles
    enum class TokenType {
        KEYWORD,
        IDENTIFIER,
        OPERATOR,
        LITERAL,
        NUMBER,
        STRING,
        PAREN_OPEN,
        PAREN_CLOSE,
        COMMA,
        SEMICOLON,
        END_OF_FILE,
        UNKNOWN
    };

    // Estructura para representar un token
    struct Token {
        TokenType type;
        std::string value;
    };

    // Estructura de nodos del árbol de análisis para representar una consulta SQL
    struct ASTNode {
        TokenType type;
        std::string value;
        std::vector<ASTNode*> children;
        
        ASTNode(TokenType type, const std::string& value) : type(type), value(value) {}

        // Obtener todas las columnas seleccionadas en una consulta SELECT
        std::vector<std::string> getSelectedColumns() const {
            std::vector<std::string> columns;
            for (const auto& child : children) {
                if (child->type == TokenType::IDENTIFIER) {
                    columns.push_back(child->value);
                }
            }
            return columns;
        }

        // Obtener el nombre de la tabla de la consulta SELECT
        std::string getTableName() const {
            for (const auto& child : children) {
                if (child->type == TokenType::IDENTIFIER) {
                    return child->value;  // Asumimos que el primer identificador después de FROM es el nombre de la tabla
                }
            }
            return "";
        }
    };

    // Clase modificada SQLParser con la función para analizar la consulta
    class CrescendoParser {
    public:
        CrescendoParser(const std::string& query);
        std::vector<Token> tokenize();
        ASTNode* parse(); // Nueva función para analizar la consulta

    private:
        std::string query_;
        size_t current_pos_;
        std::vector<Token> tokens_;
        size_t current_token_index_;

        // Métodos de ayuda
        char peek() const;
        char get();
        void skipWhitespace();
        Token extractToken();
        bool isKeyword(const std::string& word) const;

        // Funciones de parsing
        Token nextToken();
        Token peekToken() const;
        ASTNode* parseSelect(); // Función específica para consultas SELECT

        // Agrega las nuevas funciones de análisis para CREATE DATABASE, CREATE TABLE, INSERT INTO
        ASTNode* parseCreateDatabase();
        ASTNode* parseCreateTable();
        ASTNode* parseInsert();
    };    

} // namespace Crescendo

#endif // CRESCENDO_PARSER_H
