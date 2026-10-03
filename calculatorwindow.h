#ifndef CALCULATORWINDOW_H
#define CALCULATORWINDOW_H

#include <QWidget>
#include "calculatorengine.h"
#include <QKeyEvent>
#include <QListWidget>

class QGridLayout;
class QLineEdit;
class QPushButton;


class CalculatorWindow : public QWidget
{
public:
    explicit CalculatorWindow(QWidget *parent = nullptr);
    
private:
    CalculatorEngine engine;
    
    QLineEdit* display;
    QLineEdit* displayError;
    QGridLayout *layout;
    
    QPushButton *btn0;
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;
    QPushButton *btn4;
    QPushButton *btn5;
    QPushButton *btn6;
    QPushButton *btn7;
    QPushButton *btn8;
    QPushButton *btn9;
    
    QPushButton *btnAdd;
    QPushButton *btnSub;
    QPushButton *btnMul;
    QPushButton *btnDiv;
    QPushButton *btnEq;
    
    QPushButton *btnDot;
    QPushButton *btnDelete;
    QPushButton *btnClear;
    QPushButton *btnLeftBracket;
    QPushButton *btnRightBracket;
    
    void createWidgets();
    void createLayout();
    void connectButtons();
    void refreshDisplay();
    void setButtonsStyle();
    void refreshHistory();
    void clearHistory();
    
    QPushButton *createButton(
    const QString &text,
    int height = 80
    );
    
    QList<QPushButton *> numberButtons;
    QList<QPushButton *> signButtons;
    QList<QPushButton *> otherButtons;
    
    QListWidget* historyList;
    
protected:
    void keyPressEvent(QKeyEvent* event) override;
    
    /*
     imagine the class
     class QWidget
     {
     public:
         virtual void keyPressEvent(QKeyEvent* event);
     };
     
     CalculatorWindow ingerits from QWidget and provides own implementation of keyPressEvent
     
     */
    
    
    
};

#endif
