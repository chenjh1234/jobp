#include "flowwin.h"
#include "flowapplication.h"
#include <QGraphicsScene>
#include <QWheelEvent>
#include <QMessageBox>
#include <math.h>
flowWin::flowWin(QWidget *p):QGraphicsView(p)
{
    init();
}
//=======================
flowWin::~flowWin()
{
    
}
void flowWin::clear()
{
    int i,num;
    //flowNode *n;
    // delete node:
    num = m_listNode.size();
    for (i = 0; i<num ; i++) 
    {
        removeNode(num -1-i);
    }
     
}
int flowWin::numNodes()
{
    return m_listNode.size();
}
flowNode * flowWin::getSelected()
{
    int i,num;
    //selected NodeID:
    num = m_listNode.size();
    flowNode *fnode;
    fnode = NULL;
 
    for (i = 0 ;i < num ; i++)
    {
        fnode = m_listNode[i];
        if (fnode->isSelected()) 
           return fnode;
    }
    return NULL;

}
void flowWin::removeSelectedFlag()
{
 
    int num;
    int i;
  
//selected NodeID:
    num = m_listNode.size();
    flowNode *fnode;
    for (i = 0 ;i < num ; i++)
    {
        fnode = m_listNode[i];
        //fnode->setSelectd(false);   
        fnode->setSelected(false);
        fnode->update();
    }
}
void flowWin::setNodePos()
{
    int nodeGap;
    int num;
    int i,x,y,iy;
    x = NODE_X;
    iy = NODE_Y;
    nodeGap = NODE_GAP;

//selected NodeID:
    num = m_listNode.size();
    scene->setSceneRect(0,0,NODE_X +NODE_X + NODE_WIDE ,(NODE_HIGHT + NODE_GAP)*num +NODE_Y);
    flowNode *fnode;
 
    for (i = 0 ;i < num ; i++)
    {
        fnode = m_listNode[i];
        y = iy + (fnode->getSize().height() + nodeGap)*fnode->m_id;
        //qDebug() << i<< fnode->m_name <<  fnode->m_id;
        fnode->setPos(x,y);   
        fnode->update();
    }
}
int flowWin::findSelectedIndex()
{
    int num;
    int i;
 
//selected NodeID:
    num = m_listNode.size();
    flowNode *fnode;
 
    for (i = 0 ;i < num ; i++)
    {
        fnode = m_listNode[i];
        if (fnode->isSelected()) 
           return fnode->m_id;
    }
    return -1;
}
int flowWin::moveNode(int nodeid,int index)
{
    int num;
    int i;//,x,y,iy;

    num = m_listNode.size();
    flowNode *fnode;
    for (i = 0 ;i < num ; i++)
    {
        fnode = m_listNode[i]; 
        if(fnode->m_id == nodeid)
        {
           // qDebug() << "nodid  i= " << i << "id = " << fnode->m_id ;
            fnode->m_id = index;
        }
        else if (nodeid > index) 
        {
            if (fnode->m_id >= index && fnode->m_id  < nodeid) 
            {    
                fnode->m_id = fnode->m_id + 1;
                //qDebug() << "+1 i= " << i << "id = " << fnode->m_id ;
            }
        }
        else if (nodeid < index) 
        {
            if (fnode->m_id > nodeid && fnode->m_id  <= index) 
            {    
                fnode->m_id = fnode->m_id -1 ;
                //qDebug() << "+1 i= " << i << "id = " << fnode->m_id ;
            }

        }
        
    }
    //node->setSelected(true);
    //qDebug() << "listsize = " << m_listNode.size();
    
    theApp->m_win->setWindowModified(true);//move
 
    setNodePos();
    updateGeometry ();
    return 0;
}
int flowWin::slotAddNode(QString n)
{
    int num;
    int selectedNodeID;
    int i;//,x,y,iy;
    QString str;
    //qDebug() <<  "===add Node";
 
//selected NodeID:
    num = m_listNode.size();
    selectedNodeID = findSelectedIndex();
    
// insert Node:
    flowNode *node = new flowNode();
    node->setName(n);
    //qDebug() <<  "===add Node = " << node->m_pdf;
    if (node->m_pdf == NULL )
    {
        str = QString(" No this module: ") + n;
        QMessageBox::warning(this,"err",str);
        return -1;
    }
    scene->addItem(node);
      Q_CHECK_PTR(node);
    //node->setName(n);
     
    flowNode *fnode;
 
    for (i = 0 ;i < num ; i++)
    {
        fnode = m_listNode[i]; 
        if(fnode->m_id >=selectedNodeID&&selectedNodeID !=-1 )
        {//chaned the m_id: if id > insert Node.m_id
            fnode->setSelected(false);
            if (fnode->m_id >selectedNodeID&&selectedNodeID !=-1) 
            fnode->m_id = fnode->m_id + 1; 
        }
    }

    node->m_id = selectedNodeID +1;
    if (selectedNodeID == -1) 
        node->m_id = num;

    node->setSelected(true);
    m_listNode.append(node);
    if(!theApp->m_doc->m_loadFile)
        theApp->m_win->setWindowModified(true);// add
    emit sigAddNode(node);
    setNodePos();
    //repaint();
    //scene()->update();
    updateGeometry ();
    return 0;
}
int flowWin::removeNode(int id)
{
    //find:
    foreach(flowNode *node,m_listNode)
    {
        if (node->m_id == id) 
        {   
            emit sigRemoveParam(node);
            m_listNode.removeAll(node);  
            delete node;
            break;
        }
    }
//re index and select:
    int num;
    int i;//,x,y,iy;
    flowNode *fnode,*fnodeLast;
    num = m_listNode.size();
    
    for (i = 0 ;i < num ; i++)
    {
        fnode = m_listNode[i]; 
 
        if (fnode->m_id > id) 
        {  
            fnode->m_id = fnode->m_id -1;
            if (fnode->m_id == id) 
            {
                fnode->setSelected(true);
                emit sigShowParam(fnode);
            }
        }
 
    }
    if (id == num && id !=0)
    {//last:
         fnode->setSelected(true);
         emit sigShowParam(fnode);
    }
   
//    qDebug() << "listsize = " << m_listNode.size();
    theApp->m_win->setWindowModified(true);//remove
    setNodePos();
    return 0;
}

//=======================
void flowWin::init()
{   
 
    timerId = 0;
    scene = new QGraphicsScene(this);

    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0, 0, 300, 300);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    setResizeAnchor(AnchorViewCenter);
   // setResizeAnchor(NoAnchor);
    setAlignment ( Qt::AlignLeft|Qt::AlignTop);

    //scale(qreal(0.8), qreal(0.8));
    //setMinimumSize(400, 400);
    setWindowTitle(tr("flow "));
    //scene->setBackgroundBrush(Qt::blue);
   // flowView->setBackgroundBrush(QPixmap(":/images/flowback.jpg"));
}
 
void flowWin::itemMoved()
{
    //if (!timerId)
    //    timerId = startTimer(1000 / 25);
}

void flowWin::keyPressEvent(QKeyEvent *event)
{
    //qDebug("modify = %X,%X,%x\n",event->modifiers(),Qt::ShiftModifier,event->modifiers()& Qt::ShiftModifier);

    if (event->modifiers() != Qt::ShiftModifier) return;
    int id = findSelectedIndex();
    if (id < 0)return;
 

    switch (event->key()) {
    case Qt::Key_Up:
         if (id <=0)break;
        moveNode(id,id-1);
        break; 
    case Qt::Key_Down:
        if (id < m_listNode.size()-1) 
            moveNode(id, id + 1); 
        break;
    case Qt::Key_Left:
        removeNode(id);
        break;
    case Qt::Key_Right:
        //centerNode->moveBy(20, 0);
        break;
    case Qt::Key_Plus:
        //scaleView(qreal(1.2));
        break;
    case Qt::Key_Minus:
        //scaleView(1 / qreal(1.2));
        break;
    case Qt::Key_Space:
    case Qt::Key_Enter:
        //foreach (QGraphicsItem *item, scene()->items()) {
        //    if (qgraphicsitem_cast<Node *>(item))
        //        item->setPos(-150 + qrand() % 300, -150 + qrand() % 300);
        //}
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
     
}

void flowWin::timerEvent(QTimerEvent *event)
{
    /*
    Q_UNUSED(event);

    QList<Node *> nodes;
    foreach (QGraphicsItem *item, scene()->items()) {
        if (Node *node = qgraphicsitem_cast<Node *>(item))
            nodes << node;
    }

    foreach (Node *node, nodes)
        node->calculateForces();

    bool itemsMoved = false;
    foreach (Node *node, nodes) {
        if (node->advance())
            itemsMoved = true;
    }

    if (!itemsMoved) {
        killTimer(timerId);
        timerId = 0;
    }
    */
}

void flowWin::wheelEvent(QWheelEvent *event)
{
   // scaleView(pow((double)2, -event->delta() / 240.0));
}

void flowWin::drawBackground(QPainter *painter, const QRectF &rect)
{
    QGraphicsView::drawBackground(painter,rect);
    return;
    Q_UNUSED(rect);

    // Shadow
    QRectF sceneRect = this->sceneRect();
    QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
    QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
	painter->fillRect(rightShadow, Qt::darkGray);
    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
	painter->fillRect(bottomShadow, Qt::darkGray);

    // Fill
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);
    return;

    // Text
    QRectF textRect(sceneRect.left() + 4, sceneRect.top() + 4,
                    sceneRect.width() - 4, sceneRect.height() - 4);
    QString message(tr("Click and drag the nodes around, and zoom with the mouse "
                       "wheel or the '+' and '-' keys"));

    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(14);
    painter->setFont(font);
    painter->setPen(Qt::lightGray);
    painter->drawText(textRect.translated(2, 2), message);
    painter->setPen(Qt::black);
    painter->drawText(textRect, message);
}

void flowWin::scaleView(qreal scaleFactor)
{
    qreal factor = matrix().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}
void flowWin::mouseDoubleClickEvent ( QMouseEvent * event )
{
    int x,y;
    QGraphicsView::mouseDoubleClickEvent(event); 
    flowNode *item;
    QList<QGraphicsItem *> l;
    QString str;

    x= event->x();
    y = event->y();
    
    l = items(x,y);
    qDebug()<< "start";

    if(l.size()>0) 
    {
        item = (flowNode *)l[0]; 
   
        if(item !=NULL) 
        {
            str = item->getQName();
            qDebug()<< "qname = " << str;
            //emit sigShowParam(item);
            emit sigModHelp(item->getQName());
        }
     }

}
void flowWin::mousePressEvent ( QMouseEvent * event )
{
    
    int x,y;
    QGraphicsView::mousePressEvent(event); 
    flowNode *item;
    QList<QGraphicsItem *> l;
    QString str;

    x= event->x();
    y = event->y();
    
    l = items(x,y);
    //qDebug()<< "start";

    if(l.size()>0) 
    {
        item = (flowNode *)l[0]; 
   
        if(item !=NULL) 
        {
            str = item->getQName();
            //qDebug()<< "emit sig =" <<str;
            emit sigShowParam(item);
            //emit sigModHelp(item->getQName());
        }
        //qDebug()<< "out ";
     }
    
}
void flowWin::resizeEvent ( QResizeEvent * event )
{
    
    //scene->setSceneRect(0,0,event->size().width(),event->size().height());
    QGraphicsView::resizeEvent(event);
}
