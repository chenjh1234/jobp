
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
 
#include "flownode.h"
#include "flowwin.h"


flowNode::flowNode():QGraphicsItem()
{
    //setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setAcceptDrops(false);
    //setAcceptHoverEvents(true);
    setZValue(-1);
    QSize s(NODE_WIDE,NODE_HIGHT);
    setSize(s);
    //setSelected(true);
    setFlag(QGraphicsItem::ItemIsMovable, false);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    m_pdf = NULL;
    m_modInfo = new modInfo();
}
flowNode::~flowNode()
{
    if (m_modInfo != NULL) 
    {
        delete m_modInfo;
    }
}

 
void flowNode::calculateForces()
{
    if (!scene() || scene()->mouseGrabberItem() == this) {
        newPos = pos();
        return;
    }
  /*
    // Sum up all forces pushing this item away
    qreal xvel = 0;
    qreal yvel = 0;
    foreach (QGraphicsItem *item, scene()->items()) {
        flowNode *flowNode = qgraphicsitem_cast<flowNode *>(item);
        if (!flowNode)
            continue;

        QLineF line(mapFromItem(flowNode, 0, 0), QPointF(0, 0));
        qreal dx = line.dx();
        qreal dy = line.dy();
        double l = 2.0 * (dx * dx + dy * dy);
        if (l > 0) {
            xvel += (dx * 150.0) / l;
            yvel += (dy * 150.0) / l;
        }
    }

    // Now subtract all forces pulling items together
    double weight = (edgeList.size() + 1) * 10;
    foreach (Edge *edge, edgeList) {
        QPointF pos;
        if (edge->sourceflowNode() == this)
            pos = mapFromItem(edge->destflowNode(), 0, 0);
        else
            pos = mapFromItem(edge->sourceflowNode(), 0, 0);
        xvel += pos.x() / weight;
        yvel += pos.y() / weight;
    }
    
    if (qAbs(xvel) < 0.1 && qAbs(yvel) < 0.1)
        xvel = yvel = 0;

    QRectF sceneRect = scene()->sceneRect();
    newPos = pos() + QPointF(xvel, yvel);
    newPos.setX(qMin(qMax(newPos.x(), sceneRect.left() + 10), sceneRect.right() - 10));
    newPos.setY(qMin(qMax(newPos.y(), sceneRect.top() + 10), sceneRect.bottom() - 10));
*/  
}

bool flowNode::advance()
{
    if (newPos == pos())
        return false;

    setPos(newPos);
    return true;
}
int flowNode::setSize(QSize s)
{
    m_size = s;
    return 0;
}
QSize flowNode::getSize()
{
    return m_size;
}

QRectF flowNode::boundingRect() const
{
    qreal adjust = 2;
    return QRectF(0 - adjust, 0 - adjust,
                  m_size.width() + adjust, m_size.height() + adjust);
}

QPainterPath flowNode::shape() const
{
    QPainterPath path;
    path.addEllipse(0, 0, m_size.width(), m_size.height());
    return path;
}

void flowNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
 
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawRect(3, 3, m_size.width(), m_size.height());
  // return;
     
    QRadialGradient gradient(m_size.width()/2, m_size.height()/2, m_size.width()/2);
    if (option->state & QStyle::State_Sunken) {
        gradient.setCenter(3, 3);
        gradient.setFocalPoint(3, 3);
        gradient.setColorAt(1, QColor(Qt::yellow).light(120));
        gradient.setColorAt(0, QColor(Qt::darkYellow).light(120));
    } else {
        gradient.setColorAt(0, Qt::cyan);
        gradient.setColorAt(1, Qt::darkCyan);
        if (isSelected()) 
        {     
             gradient.setColorAt(0, Qt::yellow);
             gradient.setColorAt(1, Qt::darkYellow);
        }
   
    }
 
     
 
    painter->setBrush(gradient);
    //painter->setPen(QPen(Qt::black, 0));
    
    if (isSelected())
        painter->setPen(QPen(Qt::red, 0));   

    painter->drawRect(0, 0, m_size.width()-3, m_size.height()-3);

    QString str;
    str = str.setNum(m_id) +":" + m_name.c_str();
    QFont f = painter->font();
    f.setPixelSize(FONT_SIZE);
    painter->setFont(f);
    painter->setPen(QPen(Qt::black, 0));//pen for text;
    //QRect r =  painter->boundingRect (2,2, m_size.width()  ,m_size.height(),Qt::AlignHCenter,str );
    //m_size = QSize(r.width(),m_size.height());
    //painter->drawText(2,2, m_size.height()  ,m_size.height(),Qt::AlignHCenter,str  );
    painter->drawText(2,2, m_size.width()  ,m_size.height(),Qt::AlignHCenter,str  );

   
}

QVariant flowNode::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        //foreach (Edge *edge, edgeList)
        //    edge->adjust();
        //graph->itemMoved();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

void flowNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    flowWin *v =getView();
    v->removeSelectedFlag();
    //update();
    QGraphicsItem::mousePressEvent(event);
}
flowWin * flowNode::getView()
{
    QGraphicsScene *sc = scene ();
    QList<QGraphicsView *> list  = sc->views() ;   
    return(flowWin *)list[0];
  
}
 
void flowNode::rePos()
{
    QGraphicsScene *sc = scene ();
    QList<QGraphicsView *> list  = sc->views() ;
    
    flowWin *v = getView();
    //qDebug("v = %d\n",v) ;
    v->setNodePos();
}
 
void flowNode::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    rePos();
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
/*
void flowNode::hoverEnterEvent ( QGraphicsSceneHoverEvent * event )
{
     qDebug() << " hover Enter= "<< m_id  << m_name;
     QGraphicsItem::hoverEnterEvent(event);
}
void flowNode::hoverLeaveEvent ( QGraphicsSceneHoverEvent * event )
{
    qDebug() << " hover leave= "<< m_id  << m_name;
    QGraphicsItem::hoverLeaveEvent(event);

}
void flowNode::hoverMoveEvent ( QGraphicsSceneHoverEvent * event )
{
    qDebug() << " hover move= "<< m_id  << m_name;
    QGraphicsItem::hoverMoveEvent(event);

} 
*/ 
void	flowNode::dragEnterEvent ( QGraphicsSceneDragDropEvent * event )
{
    qDebug() << " dragEnter Event= "<< m_id  << getQName();
    QGraphicsItem::dragEnterEvent(event);

}
void	flowNode::dragLeaveEvent( QGraphicsSceneDragDropEvent * event )
{
    qDebug() << " dragLeaveEvent= "<< m_id  << getQName();
    QGraphicsItem::dragLeaveEvent(event);

}
void	flowNode::dragMoveEvent( QGraphicsSceneDragDropEvent * event )
{
    qDebug() << " dragMoveEvent= "<< m_id  << getQName();
    QGraphicsItem::dragMoveEvent(event);

}
string   flowNode::getName()
{
    return m_name;
}
QString   flowNode::getQName()
{
    QString str;
    str = m_name.c_str();
    return str;
}
void flowNode::setName(QString n)
{
    string str;
    str = n.toUtf8().data();
    setName(str);
}
void flowNode::setName(string n)
{
    m_name = n;
    m_modInfo->setModule(n);
    m_pdf = m_modInfo->getPDef();
}
void	dragLeaveEvent ( QGraphicsSceneDragDropEvent * event );
void dragMoveEvent ( QGraphicsSceneDragDropEvent * event );
