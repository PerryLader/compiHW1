#include "tokens.hpp"
#include <iostream>
#include <sstream>



void printToken(std::string tokenType, std::string tokenText) {
    std::cout << yylineno << " " << tokenType << " " << tokenText << std::endl;
}

void bad_HexSeq() {
    std::string tokenText(yytext);
    int textSize = tokenText.size();
    std::cout << "Error undefined escape sequence ";
    if (tokenText[textSize - 2] == 'x') {
        std::cout << tokenText[textSize - 2] << std::endl;
        return;
    }
    std::cout << "x" << tokenText[textSize - 2];
    if (tokenText[textSize - 1] != '"')
        std::cout << tokenText[textSize - 1];
    std::cout << std::endl;
}

void bad_EscapeSeq() {
    std::string tokenText(yytext);
    char lastChar = tokenText[tokenText.size() - 1];
    std::cout << "Error undefined escape sequence " << lastChar << std::endl;
    exit(0);
}

void stringToken() {
    std::string tokenText(yytext);
    std::stringstream formattedOutput;

    formattedOutput << yylineno << " STRING ";

    for (size_t i = 0; i < tokenText.size(); ++i) {
        char currentChar = tokenText[i];

        if (currentChar == '"') {
            continue;
        }

        if (currentChar == '\\') {
            char nextChar = tokenText[i + 1];

            if (nextChar == 'x') {
                int hexValue = std::stoi(tokenText.substr(i + 2, 2), nullptr, 16);
                formattedOutput << static_cast<char>(hexValue);
                i += 3;
            } else if (nextChar == 'n') {
                formattedOutput << '\n';
                ++i;
            } else if (nextChar == 'r') {
                formattedOutput << '\r';
                ++i;
            } else if (nextChar == 't') {
                formattedOutput << '\t';
                ++i;
            } else if (nextChar == '\"') {
                formattedOutput << '\"';
                ++i;
            } else if (nextChar == '\\') {
                formattedOutput << '\\';
                ++i;
            }
        } else {
            formattedOutput << currentChar;
        }
    }

    std::cout << formattedOutput.str() << std::endl;
}

int main() {
    int token;
    while ((token = yylex())) {
        switch (token) {
        case INT:
            printToken("INT", yytext);
            break;
        case BYTE:
            printToken("BYTE", yytext);
            break;
        case B:
            printToken("B", yytext);
            break;
        case BOOL:
            printToken("BOOL", yytext);
            break;
        case AND:
            printToken("AND", yytext);
            break;
        case OR:
            printToken("OR", yytext);
            break;
        case NOT:
            printToken("NOT", yytext);
            break;
        case TRUE:
            printToken("TRUE", yytext);
            break;
        case FALSE:
            printToken("FALSE", yytext);
            break;
        case RETURN:
            printToken("RETURN", yytext);
            break;
        case IF:
            printToken("IF", yytext);
            break;
        case ELSE:
            printToken("ELSE", yytext);
            break;
        case WHILE:
            printToken("WHILE", yytext);
            break;
        case BREAK:
            printToken("BREAK", yytext);
            break;
        case CONTINUE:
            printToken("CONTINUE", yytext);
            break;
        case SC:
            printToken("SC", yytext);
            break;
        case LPAREN:
            printToken("LPAREN", yytext);
            break;
        case RPAREN:
            printToken("RPAREN", yytext);
            break;
        case LBRACE:
            printToken("LBRACE", yytext);
            break;
        case RBRACE:
            printToken("RBRACE", yytext);
            break;
        case ASSIGN:
            printToken("ASSIGN", yytext);
            break;
        case RELOP:
            printToken("RELOP", yytext);
            break;
        case COMMENT:
            std::cout << yylineno << " COMMENT //" << std::endl;
            break;
        case BINOP:
            printToken("BINOP", yytext);
            break;
        case ID:
            printToken("ID", yytext);
            break;
        case NUM:
            printToken("NUM", yytext);
            break;
        case STRING:
            stringToken();
            break;
        case UNCLOSED_STR:
            std::cout << "Error unclosed string" << std::endl;
            exit(0);
            break;
        case INV_HEX:
            bad_HexSeq();
            exit(0);
		case INV_ESC:
            bad_EscapeSeq();
            exit(0);
            break;
        case ERROR:
            std::cout << "Error " << yytext << std::endl;
            exit(0);
        default:
            std::cout << "Error " << yytext << std::endl;
            exit(0);
    }
    }
    return 0;
}