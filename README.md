# Evaluation Test

## Description

The exercise required to complete the evaluate function, which takes a string and a map as inputs. The goal was to implement the evaluate function so that it could process and evaluate expressions within the provided strings.

The task can be broken down into two main steps:

- Parsing the string by analyzing each symbol.
- Calculating the expression while considering parentheses and [operator precedence](https://en.wikipedia.org/wiki/Operators_in_C_and_C%2B%2B#Operator_precedence).

### To solve this problem

The key aspect is handling operator precedence and the grouping of expressions using brackets. To address this, I used the [Shunting Yard Algorithm](https://en.wikipedia.org/wiki/Shunting_yard_algorithm), which converts infix notation (the standard mathematical notation) into [Reverse Polish Notation (RPN)](https://en.wikipedia.org/wiki/Reverse_Polish_notation), a format that makes it easier to evaluate expressions while maintaining the correct precedence and operator priorities.

Here’s an overview of how the solution works:

Tokenization: First, we break the input string into tokens (numbers, operators, and parentheses).
Conversion to RPN: Using the Shunting Yard Algorithm, we convert the infix expression to Reverse Polish Notation. This step ensures that operators are ordered correctly based on their precedence and the structure provided by parentheses.
Evaluation: Once the expression is in RPN, it's straightforward to evaluate by processing the tokens in a stack-based approach.
This method ensures that the brackets and operator precedence are properly handled during the evaluation of the expression.

### Result

All comparisons in the expressions are correctly performed, respecting the order of brackets and operator precedence. However, as the test is currently written, it does not produce the expected result where "Good job!" is printed. To achieve the correct outcome, the fifth and sixth calls to the evaluate function need to be negated using the not operator.

```
!evaluate(e5, m) &&
!evaluate(e6, m) &&
```

## Getting Started

Download and execute the code.

```
git clone https://github.com/PhilipTamb/evaluation_test.git
cd evaluation_test
clang++ --std=c++11 evaluation_test.cpp -o evaluation_test
./evaluation_test
```
