#ifndef DUMMYVIEW_H
#define DUMMYVIEW_H

#include <QObject>
#include <QImage>
#include <QPainter>
#include <QQuickPaintedItem>
#include <QPoint>
#include <QMap>
#include <QVector>
//#include <QPushButton>
namespace UI{
class DummyView: public QQuickPaintedItem
{
    Q_OBJECT
private:
    QMap<int,QVector<QPoint>> m_area_ponints;
    QVector<QImage> *m_vector_images = new QVector<QImage>(29);
    void _createDummy(QPainter* painter);
    int x = 220;
    QMap<int,QPoint> m_position_points={
        {0,QPoint(6,98)},{1,QPoint(145 + x,97)},{2,QPoint(142,98)},{3,QPoint(5 + x,97)},{4,QPoint(4,204)},
        {5,QPoint(146 + x,204)},{6,QPoint(146,204)},{7,QPoint(4 + x,204)},{8,QPoint(34,81)},{9,QPoint(34 + x,80)},
        {10,QPoint(38,156)},{11,QPoint(38 + x,156)},{12,QPoint(42,223)},{13,QPoint(39 + x,223)},{14,QPoint(33,282)},
        {15,QPoint(89 + x,286)},{16,QPoint(90,282)},{17,QPoint(31 + x,287)},{18,QPoint(34,249)},{19,QPoint(90 + x,260)},
        {20,QPoint(90,249)},{21,QPoint(34 + x,260)},{22,QPoint(43,418)},{23,QPoint(99 + x,404)},{24,QPoint(99,418)},
        {25,QPoint(40 + x,404)},{26,QPoint(53 + x,541)},{27,QPoint(102 + x,541)},{28,QPoint(60 + x,0)}
    };

public:
    DummyView();
    virtual void paint(QPainter* painter);

    virtual   void  mousePressEvent(QMouseEvent *event);
//    virtual   void  mouseMoveEvent(QMouseEvent *event);
//    virtual   void  mouseReleaseEvent(QMouseEvent *event);

    Q_INVOKABLE void areaClicked(int mouseX, int mouseY);
};

}

#endif // DUMMYVIEW_H
