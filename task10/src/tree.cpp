#include "../include/lib/tree.hpp"

namespace task {
    
    operator_tree::operator_tree(std::string type, bool is_unary) : type(type), is_unary(is_unary) {}
    
    int operator_tree::calculate(const std::map<std::string, int>& values) {
        if (type == "AND") {
            if (left == nullptr) {
                throw std::runtime_error("AND operator must have left operand");
            }
            if (right == nullptr) {
                throw std::runtime_error("AND operator must have right operand");
            }

            return left->calculate(values) && right->calculate(values);
        }
        else if (type == "OR") {
            if (left == nullptr) {
                throw std::runtime_error("OR operator must have left operand");
            }
            if (right == nullptr) {
                throw std::runtime_error("OR operator must have right operand");
            }

            return left->calculate(values) || right != nullptr && right->calculate(values);
        }
        else if (type == "NOT") {
            if (right == nullptr) {
                throw std::runtime_error("NOT operator must have right operand");
            }

            return !right->calculate(values);
        }

        return 0;
    }

    void operator_tree::print() {
        if (this->left != nullptr) {
            this->left->print();
        }

        std::cout << this->type << std::endl;

        if (this->right != nullptr) {
            this->right->print();
        }
    }

    operand_tree::operand_tree(std::string symbol) : symbol(symbol) {}

    int operand_tree::calculate(const std::map<std::string, int>& values) {
        return values.at(this->symbol);
    }

    void operand_tree::print() {
        std::cout << this->symbol << std::endl;
    }

}