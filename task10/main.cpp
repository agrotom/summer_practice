#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <stdexcept>

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

void print_table(task::ITree* tree, const std::vector<std::string>& vars, std::map<std::string, int>& cur_values, int depth) {
    if (depth == 0) {
        for (int i = 0; i < vars.size(); i++) {
            std::cout << cur_values.at(vars.at(i)) << " ";
        }

        std::cout << tree->calculate(cur_values) << std::endl;

        return;
    }

    for (int i = 0; i <= 1; i++) {
        cur_values.at(vars.at(vars.size() - depth)) = i;
        print_table(tree, vars, cur_values, depth - 1);
    }
    
}

void delete_tree(task::ITree* tree) {
    if (tree == nullptr) {
        return;
    }

    delete_tree(tree->left);
    delete_tree(tree->right);

    delete tree;
}

int main(int argc, char** argv) {
    std::string input_string = "";

    std::getline(std::cin, input_string);

    std::deque<std::string>* lexems = break_to_lex(input_string);

    task::parser parser_obj(lexems);

    task::ITree* tree = nullptr;

    try {
        tree = parser_obj.parse_expr();
    } catch (const std::runtime_error& e) {
        return 1;
    }

    if (parser_obj.current_token != "") {
        return 1;
    }
 
    std::vector<std::string> vars = *new std::vector<std::string>();
    std::map<std::string, int> values = *new std::map<std::string, int>();

    for (auto const& [key, value] : parser_obj.values) {
        std::cout << key << " ";
        vars.push_back(key);
        values[key] = 0;
    }

    std::cout << "Result" << std::endl;

    try {
        print_table(tree, vars, values, vars.size());
    } catch (const std::runtime_error& e) {
        return 1;
    }

    delete lexems;
    delete_tree(tree);
    
    return 0;
}