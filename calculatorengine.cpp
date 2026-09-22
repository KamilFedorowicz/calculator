#include "calculatorengine.h"

void CalculatorEngine::appendNumber(const QString& num)
{
    displayText += num;
}

void CalculatorEngine::backspace()
{
    if (!displayText.isEmpty())
    {
        displayText.chop(1);
    }
}

void CalculatorEngine::clear()
{
    displayText.clear();
}

QString CalculatorEngine::getDisplayText() const
{
    return displayText;
}
