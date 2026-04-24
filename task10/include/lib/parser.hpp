#include "./tree.hpp"
#include <stdexcept>
#include <map>
#include <deque>

#ifndef TASK10_PARSER_HPP

#define TASK10_PARSER_HPP

namespace task {

    struct parser {
        std::string current_token = "";
        std::deque<std::string>* tokens = nullptr;

        std::map<std::string, int> values = *new std::map<std::string, int>();

        parser(std::deque<std::string>* tokens);

        bool is_operand(const std::string& str);

        void next_token();

        void expect(const std::string& str);

        task::ITree* parse_expr();

        task::ITree* parse_term();

        task::ITree* parse_factor();

    };

}

#endif