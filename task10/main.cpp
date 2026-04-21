#include <iostream>
#include <string>
#include <vector>
#include <deque>

#include "./include/lib/parser.hpp"

#include "./include/lib/tree.hpp"

#define WORD_COUNT 3

std::string words[WORD_COUNT] = {
    "AND",
    "OR",
    "NOT"
};

bool valid_word(const std::string& word) {
    for (int i = 0; i < WORD_COUNT; i++) {
        if (words[i].compare(word) == 0) {
            return true;
        }
    }

    return false;
}

std::string next_lex(const std::string& str) {
    static int i = 0;
    std::string word = "";
    
    for (; i < str.size(); i++) {
        char ch = str.at(i);

        if (ch == '\n') {
            continue;
        }
        
        if (ch == '(' || ch == ')') {
            i++;
            return word + ch;
        }
        else if (ch != ' ') {
            word += ch;
            
            if (i != str.size() - 1 && (str.at(i + 1) != '(' && str.at(i + 1) != ')')) {
                continue;
            }
        }
        else if (ch == ' ' && word == "") {
            continue;
        }

        i++;

        return word;
    }

    return "";
}

bool is_operand(const std::string& str) {
    for (int i = 'A'; i <= 'Z'; i++) {
        if (str == std::string(1, i)) {
            return true;
        }
    }

    return false;
}

std::deque<std::string>* break_to_lex(const std::string& str) {
    std::deque<std::string>* lexems = new std::deque<std::string>();

    std::string lex = "";
    while ((lex = next_lex(str)) != "") {
        lexems->push_back(lex);
    }

    return lexems;
}

int main(int argc, char** argv) {
    std::string input_string = "";

    std::getline(std::cin, input_string);

    std::deque<std::string>* lexems = break_to_lex(input_string);

    task::parser parser_obj(lexems);

    task::ITree* tree = parser_obj.parse_expr();

    parser_obj

    std::map<std::string, int> values = *new std::map<std::string, int>();

    tree->print();

    values["A"] = 1;
    values["B"] = 1;
    values["C"] = 0;

    std::cout << tree->calculate(values) << std::endl;
    
    return 0;
}