 
#ifndef FLOWNODE_H
#define FLOWNODE_H

#include <QGraphicsItem>
#include <QList>
#include <QSize>
#include <QDebug>
#include "modinfo.h"
#include "csParamDef.h"
//#include "flowwin.h"
class flowWin;
class Edge;
 
QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

#define NODE_WIDE 100
#define NODE_HIGHT 30
#define FONT_SIZE 12

#define NODE_X 50
#define NODE_Y 50
#define NODE_GAP 20

using namespace cseis_system;

class flowNode : public QGraphicsItem
{
public:
    flowNode();
    ~flowNode();
    QRectF boundingRect() const;
    QPainterPath shape() const;

    int setSize(QSize s);
    QSize getSize();

    string getName();
    QString getQName();
    void setName(string n);
    void setName(QString n);

    int m_id;//if the index of the node in flowView:
    csParamDef *m_pdf;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void rePos();

    //hover = mouse moving event
   // void	hoverEnterEvent ( QGraphicsSceneHoverEvent * event );
   // void	hoverLeaveEvent ( QGraphicsSceneHoverEvent * event );
   // void	hoverMoveEvent ( QGraphicsSceneHoverEvent * event );  
    void	dragEnterEvent ( QGraphicsSceneDragDropEvent * event );
    void	dragLeaveEvent ( QGraphicsSceneDragDropEvent * event );
    void dragMoveEvent ( QGraphicsSceneDragDropEvent * event );
    
private:
    QSize m_size;
    QPointF newPos;
    flowWin * getView();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void calculateForces();
    bool advance();


    modInfo *m_modInfo;
 
    string m_name;
     
};

#endif
