#include "calculatorwindow.h"

#include <QFont>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSizePolicy>

void CalculatorWindow::keyPressEvent(QKeyEvent* event)
{
    qDebug() << "Text:" << event->text();
    
    QString text = event->text();
    bool isItSign = engine.isSign(text);
    
    if(text.length() == 1)
    {
        QChar c = text.front();
        
        // handling nunmbers
        if(c.isDigit())
        {
            qDebug() << "Number appended";
            engine.appendNumber(text);
            clearHistory();
        }
        
        // handling brackets
        if(c == "(" || c == ")")
        {
            qDebug() << "Bracket appended";
            engine.addBracket(text);
        }
    }
    
    if(isItSign)
    {
        // handling signs
        qDebug() << "Sign appended";
        engine.appendSign(text);
        clearHistory();
    }
    
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        // handling enters
        qDebug() << "Expression evaluated";
        engine.evaluateExpression();
        refreshHistory();
    }
    
    if(event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Delete)
    {
        // handling backspace
        qDebug() << "Backspace pressed";
        engine.backspace();
    }
    
    
    refreshDisplay();
}

CalculatorWindow::CalculatorWindow(QWidget *parent): QWidget(parent)
{
    setWindowTitle("Calculator");
    setFixedSize(400, 600);
    
    createWidgets();
    createLayout();
    setButtonsStyle();
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
    display->setFixedHeight(40);
    display->setAlignment(Qt::AlignRight);
    
    QFont displayFont = display->font();
    displayFont.setPointSize(28);
    display->setFont(displayFont);
    
    displayError = new QLineEdit(this);
    displayError->setReadOnly(true);
    displayError->setFixedHeight(30);
    displayError->setAlignment(Qt::AlignRight);
    
    QFont displayErrorFont = displayError->font();
    displayErrorFont.setPointSize(14);
    displayError->setFont(displayErrorFont);
    
    historyList = new QListWidget(this);
    historyList->setFixedHeight(30);
    QFont historyFont = historyList->font();
    historyFont.setPointSize(14);
    historyList->setFont(historyFont);
    
    display->setFocusPolicy(Qt::NoFocus); // this widget cannot become a keyboard target
    displayError->setFocusPolicy(Qt::NoFocus);
    
    setFocusPolicy(Qt::StrongFocus); // this widget is allowed to receive keyboard focus
    setFocus(); // give focus to this widget now
    
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
    
    numberButtons = {
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
    
    btnAdd = createButton("+");
    btnSub = createButton("-");
    btnMul = createButton("*");
    btnDiv = createButton("/");
    btnEq = createButton("=");
    
    signButtons = {
        btnAdd,
        btnSub,
        btnMul,
        btnDiv,
        btnEq
    };
    
    btnDot = createButton(".");
    btnDelete = createButton("DEL");
    btnClear = createButton("C");
    btnLeftBracket = createButton("(");
    btnRightBracket = createButton(")");
    
    otherButtons = {
        btnDot,
        btnDelete,
        btnClear,
        btnLeftBracket,
        btnRightBracket
    };
    

}

void CalculatorWindow::setButtonsStyle()
{
    for(QPushButton* button: numberButtons)
    {
        button->setStyleSheet(
            "QPushButton {"
                "background-color: #5C6B7B;"
                "color: white;"
                "border-radius: 25px;"
                "font-size: 20px;"
            "}"

            "QPushButton:hover {"
                "background-color: #A2B6C7;"
            "}"

            "QPushButton:pressed {"
                "background-color: #1A202C;"
            "}"
        );
    }
    
    for(QPushButton* button: signButtons)
    {
        button->setStyleSheet(
            "QPushButton {"
                "background-color: #4A90E2;"
                "color: white;"
                "border-radius: 25px;"
                "font-size: 20px;"
            "}"

            "QPushButton:hover {"
                "background-color: #6AA8EF;"
            "}"

            "QPushButton:pressed {"
                "background-color: #3478D5;"
            "}"
        );
    }
    
    for(QPushButton* button: otherButtons)
    {
        button->setStyleSheet(
            "QPushButton {"
                "background-color: #FF8824;"
                "color: white;"
                "border-radius: 25px;"
                "font-size: 20px;"
            "}"

            "QPushButton:hover {"
                "background-color: #FFB066;"
            "}"

            "QPushButton:pressed {"
                "background-color: #D65A00;"
            "}"
        );
    }
    
}

void CalculatorWindow::createLayout()
{
    layout = new QGridLayout(this);
        
    int dispR = 1;
    
    layout->addWidget(display, dispR, 0, 1, 4);
    
    layout->addWidget(displayError, dispR+1, 0, 1, 4);
    
    layout->addWidget(historyList, dispR-1, 0,1,4);
        
    layout->addWidget(btnLeftBracket, dispR+2, 0);
    layout->addWidget(btnRightBracket, dispR+2, 1);
    layout->addWidget(btnClear, dispR+2, 2);
    layout->addWidget(btnDiv, dispR+2, 3);
        
    layout->addWidget(btn7, dispR+3, 0);
    layout->addWidget(btn8, dispR+3, 1);
    layout->addWidget(btn9, dispR+3, 2);
    layout->addWidget(btnMul, dispR+3, 3);
        
    layout->addWidget(btn4, dispR+4, 0);
    layout->addWidget(btn5, dispR+4, 1);
    layout->addWidget(btn6, dispR+4, 2);
    layout->addWidget(btnSub, dispR+4, 3);
        
    layout->addWidget(btn1, dispR+5, 0);
    layout->addWidget(btn2, dispR+5, 1);
    layout->addWidget(btn3, dispR+5, 2);
    layout->addWidget(btnAdd, dispR+5, 3);
        
    layout->addWidget(btnDelete, dispR+6, 0);
    layout->addWidget(btn0, dispR+6, 1);
    layout->addWidget(btnDot, dispR+6, 2);
    layout->addWidget(btnEq, dispR+6, 3);
        
    layout->setSpacing(6);
    layout->setContentsMargins(10, 10, 10, 10);
        
    for (int column = 0; column < 4; ++column)
    {
        layout->setColumnStretch(column, 1);
    }
}

void CalculatorWindow::connectButtons()
{
    for (QPushButton *button : numberButtons)
    {
        // when the button is clicked, execute this piece of...
        // 3rd argument receiver is the object that owns the connection. 'this' is the pointer to the current CalculatorWindow object
        // 4th argument is the action to execute.
        connect(button, &QPushButton::clicked, this, [this, button]()
        {
            engine.appendNumber(button->text());
            refreshDisplay();
            clearHistory();
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
            clearHistory();
        }
        );
    }
    
    connect(btnDot, &QPushButton::clicked, this, [this]()
        {
            engine.appendDecimalPoint();
            refreshDisplay();
            clearHistory();
        }
            );
    
    connect(btnDelete, &QPushButton::clicked, this, [this]()
    {
        engine.backspace();
        refreshDisplay();
        clearHistory();
    }
    );
    
    connect(btnClear, &QPushButton::clicked, this, [this]()
    {
        engine.clear();
        refreshDisplay();
        clearHistory();
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
        refreshHistory();
    }
    );
}

void CalculatorWindow::refreshDisplay()
{
    display->setText(engine.getCurrentExpression());
    displayError->setText(engine.getCurrentErrorMessage());
    
    //historyList->addItem(engine.historyExpression);
}

void CalculatorWindow::refreshHistory()
{
    clearHistory();
    QListWidgetItem* item = new QListWidgetItem(engine.historyExpression);
    
    item->setTextAlignment(Qt::AlignRight);
    historyList->addItem(item);
}

void CalculatorWindow::clearHistory()
{
    historyList->clear();
}
