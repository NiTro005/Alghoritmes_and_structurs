// Copyright 2024 Kita Trofimov
//#ifdef CALCULATOR
//#include "../lib_calculator/expression.h"
//int main() {
//    int main() {
//        try {
//            std::string expression;
//            std::cout << "Enter the expression: ";
//            std::getline(std::cin, expression);
//
//            Expression exp(expression);
//            exp.parse(expression);
//            exp.build_polish_record();
//            std::cout << "Polish record: ";
//            for (const auto& lex : exp.polish_record) {
//                std::cout << lex->name() << " ";
//            }
//            std::cout << std::endl;
//
//            std::string var;
//            int value;
//            while (true) {
//                std::cout << "Enter variable name (or 'done' to finish): ";
//                std::cin >> var;
//                if (var == "done") {
//                    break;
//                }
//                std::cout << "Enter value for " << var << ": ";
//                std::cin >> value;
//                exp.set_vars_values(var, value);
//            }
//
//            double result = exp.calculate();
//            std::cout << "Result: " << result << std::endl;
//        }
//        catch (const std::runtime_error& e) {
//            std::cout << "Error: " << e.what() << std::endl;
//        }
//
//        return 0;
//    }
//}
//#endif // CALCULATOR

