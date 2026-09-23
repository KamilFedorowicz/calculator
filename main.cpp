#include <QApplication>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <vector>
#include <iostream>
#include <QDebug>
#include "calculatorengine.h"
#include <QGridLayout>




int main(int argc, char *argv[]) // start executing the code
{
    
    QApplication app(argc, argv);
    qDebug() << "Application started";
    
    QWidget* window = new QWidget;
    window->setWindowTitle("Calculator");
    window->setFixedSize(400, 600); // width, height
    
    CalculatorEngine engine;
    
    // display
    QTextEdit *display = new QTextEdit;
    display->setReadOnly(true);
    display->setPlainText(engine.getDisplayText());
    display->setFixedHeight(100);
    
    // Number buttons
    QPushButton *btn1 = new QPushButton("But 1");
    QPushButton *btn2 = new QPushButton("But 2");
    QPushButton *btn3 = new QPushButton("But 3");
    QPushButton *btn4 = new QPushButton("But 4");
    QPushButton *btn5 = new QPushButton("But 5");
    QPushButton *btn6 = new QPushButton("But 6");
    QPushButton *btn7 = new QPushButton("But 7");
    QPushButton *btn8 = new QPushButton("But 8");
    QPushButton *btn9 = new QPushButton("But 9");
    QPushButton *btn0 = new QPushButton("But 0");
    QPushButton *btnDiv = new QPushButton("/");
    QPushButton *btnMul = new QPushButton("*");
    QPushButton *btnAdd = new QPushButton("+");
    QPushButton *btnSub = new QPushButton("-");
    QPushButton *btnEq = new QPushButton("=");
    QPushButton *leftBr = new QPushButton("(");
    QPushButton *rightBr = new QPushButton(")");
    
    QPushButton *del = new QPushButton("del");
    QPushButton *dot = new QPushButton("But .");
    QPushButton *clear = new QPushButton("C");
    
    // buttons vector
    std::vector<QPushButton *> numberButtons = {
        btn0,
        btn1,
        btn2,
        btn3,
        btn4,
        btn5,
        btn6,
        btn7,
        btn8,
        btn9,
        leftBr,
        rightBr
    };
    
    for(QPushButton* btn: numberButtons)
    {
        btn->setFixedHeight(80);
    }
    
    std::vector<QPushButton*> signButtons =
    {
        btnDiv,
        btnMul,
        btnAdd,
        btnSub,
        btnEq,
    };
    
    for(QPushButton* btn: signButtons)
    {
        btn->setFixedHeight(80);
        btn->setFixedWidth(40);
    }
    
    dot->setFixedHeight(80);
    del->setFixedHeight(80);
    clear->setFixedHeight(80);
    
    QGridLayout *layout = new QGridLayout;
    
    int numStartRow = 2;
    int numStartCol = 0;
    
    layout->addWidget(display, 0, 0, 1, 4);
    layout->addWidget(leftBr, 1, 0);
    layout->addWidget(dot, 1, 1);
    layout->addWidget(rightBr, 1, 2);
    layout->addWidget(btnDiv, 1, 3);
    layout->addWidget(del, numStartRow+3, numStartCol+2);
    layout->addWidget(clear, numStartRow+3, numStartCol+0);

    
    layout->addWidget(btn7, numStartRow, numStartCol); // widget, row, column
    layout->addWidget(btn8, numStartRow, numStartCol+1);
    layout->addWidget(btn9, numStartRow, numStartCol+2);
    layout->addWidget(btnMul, numStartRow, numStartCol+3);
    layout->addWidget(btn4, numStartRow+1, numStartCol);
    layout->addWidget(btn5, numStartRow+1, numStartCol+1);
    layout->addWidget(btn6, numStartRow+1, numStartCol+2);
    layout->addWidget(btnSub, numStartRow+1, numStartCol+3);
    layout->addWidget(btn1, numStartRow+2, numStartCol);
    layout->addWidget(btn2, numStartRow+2, numStartCol+1);
    layout->addWidget(btn3, numStartRow+2, numStartCol+2);
    layout->addWidget(btnAdd, numStartRow+2, numStartCol+3);
    layout->addWidget(btn0, numStartRow+3, numStartCol+1);
    layout->addWidget(dot, numStartRow+3, numStartCol+2);
    layout->addWidget(btnEq, numStartRow+3, numStartCol+3);

    // Refreshes the GUI from the calculator engine.
    auto refreshDisplay = [&engine, display]()
    {
    display->setPlainText(engine.getDisplayText());
    };
    
    QObject::connect(
        btn1,
        &QPushButton::clicked,
        [&engine, refreshDisplay]()
        {
            engine.appendNumber("1");
            refreshDisplay();
        }
    );
    
    QObject::connect(
        btn2,
        &QPushButton::clicked,
        [&engine, refreshDisplay]()
        {
            engine.appendNumber("2");
            refreshDisplay();
        }
    );
    
    QObject::connect(
        btn3,
        &QPushButton::clicked,
        [&engine, refreshDisplay]()
        {
            engine.appendNumber("3");
            refreshDisplay();
        }
    );
    
    QObject::connect(
        btn4,
        &QPushButton::clicked,
        [&engine, refreshDisplay]()
        {
            engine.appendNumber("4");
            refreshDisplay();
        }
    );
    
    QObject::connect(
        btn5,
        &QPushButton::clicked,
        [&engine, refreshDisplay]()
        {
            engine.appendNumber("5");
            refreshDisplay();
        }
    );
    
    QObject::connect(
        btn6,
        &QPushButton::clicked,
        [&engine, refreshDisplay]()
        {
            engine.appendNumber("6");
            refreshDisplay();
        }
    );
    
    QObject::connect(
        btn7,
        &QPushButton::clicked,
        [&engine, refreshDisplay]()
        {
            engine.appendNumber("7");
            refreshDisplay();
        }
    );
    
    QObject::connect(
        btn8,
        &QPushButton::clicked,
        [&engine, refreshDisplay]()
        {
            engine.appendNumber("8");
            refreshDisplay();
        }
    );

    QObject::connect(
        btn9,
        &QPushButton::clicked,
        [&engine, refreshDisplay]()
        {
            engine.appendNumber("9");
            refreshDisplay();
        }
    );
    
    QObject::connect(
        btn0,
        &QPushButton::clicked,
        [&engine, refreshDisplay]()
        {
            engine.appendNumber("0");
            refreshDisplay();
        }
    );
    
    QObject::connect(
        dot,
        &QPushButton::clicked,
        [&engine, refreshDisplay]()
        {
            engine.appendDecimalPoint();
            refreshDisplay();
        }
    );
    
    QObject::connect(
        del,
        &QPushButton::clicked,
        [&engine, refreshDisplay]()
        {
            engine.backspace();
            refreshDisplay();
        }
    );
    
    QObject::connect(
        clear,
        &QPushButton::clicked,
        [&engine, refreshDisplay]()
        {
            engine.clear();
            refreshDisplay();
        }
    );
    
    QObject::connect(
        btnMul,
        &QPushButton::clicked,
        [&engine, refreshDisplay]()
        {
            engine.appendSign("*");
            refreshDisplay();
        }
    );
    
    QObject::connect(
        btnDiv,
        &QPushButton::clicked,
        [&engine, refreshDisplay]()
        {
            engine.appendSign("/");
            refreshDisplay();
        }
    );
    
    QObject::connect(
        btnAdd,
        &QPushButton::clicked,
        [&engine, refreshDisplay]()
        {
            engine.appendSign("+");
            refreshDisplay();
        }
    );
    
    QObject::connect(
        btnSub,
        &QPushButton::clicked,
        [&engine, refreshDisplay]()
        {
            engine.appendSign("-");
            refreshDisplay();
        }
    );
    
    QObject::connect(
        leftBr,
        &QPushButton::clicked,
        [&engine, refreshDisplay]()
        {
            engine.addBracket("(");
            refreshDisplay();
        }
    );
    
    QObject::connect(
        rightBr,
        &QPushButton::clicked,
        [&engine, refreshDisplay]()
        {
            engine.addBracket(")");
            refreshDisplay();
        }
    );

    
    window->setLayout(layout);
    
    window->show();

    return app.exec();
}

/*
 QPushButton button2("Hello Qt4!", &window); - put this inside the window
 
 */


/*
 QT += widgets
 SOURCES += main.cpp
 
 inside calcilator.pro means
 
 Use Qt Widgets
 Compile main.cpp
 
 later as the code advances, it may become
 QT += widgets

 SOURCES += \
     main.cpp \
     calculator.cpp

 HEADERS += \
     calculator.h

 
 */

/*
 creates an application object, no GUI without
 no GUI without that. it says 'start a QT application
 
 QApplication app(argc, argv);
 
 create a button. at this point it only exists in memory
 QPushButton button("Hello Qt4!");
 
 // changes button size, width = 300, height = 100
 button.resize(300, 100);
 
 // make the button visible
 button.show();
 
 // without it the program starts, button is created and ends
 return app.exec();
 
 */
