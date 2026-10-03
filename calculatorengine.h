#ifndef CALCULATORENGINE_H
#define CALCULATORENGINE_H

#include <QString>

class CalculatorEngine
{
public:
    void appendNumber(const QString& num);
    void appendSign(const QString& sign);
    void appendDecimalPoint();
    void evaluateExpression();
    void backspace();
    void clear();
    void checkIfZero();
    bool isSign(const QString& sign);
    void addBracket(const QString& bracket);
    double evaluate(const std::string& expression_string);
    void clearIfJustEvaluated();

    QString getCurrentExpression() const;
    QString getCurrentErrorMessage();
    QString currentExpression{"0"};
    QString errorMessage{"Correct expression"};
    QString historyExpression;
    void setCurrentExpression(const QString& expression);

private:
    bool justEvaluated{false}; // keeps track whether the last button that was clicked was '=' (evaluate)

};

#endif
