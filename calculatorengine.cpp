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
    saveState();
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
    saveState(); // save old state before changing anything
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
    saveState();
    clearIfJustEvaluated();
    currentExpression += bracket;
    justEvaluated = false;
}

void CalculatorEngine::appendSign(const QString& sign)
{
    saveState();
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
    saveState();
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
    saveState();
    if (!currentExpression.isEmpty())
    {
        currentExpression.chop(1);
    }
    
    checkIfZero();
    justEvaluated = false;
    
}

void CalculatorEngine::clear()
{
    saveState();
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

CalculatorEngine::CalculatorState CalculatorEngine::getState() const
{
    return {
        currentExpression,
        historyExpression,
        justEvaluated
    };
}

void CalculatorEngine::saveState()
{
    undoStack.push_back(getState());
    
    redoStack.clear();
}

void CalculatorEngine::undo()
{
    if(undoStack.empty())
    {
        return;
    }
    
    redoStack.push_back(getState());
    
    restoreState(undoStack.back());
    
    undoStack.pop_back();
}

void CalculatorEngine::restoreState(const CalculatorState& state)
{
    currentExpression = state.currentExpression;
    historyExpression = state.historyExpression;
    justEvaluated  = state.justEvaluated;
}

void CalculatorEngine::redo()
{
    if (redoStack.empty())
    {
        return;
    }

    undoStack.push_back(getState());

    restoreState(redoStack.back());

    redoStack.pop_back();
}
