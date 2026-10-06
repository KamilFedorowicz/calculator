#include "calculatorwindow.h"
#include "aboutdialog.h"

#include <QFont>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSizePolicy>
#include <QSettings>

CalculatorWindow::CalculatorWindow(QWidget *parent): QWidget(parent)
{
    setWindowTitle("Calculator");
    setFixedSize(400, 600);
    
    createWidgets();
    createMenuBar();
    //createHelpMenuBar();
    createLayout();
    
    loadSettings(); // load settings has to be after widgets are created because it uses refresh dispaly for expample, which cannot be a null pointer
    setTheme();
    
    connectButtons();
    
    refreshDisplay();
    refreshHistory();
     
}

void CalculatorWindow::toggleTheme()
{
    if(theme == "dark")
    {
        theme = "light";
    }
    else if(theme == "light")
    {
        theme = "dark";
    }
    
    setTheme();
    qDebug() << "Theme:" << theme;
}

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

void CalculatorWindow::applyLightTheme()
{
    
}

void CalculatorWindow::applyDarkTheme()
{
    
}

void CalculatorWindow::styleButtons(
    const QList<QPushButton*>& buttons,
    const QString& normalColour,
    const QString& hoverColour,
    const QString& pressedColour)
{
    for(QPushButton* button : buttons)
    {
        button->setStyleSheet(
            QString(
                "QPushButton {"
                    "background-color: %1;"
                    "color: white;"
                    "border-radius: 25px;"
                    "font-size: 20px;"
                "}"
                "QPushButton:hover {"
                    "background-color: %2;"
                "}"
                "QPushButton:pressed {"
                    "background-color: %3;"
                "}"
            )
            .arg(normalColour)
            .arg(hoverColour)
            .arg(pressedColour)
        );
    }
}

void CalculatorWindow::setTheme()
{
    
    if(theme == "dark")
    {
        styleButtons(numberButtons, "#3C444C", "#59636B","#252B31");
        styleButtons(signButtons, "#2563EB", "#3B82F6", "#1D4ED8");
        styleButtons(otherButtons, "#C2410C", "#EA580C", "#9A3412");
        display->setStyleSheet(
            "background-color: black;"
            "color: white;"
            "border-radius: 15px;"
        );
        
        displayError->setStyleSheet(
            "background-color: black;"
            "color: white;"
            "border-radius: 10px;"
        );
        
        historyList->setStyleSheet(
            "background-color: black;"
            "color: white;"
            "border-radius: 10px;"
        );
    }
    else if(theme == "light")
    {
        styleButtons(numberButtons, "#5C6B7B", "#A2B6C7","#1A202C");
        styleButtons(signButtons, "#4A90E2", "#6AA8EF", "#3478D5");
        styleButtons(otherButtons, "#FF8824", "#FFB066", "#D65A00");
        display->setStyleSheet(
            "background-color: white;"
            "color: black;"
            "border-radius: 15px;"
        );
        
        displayError->setStyleSheet(
            "background-color: white;"
            "color: black;"
            "border-radius: 10px;"
        );
        
        historyList->setStyleSheet(
            "background-color: white;"
            "color: black;"
            "border-radius: 10px;"
        );
    }
}

void CalculatorWindow::setLightTheme()
{
    styleButtons(numberButtons, "#5C6B7B", "#A2B6C7","#1A202C");
    styleButtons(signButtons, "#4A90E2", "#6AA8EF", "#3478D5");
    styleButtons(otherButtons, "#FF8824", "#FFB066", "#D65A00");
    
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

void CalculatorWindow::saveSettings()
{
    // organisation, application
    QSettings settings("Kamil", "Calculator");

    // creates a setting called currentExpression, and assignes value of engine.getCurrentExpression()
    settings.setValue(
        "currentExpression",
        engine.getCurrentExpression()
    );

    settings.setValue("historyExpression", engine.historyExpression);
    
    settings.setValue("theme", theme);
    
    qDebug() << settings.fileName();
}

void CalculatorWindow::loadSettings()
{
    QSettings settings("Kamil", "Calculator");

    // find setting called currentExpression, return stored value
    QString expression =
        settings.value(
            "currentExpression",
            "0"
        ).toString();
    
    engine.setCurrentExpression(expression);

    QString history =
        settings.value(
            "historyExpression",
            ""
        ).toString();
    
    theme = settings.value("theme", "light").toString();
    setTheme();
    
    engine.historyExpression = history;
    //historyList->addItem(history);
    
    refreshDisplay();
    refreshHistory();
}

void CalculatorWindow::closeEvent(QCloseEvent* event)
{
    saveSettings();
    QWidget::closeEvent(event);
}

void CalculatorWindow::createMenuBar()
{
    menuBar = new QMenuBar(this);
    viewMenu = menuBar->addMenu("View");
    
    toggleThemeAction = new QAction("Toggle theme", this);
    viewMenu->addAction(toggleThemeAction);
    connect(
        toggleThemeAction,
        &QAction::triggered,
        this,
        [this]()
        {
            toggleTheme();
        }
    );
    
    // this is just for learning purposes. it activates evaluate button from the view menu. rather not necessary and can be easily deleted
    testEval = new QAction("Evaluate");
    viewMenu->addAction(testEval);
    connect(
        testEval,
        &QAction::triggered,
        this,
        [this]()
        {
            engine.evaluateExpression();
            refreshDisplay();
            refreshHistory();
        }
    );
    
}

void CalculatorWindow::createHelpMenuBar()
{
    helpMenu = menuBar->addMenu("Help");
    aboutAction = new QAction("About", this);

    helpMenu->addAction(aboutAction);
    
    connect(
        aboutAction,
        &QAction::triggered,
        this,
        [this]()
        {
            AboutDialog dialog(this);
            dialog.exec();
        }
    );
}
