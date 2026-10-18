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
    
    struct CalculatorState
    {
        QString currentExpression;
        QString historyExpression;
        bool justEvaluated = false;
    };
    
    // we dont need stach because push_back and pop_back acts as a stack
    std::vector<CalculatorState> undoStack;
    std::vector<CalculatorState> redoStack;
    
    CalculatorState getState() const;
    void saveState();
    void undo();
    void redo();
    void restoreState(const CalculatorState& state);

private:
    bool justEvaluated{false}; // keeps track whether the last button that was clicked was '=' (evaluate)

};

#endif
