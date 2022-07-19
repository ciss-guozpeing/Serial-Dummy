#include "DummyView.h"

using namespace UI;
DummyView::DummyView()
{
}

void DummyView::paint(QPainter* painter)
{

    QColor initColor;
    initColor.setBlue(100);
    // 加载图片
    for (int i=0; i<m_vector_images->count(); i++){
        QImage image;
        image.load(QString(":/images/1x/%1.png").arg(i+1));
        image = image.convertToFormat(QImage::Format_RGBA8888_Premultiplied,Qt::NoFormatConversion);
        m_vector_images->replace(i,image);
    }


    //
    QVector<QImage>::iterator iter;
    int nums=0;
    for (iter = m_vector_images->begin();iter!=m_vector_images->end();iter++){
        nums +=1;
        QVector<QPoint> vector_points;
        int bmpWidth = iter->width();
        int bmpHeight = iter->height();
        for (int w=0; w<bmpWidth; w++){
            for (int h=0; h<bmpHeight; h++){
                if (iter->pixelColor(w,h).value()){
                    QPoint point(w,h);
                    point = point + m_position_points[nums-1];
                    iter->colorCount();
                    vector_points.push_back(point);
                    iter->setPixelColor(w,h,initColor);
                }
            }
        }
        m_area_ponints.insert(nums, vector_points);
    }
    this->_createDummy(painter);
}

void DummyView::mousePressEvent(QMouseEvent *event)
{
    qDebug() <<  "CustomItem::mousePressEvent" ;
    QQuickPaintedItem::mousePressEvent(event);
    event->pos();
    qDebug()<<event->pos();
}


void DummyView::areaClicked(int mouseX, int mouseY)
{
    QMap<int,QVector<QPoint>>::Iterator iter;
    for (iter=m_area_ponints.begin();iter!=m_area_ponints.end(); iter++)
    {
        if (iter->contains(QPoint(mouseX,mouseY))){
            qDebug() <<iter.key();
            qDebug()<<mouseX;
            qDebug() << mouseY;
        }
    }
}

void DummyView::_createDummy(QPainter* painter)
{
    for(int i=0; i<m_vector_images->count();i++){
        painter->drawImage(m_position_points[i],m_vector_images->at(i));
    }
//    // 正面
//    painter->drawImage(34,81, m_vector_images->at(8)); // 胸部
//    painter->drawImage(m_position_points[0],m_vector_images->at(0));   // 右上臂
//    painter->drawImage(142,98, m_vector_images->at(2)); // 左上臂
//    painter->drawImage(38,156, m_vector_images->at(10)); //腹部
//    painter->drawImage(42,223, m_vector_images->at(12)); // 腰部
//    painter->drawImage(4,204, m_vector_images->at(4));  //右下臂
//    painter->drawImage(146,204, m_vector_images->at(6));  // 左下臂
//    painter->drawImage(34,249, m_vector_images->at(18));  // 右臀部
//    painter->drawImage(90,249, m_vector_images->at(20));  // 左臀部
//    painter->drawImage(33,282, m_vector_images->at(14));  // 右大腿
//    painter->drawImage(90,282, m_vector_images->at(16));  // 左大腿
//    painter->drawImage(43,418, m_vector_images->at(22));  // 右小腿
//    painter->drawImage(99,418, m_vector_images->at(24));  // 左小腿



//    // 背面
//    int x = 240;
//    painter->drawImage(60 + x,0,m_vector_images->at(28));  // 头部
//    painter->drawImage(34 + x,80, m_vector_images->at(9)); // 胸部
//    painter->drawImage(5 + x,97,m_vector_images->at(3));   // 右上臂
//    painter->drawImage(145 + x,97, m_vector_images->at(1)); // 左上臂
//    painter->drawImage(38 + x,156, m_vector_images->at(11)); //腹部
//    painter->drawImage(39 + x,223, m_vector_images->at(13)); // 腰部
//    painter->drawImage(4 + x,204, m_vector_images->at(7));  //右下臂
//    painter->drawImage(146 + x,204, m_vector_images->at(5));  // 左下臂
//    painter->drawImage(34 + x,260, m_vector_images->at(21));  // 右臀部
//    painter->drawImage(90 + x,260, m_vector_images->at(19));  // 左臀部
//    painter->drawImage(31 + x,287, m_vector_images->at(17));  // 右大腿
//    painter->drawImage(89 + x,286, m_vector_images->at(15));  // 左大腿
//    painter->drawImage(40 + x,404, m_vector_images->at(25));  // 右小腿
//    painter->drawImage(99 + x,404, m_vector_images->at(23));  // 左小腿
//    painter->drawImage(53 + x,541, m_vector_images->at(26));  // 右脚
//    painter->drawImage(102 + x,541, m_vector_images->at(27));  // 左脚

    // 特殊
    painter->drawImage(53,542, m_vector_images->at(26));  // 右脚
    painter->drawImage(100,542, m_vector_images->at(27));  // 左脚
    painter->drawImage(60,0,m_vector_images->at(28));  // 头部

}
