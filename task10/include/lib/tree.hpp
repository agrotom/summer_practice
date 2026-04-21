#include <map>
#include <iostream>

#ifndef TASK10_TREE_HPP

#define TASK10_TREE_HPP

namespace task {
    class ITree {
    public:
        ITree* left = nullptr;
        ITree* right = nullptr;

        virtual int calculate(const std::map<std::string, int>& values) = 0;
        virtual void print() = 0;
    };

    struct operator_tree : ITree {
        std::string type;
        bool is_unary;

        operator_tree(std::string type, bool is_unary) : type(type), is_unary(is_unary) {}
        
        int calculate(const std::map<std::string, int>& values) override {
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

                return !left->calculate(values);
            }

            return 0;
        }

        void print() override {
            if (this->left != nullptr) {
                this->left->print();
            }

            std::cout << this->type << std::endl;

            if (this->right != nullptr) {
                this->right->print();
            }
        }

    };

    struct operand_tree : ITree {
        std::string symbol;

        operand_tree(std::string symbol) : symbol(symbol) {}

        int calculate(const std::map<std::string, int>& values) override {
            return values.at(this->symbol);
        }

        void print() override {
            std::cout << this->symbol << std::endl;
        }

    };

}

#endif