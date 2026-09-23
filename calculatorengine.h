#ifndef CALCULATORENGINE_H
#define CALCULATORENGINE_H

#include <QString>

class CalculatorEngine
{
public:
    void appendNumber(const QString& num);
    void appendSign(const QString& sign);
    void appendDecimalPoint();
    void backspace();
    void clear();
    void checkIfZero();
    bool isSign(const QString& sign);
    void addBracket(const QString& bracket);

    QString getDisplayText() const;
    QString displayText{"0"};

private:
    
};

#endif
