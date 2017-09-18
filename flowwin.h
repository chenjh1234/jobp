
#ifndef FLOWWIN_H 
#define FLOWWIN_H 

#include <QWidget>
#include <QGraphicsView>
#include "flownode.h"
#include "sysdefine.h"



class flowWin :public QGraphicsView
{
    Q_OBJECT

public:
    flowWin(QWidget *p);
    ~flowWin();


    int removeNode(int id);
    int moveNode(int nodeid,int index);

    void setNodePos();
    void removeSelectedFlag();

    int findSelectedIndex();
    flowNode * getSelected();
    int numNodes();
    void clear();


public slots:
    int slotAddNode(QString name);
protected:
    void keyPressEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);
    void wheelEvent(QWheelEvent *event);
    void drawBackground(QPainter *painter, const QRectF &rect);
    void scaleView(qreal scaleFactor);
    void mousePressEvent ( QMouseEvent * event );
    //void mousePressEvent ( QMouseEvent * event );
    void mouseDoubleClickEvent ( QMouseEvent * event );
    void resizeEvent ( QResizeEvent * event );
    //void drawBackground ( QPainter * painter, const QRectF & rect ) ;



signals:

    void sigAddNode(flowNode *);
    void sigShowParam(flowNode*);
    void sigRemoveParam(flowNode*);
    void sigModHelp(QString);

private:     
    void init();
    void itemMoved();

    
    int timerId;
    QGraphicsScene *scene;
     
    QList <flowNode *> m_listNode;

};



#endif
