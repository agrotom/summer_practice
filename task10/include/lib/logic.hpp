namespace task {

    struct operand {
        char symbol;

        operand(char symbol) : symbol(symbol) {}
    };

    struct operator_t {

        bool is_unary;
        std::string type;
        
        operator_t(bool is_unary, std::string type) : is_unary(is_unary), type(type) {}

    };

}