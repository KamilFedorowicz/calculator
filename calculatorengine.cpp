#include "calculatorengine.h"

void CalculatorEngine::appendNumber(const QString& num)
{
    if(displayText == "0")
    {
        displayText.chop(1);
    }
    displayText += num;
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
    displayText += bracket;
}

void CalculatorEngine::appendSign(const QString& sign)
{
    QChar lastChar = displayText.back();
    if(isSign(lastChar))
    {
        displayText.chop(1);
    }
    displayText += sign;
}

void CalculatorEngine::appendDecimalPoint()
{
    for(QChar c: displayText)
    {
        if(c == ".")
        {
            return;
        }
    }
    
    displayText += ".";
}

void CalculatorEngine::checkIfZero()
{
    if(displayText.isEmpty())
    {
        displayText += "0";
    }
}

void CalculatorEngine::backspace()
{
    if (!displayText.isEmpty())
    {
        displayText.chop(1);
    }
    
    checkIfZero();
    
}

void CalculatorEngine::clear()
{
    displayText.clear();
    checkIfZero();
}

QString CalculatorEngine::getDisplayText() const
{
    return displayText;
}

