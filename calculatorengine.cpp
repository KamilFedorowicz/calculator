#include "calculatorengine.h"
#include "exprtk.hpp"

void CalculatorEngine::evaluateExpression()
{
    double result = evaluate(currentExpression.toStdString());
    QString currentInput = QString::number(result);
    currentExpression = currentInput;
}


double CalculatorEngine::evaluate(const std::string& expression_string)
{
    typedef exprtk::expression<double> expression_t;
    typedef exprtk::parser<double> parser_t;

    expression_t expression;
    parser_t parser;

    if (!parser.compile(expression_string, expression))
    {
        return 0.0;
        throw std::runtime_error("Invalid expression");
    }

    return expression.value();
}

void CalculatorEngine::appendNumber(const QString& num)
{
    if(currentExpression == "0")
    {
        currentExpression.chop(1);
    }
    currentExpression += num;
}

bool CalculatorEngine::isSign(const QString& sign)
{
    if(sign == "+" || sign == "-" || sign == "*" || sign == "/")
    {
        return true;
    }
    
    return false;
}

void CalculatorEngine::addBracket(const QString& bracket)
{
    currentExpression += bracket;
}

void CalculatorEngine::appendSign(const QString& sign)
{
    QChar lastChar = currentExpression.back();
    if(isSign(lastChar))
    {
        currentExpression.chop(1);
    }
    currentExpression += sign;
}

void CalculatorEngine::appendDecimalPoint()
{
    for(QChar c: currentExpression)
    {
        if(c == ".")
        {
            return;
        }
    }
    
    currentExpression += ".";
}

void CalculatorEngine::checkIfZero()
{
    if(currentExpression.isEmpty())
    {
        currentExpression += "0";
    }
}

void CalculatorEngine::backspace()
{
    if (!currentExpression.isEmpty())
    {
        currentExpression.chop(1);
    }
    
    checkIfZero();
    
}

void CalculatorEngine::clear()
{
    currentExpression.clear();
    checkIfZero();
}

QString CalculatorEngine::getCurrentExpression() const
{
    return currentExpression;
}

