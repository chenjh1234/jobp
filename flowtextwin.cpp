#include "flowtextwin.h"

#include <QFont>
flowTextWin::flowTextWin(QWidget *p):QTextBrowser(p)
{
    init();
}
//=======================
flowTextWin::~flowTextWin()
{

}

//=======================
void flowTextWin::init()
{ 
    QFont ft;
    //ft = font();
    //ft.setStyleHint(QFont::TypeWriter,QFont::PreferOutline);
    //ft.setStyleHint(QFont::SansSerif);
    //ft.setStyleHint(QFont::Times);//QFont::Courier
    ft.setFamily("Courier");
    //ft.setStyleHint(QFont::Courier);
    ft.setPixelSize(14);

    qDebug() << "qfont = " << ft.family();
    setFont(ft);
   
    //setLineWrapMode(QTextEdit::NoWrap) ; //line will end with "\n"
    //setLineWrapMode(QTextEdit::WidgetWidth) ; //line will added when meet widget right eadge
   // setLineWrapMode(QTextEdit::FixedPixelWidth) ; //line will end with " ";
   // setLineWrapMode(QTextEdit::FixedColumnWidth) ; //line will end with a char;

}
void flowTextWin::mousePressEvent(QMouseEvent *e)
{ 
    
    QTextBrowser::mousePressEvent(e);
    QTextCursor cursor = textCursor();
    
    int i;
    //qDebug() << "x,y ="  << e->x() << e->y();
    //qDebug() <<"first select= " <<   lastCursor.selectedText();// it is "" ???
 // restore the last cursor to white backgroud.
    setTextCursor(lastCursor);
    lastFmt.setBackground(Qt::white);
    lastCursor.mergeCharFormat(lastFmt);
    mergeCurrentCharFormat(lastFmt);
   // qDebug()<< lastFmt.background();
   
    //QColor col = QColorDialog::getColor(textEdit->textColor(), this);
    QColor col;
    col = Qt::red;
    QBrush br;
    br=Qt::yellow;
  
     //qDebug() <<"last= " <<   cursor.selectedText();// it is "" ???
// change the current line to yellow:
    setTextCursor(cursor);
    QTextCharFormat fmt;
    lastFmt = cursor.charFormat();
//    fmt.setForeground(col);
    fmt.setBackground(br);
 
    cursor.select(QTextCursor::LineUnderCursor);
    
    // we put  QTextBrowser::mousePressEvent(e),to upper posotion
    //qDebug() <<  cursor.selectedText() << fmt.background(); 

    cursor.mergeCharFormat(fmt);//we need this two
    mergeCurrentCharFormat(fmt);//we need this two;
    lastCursor = cursor; //remember the cursor,in order to restore the background next time;
   
   // QTextBrowser::mouseDoubleClickEvent(e);
    
   
}
