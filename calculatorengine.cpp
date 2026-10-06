#include "calculatorengine.h"
#include "exprtk.hpp"
#include <QDebug>

void CalculatorEngine::clearIfJustEvaluated()
{
    if(justEvaluated == true)
    {
        clear();
    }
}

void CalculatorEngine::evaluateExpression()
{
    historyExpression = currentExpression;
    double result = evaluate(currentExpression.toStdString());
    QString currentInput = QString::number(result);
    currentExpression = currentInput;
    justEvaluated = true;
    
    historyExpression += "=";
    historyExpression += currentExpression;
    
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
    
    clearIfJustEvaluated();
    
    if(currentExpression == "0")
    {
        currentExpression.chop(1);
    }
    currentExpression += num;
    justEvaluated = false;
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
    clearIfJustEvaluated();
    currentExpression += bracket;
    justEvaluated = false;
}

void CalculatorEngine::appendSign(const QString& sign)
{
    QChar lastChar = currentExpression.back();
    if(isSign(lastChar))
    {
        currentExpression.chop(1);
    }
    currentExpression += sign;
    justEvaluated = false;
}

void CalculatorEngine::appendDecimalPoint()
{
    clearIfJustEvaluated();
    
    for(QChar c: currentExpression)
    {
        if(c == ".")
        {
            return;
        }
    }
    
    currentExpression += ".";
    justEvaluated = false;
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
    justEvaluated = false;
    
}

void CalculatorEngine::clear()
{
    currentExpression.clear();
    checkIfZero();
    justEvaluated = false;
}

QString CalculatorEngine::getCurrentExpression() const
{
    return currentExpression;
}

QString CalculatorEngine::getCurrentErrorMessage()
{
    std::string expression_string = currentExpression.toStdString();
    
    typedef exprtk::expression<double> expression_t;
    typedef exprtk::parser<double> parser_t;

    expression_t expression;
    parser_t parser;

    if (!parser.compile(expression_string, expression))
    {
        errorMessage = "Invalid expression!";
    }
    else
    {
        errorMessage = "Valid expression";
    }

    return errorMessage;
}

void CalculatorEngine::setCurrentExpression(
    const QString& expression)
{
    currentExpression = expression;
}
