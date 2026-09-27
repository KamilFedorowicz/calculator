#include <QApplication>

#include "calculatorwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    CalculatorWindow window;
    window.show();

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
