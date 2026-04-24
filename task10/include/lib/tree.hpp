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

        operator_tree(std::string type, bool is_unary);
        
        int calculate(const std::map<std::string, int>& values) override;

        void print() override;

    };

    struct operand_tree : ITree {
        std::string symbol;

        operand_tree(std::string symbol);

        int calculate(const std::map<std::string, int>& values) override;

        void print() override;

    };

}

#endif