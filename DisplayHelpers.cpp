#include "DisplayHelpers.h"

void numberPressed(QTextEdit *display, const QString num)
{
    display->insertPlainText(num);
}

void delPressed(QTextEdit *display)
{
    QString text = display->toPlainText();
    
    if(!text.isEmpty())
    {
        text.chop(1);
        display->setPlainText(text);
    }
}
 
void dotPressed(QTextEdit *display)
{
    int num_dots = 0;
    QString text = display->toPlainText();
    
    for(QChar c: text)
    {
        if(c=='.')
        {
            return;
        }
    }
    
    display->insertPlainText(".");
}
