#include <iostream>
#include "calculator.hpp"
int main() {
  std::string input;
  std::cout << "Enter an expression to calculate: ";
  std::getline(std::cin, input);

  try {
    int result = CalculateExpression(input);
    std::cout << "Result: " << result << std::endl;
  } catch (const WrongExpressionError& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  } catch (const std::exception& e) {
    std::cerr << "Unexpected error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}