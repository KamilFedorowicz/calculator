#include "calculatorwindow.h"

#include <QFont>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSizePolicy>

CalculatorWindow::CalculatorWindow(QWidget *parent): QWidget(parent)
{
    setWindowTitle("Calculator");
    setFixedSize(400, 600);
    
    createWidgets();
    createLayout();
    connectButtons();
    refreshDisplay();
}

QPushButton *CalculatorWindow::createButton(const QString& test, int height)
{
    QPushButton* button = new QPushButton(test, this);
    button->setFixedHeight(height);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    
    return button;
}

void CalculatorWindow::createWidgets()
{
    display = new QLineEdit(this);
    display->setReadOnly(true);
    display->setFixedHeight(100);
    display->setAlignment(Qt::AlignRight);
        
    QFont displayFont = display->font();
    displayFont.setPointSize(28);
    display->setFont(displayFont);
    
    displayError = new QLineEdit(this);
    displayError->setReadOnly(true);
    displayError->setFixedHeight(40);
    displayError->setAlignment(Qt::AlignRight);
    
    QFont displayErrorFont = displayError->font();
    displayErrorFont.setPointSize(14);
    displayError->setFont(displayErrorFont);
        
    btn0 = createButton("0");
    btn1 = createButton("1");
    btn2 = createButton("2");
    btn3 = createButton("3");
    btn4 = createButton("4");
    btn5 = createButton("5");
    btn6 = createButton("6");
    btn7 = createButton("7");
    btn8 = createButton("8");
    btn9 = createButton("9");
        
    btnAdd = createButton("+");
    btnSub = createButton("-");
    btnMul = createButton("*");
    btnDiv = createButton("/");
    btnEq = createButton("=");
        
    btnDot = createButton(".");
    btnDelete = createButton("DEL");
    btnClear = createButton("C");
    btnLeftBracket = createButton("(");
    btnRightBracket = createButton(")");
}

void CalculatorWindow::createLayout()
{
    layout = new QGridLayout(this);
        
    layout->addWidget(display, 0, 0, 1, 4);
    layout->addWidget(displayError, 1, 0, 1, 4);
        
    layout->addWidget(btnLeftBracket, 2, 0);
    layout->addWidget(btnRightBracket, 2, 1);
    layout->addWidget(btnClear, 2, 2);
    layout->addWidget(btnDiv, 2, 3);
        
    layout->addWidget(btn7, 3, 0);
    layout->addWidget(btn8, 3, 1);
    layout->addWidget(btn9, 3, 2);
    layout->addWidget(btnMul, 3, 3);
        
    layout->addWidget(btn4, 4, 0);
    layout->addWidget(btn5, 4, 1);
    layout->addWidget(btn6, 4, 2);
    layout->addWidget(btnSub, 4, 3);
        
    layout->addWidget(btn1, 5, 0);
    layout->addWidget(btn2, 5, 1);
    layout->addWidget(btn3, 5, 2);
    layout->addWidget(btnAdd, 5, 3);
        
    layout->addWidget(btnDelete, 6, 0);
    layout->addWidget(btn0, 6, 1);
    layout->addWidget(btnDot, 6, 2);
    layout->addWidget(btnEq, 6, 3);
        
    layout->setSpacing(6);
    layout->setContentsMargins(10, 10, 10, 10);
        
    for (int column = 0; column < 4; ++column)
    {
        layout->setColumnStretch(column, 1);
    }
}

void CalculatorWindow::connectButtons()
{
    const QList<QPushButton *> numberButtons = {
        btn0,
        btn1,
        btn2,
        btn3,
        btn4,
        btn5,
        btn6,
        btn7,
        btn8,
        btn9
    };
    
    for (QPushButton *button : numberButtons)
    {
        // when the button is clicked, execute this piece of...
        // 3rd argument receiver is the object that owns the connection. 'this' is the pointer to the current CalculatorWindow object
        // 4th argument is the action to execute.
        connect(button, &QPushButton::clicked, this, [this, button]()
        {
            engine.appendNumber(button->text());
            refreshDisplay();
        }
        );
    }
    
    const QList<QPushButton *> operatorButtons = {
        btnAdd,
        btnSub,
        btnMul,
        btnDiv
    };
    
    for (QPushButton *button : operatorButtons)
    {
        connect(button, &QPushButton::clicked, this, [this, button]()
        {
            engine.appendSign(button->text());
            refreshDisplay();
        }
        );
    }
    
    connect(btnDot, &QPushButton::clicked, this, [this]()
            {
            engine.appendDecimalPoint();
            refreshDisplay();
            }
            );
    
    connect(btnDelete, &QPushButton::clicked, this, [this]()
    {
        engine.backspace();
        refreshDisplay();
    }
    );
    
    connect(btnClear, &QPushButton::clicked, this, [this]()
    {
        engine.clear();
        refreshDisplay();
    }
    );
    
    connect(btnLeftBracket, &QPushButton::clicked, this, [this]()
    {
        engine.addBracket("(");
        refreshDisplay();
    }
    );
    
    connect(btnRightBracket, &QPushButton::clicked, this, [this]()
    {
        engine.addBracket(")");
        refreshDisplay();
    }
    );
        
    connect(btnEq, &QPushButton::clicked, this, [this]()
    {
        engine.evaluateExpression();
        refreshDisplay();
    }
    );
}

void CalculatorWindow::refreshDisplay()
{
    display->setText(engine.getCurrentExpression());
    displayError->setText(engine.getCurrentErrorMessage());
}
