#include "./tree.hpp"
#include <stdexcept>
#include <map>

namespace task {

    struct parser {
        std::string current_token = "";
        std::deque<std::string>* tokens = nullptr;

        std::map<std::string, int> values = *new std::map<std::string, int>();

        parser(std::deque<std::string>* tokens) : tokens(tokens) {
            this->next_token();
        }

        std::string peek_token() {
            if (this->tokens->size() == 0) {
                return "";
            }

            return this->tokens->front();
        }

        bool is_operand() {
            for (int i = 'A'; i <= 'Z'; i++) {
                if (current_token == std::string(1, i)) {
                    return true;
                }
            }

            return false;
        }

        bool is_operator() {
            return current_token == "NOT" || current_token == "AND" || current_token == "OR";
        }

        void next_token() {
            if (tokens->size() == 0) {
                this->current_token = "";
                return;
            }
            
            this->current_token = this->tokens->front();
            this->tokens->pop_front();
        }

        void expect(const std::string& str) {
            this->next_token();

            if (this->current_token != str) {
                throw std::runtime_error("'" + str + "'" + " expected");
            }
        }

        task::ITree* parse_expr() {
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

        task::ITree* parse_term() {
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

        task::ITree* parse_factor() {
            task::ITree* node = nullptr;

            if (current_token == "NOT") {
                this->next_token();

                task::ITree* left = this->parse_factor();

                node = new task::operator_tree("NOT", true);

                node->left = new task::operand_tree(this->current_token);
                node->left = left;

                return node;
            }
            else if (current_token == "(") {
                this->next_token();

                node = parse_expr();

                expect(")");

                return node;
            }

            std::string operand = this->current_token;
            this->values[operand] = 1;
            next_token();

            return new task::operand_tree(operand);
        }

    };

}