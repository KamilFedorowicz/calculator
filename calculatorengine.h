#ifndef CALCULATORENGINE_H
#define CALCULATORENGINE_H

#include <QString>

class CalculatorEngine
{
public:
    void appendNumber(const QString& num);
    void backspace();
    void clear();

    QString getDisplayText() const;
    QString displayText;

private:
    
};

#endif
