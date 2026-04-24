#include "../include/lib/parser.hpp"

namespace task {

    parser::parser(std::deque<std::string>* tokens) {
        this->tokens = tokens;
        this->next_token();
    }

    bool parser::is_operand(const std::string& str) {
        for (int i = 'A'; i <= 'Z'; i++) {
            if (str == std::string(1, i)) {
                return true;
            }
        }

        return false;
    }

    void parser::next_token() {
        if (tokens->size() == 0) {
            this->current_token = "";
            return;
        }
        
        this->current_token = this->tokens->front();
        this->tokens->pop_front();
    }

    void parser::expect(const std::string& str) {
        if (this->current_token != str) {
            throw std::runtime_error("'" + str + "'" + " expected");
        }
    }

    task::ITree* parser::parse_expr() {
        task::ITree* node = parse_term();

        while (current_token == "OR") {
            next_token();

            task::ITree* right = parse_term();

            task::ITree* new_node = new task::operator_tree("OR", false);

            new_node->left = node;
            new_node->right = right;

            node = new_node;
        }

        return node;
    }

    task::ITree* parser::parse_term() {
        task::ITree* node = parse_factor();

        while (current_token == "AND") {
            next_token();

            task::ITree* right = parse_factor();

            task::ITree* new_node = new task::operator_tree("AND", false);

            new_node->left = node;
            new_node->right = right;

            node = new_node;
        }

        return node;
    }

    task::ITree* parser::parse_factor() {
        task::ITree* node = nullptr;

        if (current_token == "NOT") {
            this->next_token();

            task::ITree* right = this->parse_factor();

            if (right == nullptr) {
                
            }

            node = new task::operator_tree("NOT", true);

            node->right = right;

            return node;
        }
        else if (current_token == "(") {
            this->next_token();

            node = parse_expr();

            expect(")");

            this->next_token();

            return node;
        }

        if (!this->is_operand(this->current_token)) {
            throw std::runtime_error("Unexpected token: " + this->current_token);
        }

        std::string operand = this->current_token;
        this->values[operand] = 1;
        next_token();

        return new task::operand_tree(operand);
    }

}