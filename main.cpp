#include <QApplication>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <vector>
#include <iostream>
#include <QDebug>
#include "DisplayHelpers.cpp"




int main(int argc, char *argv[]) // start executing the code
{

    QApplication app(argc, argv);
    qDebug() << "Application started";

    QWidget* window = new QWidget;
    window->setWindowTitle("Calculator");
    window->resize(800, 600);

    // buttons
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
    QPushButton *big = new QPushButton("Big");
    QPushButton *del = new QPushButton("del");
    QPushButton *dot = new QPushButton("But .");
    
    // buttons vector
    std::vector<QPushButton*> buttons;
    buttons.push_back(btn1);
    buttons.push_back(btn2);
    buttons.push_back(btn3);
    buttons.push_back(btn4);
    buttons.push_back(btn5);
    buttons.push_back(btn6);
    buttons.push_back(btn7);
    buttons.push_back(btn8);
    buttons.push_back(btn9);
    buttons.push_back(btn0);
    buttons.push_back(del);
    buttons.push_back(dot);
    
    for(QPushButton* btn: buttons)
    {
        btn->setMinimumHeight(100);
    }
    //big->setMinimumHeight(100);
    
    // display
    QTextEdit *display = new QTextEdit;
    display->setReadOnly(true);
    
    QGridLayout *layout = new QGridLayout;
    
    int numStartRow = 2;
    int numStartCol = 0;
    
    layout->addWidget(btn7, numStartRow, numStartCol); // widget, row, column
    layout->addWidget(btn8, numStartRow, numStartCol+1);
    layout->addWidget(btn9, numStartRow, numStartCol+2);
    layout->addWidget(btn4, numStartRow+1, numStartCol);
    layout->addWidget(btn5, numStartRow+1, numStartCol+1);
    layout->addWidget(btn6, numStartRow+1, numStartCol+2);
    layout->addWidget(btn1, numStartRow+2, numStartCol);
    layout->addWidget(btn2, numStartRow+2, numStartCol+1);
    layout->addWidget(btn3, numStartRow+2, numStartCol+2);
    layout->addWidget(btn0, numStartRow+3, numStartCol+1);
    layout->addWidget(dot, numStartRow+3, numStartCol+2);
    layout->addWidget(del, 1, 0);
    layout->addWidget(display, 0, 0, 1, 3);
    
    QObject::connect(btn1, &QPushButton::clicked, [display](){numberPressed(display, "1");});
    QObject::connect(btn2, &QPushButton::clicked, [display](){numberPressed(display, "2");});
    QObject::connect(btn3, &QPushButton::clicked, [display](){numberPressed(display, "3");});
    QObject::connect(btn4, &QPushButton::clicked, [display](){numberPressed(display, "4");});
    QObject::connect(btn5, &QPushButton::clicked, [display](){numberPressed(display, "5");});
    QObject::connect(btn6, &QPushButton::clicked, [display](){numberPressed(display, "6");});
    QObject::connect(btn7, &QPushButton::clicked, [display](){numberPressed(display, "7");});
    QObject::connect(btn8, &QPushButton::clicked, [display](){numberPressed(display, "8");});
    QObject::connect(btn9, &QPushButton::clicked, [display](){numberPressed(display, "9");});
    QObject::connect(btn0, &QPushButton::clicked, [display](){numberPressed(display, "0");});
    QObject::connect(dot, &QPushButton::clicked, [display](){dotPressed(display);});
    QObject::connect(del, &QPushButton::clicked, [display](){delPressed(display);});

    
    window->setLayout(layout);
    
    window->show();
    
    /*
    QWidget window;
    window.resize(400, 300);
    window.setWindowTitle("Calculator window");
    
    QPushButton button1("Hello Qt4!", &window);
    button1.move(50, 50);
    button1.resize(100, 40);

    
    QPushButton button2("Hello Qt5!", &window);
    button2.move(200, 50);
    button2.resize(100, 40);
    
    QTestEdit display;
    window.show();
    */

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
