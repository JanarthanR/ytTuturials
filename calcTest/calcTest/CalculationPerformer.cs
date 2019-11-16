using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace calcTest
{
    class CalculationPerformer
    {

        private static int precedence(char op)
        {
            if (op == '+' || op == '-')
            {
                return 1;
            }
            if (op == '*' || op == '/')
            {
                return 2;
            }
            return 0;
        }

        // Function to perform arithmetic operations. 
        private static int applyOp(int a, int b, char op)
        {
            if (op == '+')
            {
                return a + b;
            }
            else if (op == '-')
            {
                return a - b;
            }
            else if (op == '*')
            {
                return a * b;
            }
            else if (op == '/') {
                return a / b;
            }
            return 0;
        }

        private static bool isOperation(string val)
        {
            return val == "*" || val == "/" || val == "+" || val == "-";
        }

        private static int priority(string val) {
            if (val == "/")
            {
                return 3;
            }
            else if (val == "*") {
                return 2;
            }
            return 1;
        }

        private static string performCalc(string val1, string val2, string opp) {

            if (opp == "/")
            {
                return (Convert.ToDouble(val1) / Convert.ToDouble(val2)).ToString();
            }
            else if (opp == "*")
            {
                return (Convert.ToDouble(val1) * Convert.ToDouble(val2)).ToString();
            }
            else if (opp == "-")
            {
                return (Convert.ToDouble(val1) - Convert.ToDouble(val2)).ToString();
            }
            return (Convert.ToDouble(val1) + Convert.ToDouble(val2)).ToString();
        }

        public static double calculator(List<string> expression)
        {
            Stack<string> values = new Stack<string>();

            Stack<string> operations = new Stack<string>();

            for (int iter = 0; iter < expression.Count; iter++)
            {

                if (isOperation(expression[iter]))
                {
                    if (operations.Count == 0) {
                        operations.Push(expression[iter]);
                    }
                    else if (priority(expression[iter]) > priority(operations.Peek()))
                    {
                        operations.Push(expression[iter]);
                    }
                    else
                    {

                        while (values.Count != 1 && operations.Count != 0 && priority(operations.Peek()) > priority(expression[iter]))
                        {
                            string val1 = values.Peek();
                            values.Pop();
                            string val2 = values.Peek();
                            values.Pop();
                            values.Push(performCalc(val1, val2, operations.Peek()));
                            operations.Pop();
                        }

                        operations.Push(expression[iter]);
                    }
                }
                else
                {
                    values.Push(expression[iter]);
                }
            }

            while (values.Count > 1) {
                string val1 = values.Peek();
                values.Pop();
                string val2 = values.Peek();
                values.Pop();
                values.Push(performCalc(val2, val1, operations.Peek()));
                operations.Pop();
            }

            return Convert.ToDouble(values.Peek());
        }

        // Function that returns value of 
        // expression after evaluation. 
        public static double performCalculation(string tokens) {

            List<string> operations = new List<string>();

            string currString = "";

            for (int iter = 0; iter < tokens.Length; iter++)
            {

                if (tokens[iter] == ' ')
                {
                    continue;
                }
                else if (tokens[iter] == '/' || tokens[iter] == '*' || tokens[iter] == '-' || tokens[iter] == '+' || tokens[iter] == '(' || tokens[iter] == ')')
                {
                    if (currString.Length > 0)
                    {
                        operations.Add(currString);
                    }
                    operations.Add(tokens[iter] + "");
                    currString = "";
                }
                else
                {
                    currString += tokens[iter];
                }
            }

            if (currString.Length > 0)
            {
                operations.Add(currString);
            }

            return calculator(operations);
        }

        private static double calculatorWithBrackets(List<string> expression)
        {

            Stack<string> tokens = new Stack<string>();

            for (int iter = 0; iter < expression.Count; iter++)
            {
                if (expression[iter] == ")")
                {
                    string currExp = "";
                    while (tokens.Peek() != "(")
                    {
                        currExp = tokens.Peek() + currExp;
                        tokens.Pop();
                    }
                    tokens.Pop();
                    if (currExp.Length > 0)
                    {
                        tokens.Push(performCalculation(currExp).ToString());
                    }
                }
                else
                {
                    tokens.Push(expression[iter]);
                }
            }

            string finalExp = "";

            while (tokens.Count > 0) {
                if (tokens.Peek() != "(")
                {
                    finalExp = tokens.Peek() + finalExp;
                }
                else {
                    tokens.Pop();
                    break;
                }
                
                tokens.Pop();
            }


            return performCalculation(finalExp);
        }

        public static double calculate(string tokens)
        {
            List<string> operations = new List<string>();

            string currString = "";

            for (int iter = 0; iter < tokens.Length; iter++)
            {

                if (tokens[iter] == ' ')
                {
                    continue;
                }
                else if (tokens[iter] == '/' || tokens[iter] == '*' || tokens[iter] == '-' || tokens[iter] == '+' || tokens[iter] == '(' || tokens[iter] == ')')
                {
                    if (currString.Length > 0)
                    {
                        operations.Add(currString);
                    }
                    operations.Add(tokens[iter] + "");
                    currString = "";
                }
                else
                {
                    currString += tokens[iter];
                }
            }

            if (currString.Length > 0)
            {
                operations.Add(currString);
            }
            

            return calculatorWithBrackets(operations);
        }

    }
}
