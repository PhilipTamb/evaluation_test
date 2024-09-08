#include <sstream>
#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <deque>
#include <stack>
#include <queue>
#include <stdexcept>
#include <string>
#include <iomanip>
#include <cstdlib>

std::vector<std::string> symbols = {"(", ")", "!", "<", "<=", ">", ">=", "==", "!=", "&&", "||"};

void print_queue(std::queue<std::string> q)
{
    while (!q.empty())
    {
        q.pop();
    }
    std::cout << std::endl;
}

void print_stack(std::stack<std::string> s)
{
    while (!s.empty())
    {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << std::endl;
}

int operator_precedance(const std::string &opt)
{
    if (opt == "!") // higher priority operator
    {
        return 6;
    }
    else if (opt == "<" || opt == "<=" || opt == ">" || opt == ">=")
    {
        return 5;
    }
    else if (opt == "==" || opt == "!=")
    {
        return 4;
    }
    else if (opt == "&&")
    {
        return 3;
    }
    else if (opt == "||")
    {
        return 2;
    }
    else if (opt == "(") // lower priority operator
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bool is_operator(const std::string &str)
{
    if (str == "!" || str == "<" || str == "<=" || str == ">" || str == ">=" || str == "==" || str == "!=" || str == "&&" || str == "||" || str == "(" || str == ")")
        return true;
    else
        return false;
}
std::queue<std::string> shunting_yard(const std::vector<std::string> tokens)
{
    std::stack<std::string> oper;   //  operators stack
    std::queue<std::string> output; //  output queue

    for (std::string token : tokens)
    {
        if (!token.empty() && is_operator(token))
        { // If it is an open  bracket push it into the operators stack

            if (token == "(")
            {
                oper.push(token);
            }
            else if (!oper.empty() && operator_precedance(token) < operator_precedance(oper.top()) && operator_precedance(token) > 0)
            { // If the operator over evaluation has a higher priority than the operator previously inserted in the operators stack, then I can add the current operator below to the queue, since it has a higher priority than the previous one.

                while (!oper.empty() && operator_precedance(token) < operator_precedance(oper.top()))
                {
                    // Inserting the operators from operator stack to output queue until the token priority of token <= to the operator stack.
                    output.push(oper.top());
                    oper.pop();
                }
                if (oper.empty() || !oper.empty() && operator_precedance(token) >= operator_precedance(oper.top()))
                { // if token priority <= to operator.top() or operator.top() is empty, then put the token in the operator stack
                    oper.push(token);
                }
            }
            else if (oper.empty() || !oper.empty() && operator_precedance(token) >= operator_precedance(oper.top()))
            {
                oper.push(token);
            }
            else if (token == ")")
            {
                while (!oper.empty() && oper.top() != "(")
                {
                    output.push(oper.top());
                    oper.pop();
                }
                if (oper.empty())
                {
                    std::cout << "Error parenthesis" << std::endl;
                    throw std::domain_error("Error parenthesis during parsing.");
                }

                if (!oper.empty() && oper.top() == "(") // delete open parethesis
                {
                    oper.pop();
                }
            }
        }
        else if (token == "true" || token == "false")
        {
            output.push(token);
        }
        else if (!token.empty())
        {
            std::string digit;
            for (int i = 0; i < token.size(); i++)
            {

                if (isdigit(token[i]))
                {
                    digit += token[i];
                }
                else if (token[i] == '.')
                {
                    digit += token[i];
                }
                else if (token[i] == '-')
                {
                    digit += token[i];
                }
                else if (token[i] == ' ' || std::isspace(token[i]) || token[i] == '\0')
                {
                    continue;
                }
            }
            if (!digit.empty())
            {
                output.push(digit);
            }
        }
    }

    while (!oper.empty()) // if there are operators on the stack they are pushed into the output queue
    {
        // std::cout << oper.top() << " ";
        if (oper.top() == "(" || oper.top() == ")")
        { // if it is a round bracket, delete it from the operators stack
            oper.pop();
        }
        else
        {
            output.push(oper.top());
            oper.pop();
        }
    }
    return output;
}

// parse function
std::vector<std::string> parse(const std::string &s, const std::map<std::string, std::string> &map)
{
    std::stack<std::string> operation;
    std::queue<std::string> output;
    std::stringstream ss(s);
    // Variable to hold each word
    std::string word;
    // Vector to store the words
    std::vector<std::string> words;

    std::cout << std::endl;
    std::cout << "Input String : " << s;
    std::cout << std::endl;

    while (std::getline(ss, word, ' '))
    {
        std::vector<char> char_word(word.begin(), word.end());
        if (word == "==" || word == "||" || word == "&&" || word == "!" || word == ">" || word == "<" || word == "<=" || word == ">=" || word == "!")
        {
            words.push_back(word);
        }
        else if (word == "true" || word == "false")
        {
            words.push_back(word);
        }
        else
        {
            for (int i = 0; i < char_word.size(); i++)
            {
                if (char_word[i] == '(' || char_word[i] == ')')
                {
                    std::string str;
                    str.push_back(char_word[i]);
                    words.push_back(str);
                }
                else if (char_word[i] == '!')
                {
                    std::string str;
                    str.push_back(char_word[i]);
                    words.push_back(str);
                }
                else if (char_word[i] == 'v' && isdigit(char_word[i + 1]))
                { // looking for "v0", "v1", "v2"... pattern
                    std::string str;
                    str.push_back(char_word[i]);
                    str.push_back(char_word[i + 1]);
                    str = map.at(str);
                    words.push_back(str);
                    i++; // Evaluated char_word[i] and char_word[i+1],  the next character must be char_word[i+2] then i++
                }

                else if (isdigit(char_word[i])) // get number
                {
                    std::string digit;
                    for (int i = 0; i < char_word.size(); i++)
                    {
                        if (isdigit(char_word[i]))
                        {
                            digit += char_word[i];
                        }
                        else if (char_word[i] == '.')
                        {
                            digit += char_word[i];
                        }
                        else if (char_word[i] == '-')
                        {
                            digit += char_word[i];
                        }
                        else if (char_word[i] == ' ')
                        {
                            continue;
                        }
                    }

                    if (i < char_word.size() && !isdigit(char_word[i + 1]) && char_word[i + 1] != '.') // check if next char is not digit, and it is not a poi if it is verified end digits accumulation
                    {
                        words.push_back(digit);
                    }
                }
            }
        }
    }

    // std::cout << std::endl;
    // std::cout << " words :";
    // for (std::string w : words)
    // {
    //     std::cout << "  " << w << ",    ";
    // }
    // std::cout << std::endl;
    return words;
}

float convert_string(std::string str)
{
    int precision = 0;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == '.')
        {
            precision = str.size() - (i + 1);
        }
    }

    float res = std::atof(str.c_str()); // use c_str() in order to get const char* access to the data of a std::string
    float result = std::stod(str);
    std::cout << std::fixed << std::setprecision(precision); // set the precision

    return result;
}

bool calculate(float op1, float op2, std::string oper)
{
    if (!oper.compare("<"))
    {
        return op1 < op2;
    }
    else if (!oper.compare("<="))
    {
        return op1 <= op2;
    }
    else if (!oper.compare(">"))
    {
        return op1 > op2;
    }
    else if (!oper.compare(">="))
    {
        return op1 >= op2;
    }
    else if (!oper.compare("=="))
    {
        return op1 == op2;
    }
    else if (!oper.compare("!="))
    {
        return op1 != op2;
    }
    else if (!oper.compare("&&"))
    {
        return op1 && op2;
    }
    else if (!oper.compare("||"))
    {
        return op1 || op2;
    }
    else
    {
        throw std::domain_error("Unknown operator: '" + oper + "'.");
    }
}

bool evaluate(std::string &s, std::map<std::string, std::string> &map)
{
    std::vector<std::string> words = parse(s, map);
    std::stack<std::string> solve_stack;
    std::queue<std::string> output = shunting_yard(words);
    // std::cout << "print queue: " << std::endl;
    // print_queue(output);
    float op1;
    float op2;

    while (!output.empty())
    {
        if (!is_operator(output.front())) //  if it's number put it into solve_stack
        {
            solve_stack.push(output.front());
            output.pop();
        }
        else if (is_operator(output.front()) && output.front() != "!") // if it's operator execute the operation
        {
            std::string oper = output.front(); // get operator
            output.pop();

            if (!solve_stack.empty())
            { // get operand2
                if (solve_stack.top() == "true")
                {

                    op2 = 1;
                }
                else if (solve_stack.top() == "false")
                {
                    op2 = 0;
                }
                else
                {
                    op2 = convert_string(solve_stack.top());
                }
                solve_stack.pop();
            }

            if (!solve_stack.empty())
            { // get operand1

                if (solve_stack.top() == "true")
                {
                    op1 = 1;
                }
                else if (solve_stack.top() == "false")
                {
                    op1 = 0;
                }
                else
                {
                    op1 = convert_string(solve_stack.top());
                }
                solve_stack.pop();
            }

            if (is_operator(oper) && typeid(op1) == typeid(float) && typeid(op2) == typeid(float))
            {
                bool result = calculate(op1, op2, oper);
                result = result;

                if (result)
                {
                    solve_stack.push("true");
                }
                else
                {
                    solve_stack.push("false");
                }
                std::cout << " " << op1 << " " << oper << " " << op2 << "  result: " << solve_stack.top() << "   " << std::endl;
            }
            else
            {
                throw std::domain_error("Invalid operands.");
            }
        }
        else if (is_operator(output.front()) && output.front() == "!") // not operation require only one operand
        {
            std::cout << " " << output.front() << "" << solve_stack.top();

            if (!solve_stack.empty())
            {
                if (solve_stack.top() == "true")
                {
                    solve_stack.pop();
                    solve_stack.push("false");
                }
                else if (solve_stack.top() == "false")
                {
                    solve_stack.pop();
                    solve_stack.push("true");
                }
                std::cout << "  result: " << solve_stack.top() << std::endl;
                output.pop();
            }
        }
        std::cout << std::fixed << std::setprecision(0);
    } // end while loop

    if (solve_stack.top() == "true")
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main(int argc, char **argv)
{
    std::map<std::string, std::string> m;
    std::string e1 = "v0 == 1";
    std::string e2 = "(v0 == 2 || v1 > 10)";
    std::string e3 = "(v0 == 2 || (v1 > 10 && v2 > 3)) && v3 == 0";
    std::string e4 = "(v0 == 2 || (v1 > 10 && v2 > 3)) && v3 == -15.000000001 && !v4";
    std::string e5 = "(v0 == 2 || (v1 > 10 && v2 > 3)) && v3 == -15.000000001 && v4";
    std::string e6 = "((v0 == 2 || (v1 > 10 && v2 > 3)) && v3 == -15.000000001 && v4) && (v5 == !v4) ";
    std::string e7 = "true";

    m["v0"] = "1";
    m["v1"] = "15.55";
    m["v2"] = "- 10 ";
    m["v3"] = "- 15.000000001 ";
    m["v4"] = "true";
    m["v5"] = "false";
    bool testCorrect =
        (evaluate(e1, m) &&
         evaluate(e2, m) &&
         !evaluate(e3, m) &&
         !evaluate(e4, m) &&
         evaluate(e5, m) &&
         evaluate(e6, m) &&
         evaluate(e7, m));
    std::cout << (testCorrect ? "Good job!" : "Uhm, please retry!") << std::endl;
}

/*
affinchè si possa osservare "Good job!" bisogna negare:
evaluate(e5, m) &&
evaluate(e6, m) &&
poichè entrambe queste equazioni risultano "false"
*/