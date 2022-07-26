#include "DummyView.h"

using namespace UI;
DummyView::DummyView()
{
    this->getImage_1();
    this->getImage_2();
    this->getImage_3();
    this->getImage_4();
    this->getImage_5();
    this->getImage_6();
    this->getImage_7();
    this->getImage_8();
    this->getImage_9();
    this->getImage_10();
    this->getImage_11();
    this->getImage_12();
    this->getImage_13();
    this->getImage_14();
    this->getImage_15();
    this->getImage_16();
    this->getImage_17();
    this->getImage_18();
    this->getImage_19();
    this->getImage_20();
    this->getImage_21();
    this->getImage_22();
    this->getImage_23();
    this->getImage_24();
    this->getImage_25();
    this->getImage_26();
    this->getImage_27();
    this->getImage_28();
    this->getImage_29();
}

void DummyView::paint(QPainter* painter)
{
    // 加载图片
    for (int i=0; i<m_vector_images->count(); i++){
        QImage image;
        image.load(QString(":/images/1x/%1.png").arg(i+1));
        image = image.convertToFormat(QImage::Format_RGBA8888_Premultiplied,Qt::NoFormatConversion);
        m_vector_images->replace(i,image);
    }

    // 设置点
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
    // 正面
    painter->drawImage(34,81, m_image_9); // 胸部
    painter->drawImage(6,98, m_image_1);   // 右上臂
    painter->drawImage(142,98, m_image_3); // 左上臂
    painter->drawImage(38,156, m_image_11); //腹部
    painter->drawImage(42,223, m_image_13); // 腰部
    painter->drawImage(4,204, m_image_5);  //右下臂
    painter->drawImage(146,204, m_image_7);  // 左下臂
    painter->drawImage(34,249, m_image_19);  // 右臀部
    painter->drawImage(90,249, m_image_21);  // 左臀部
    painter->drawImage(33,282, m_image_15);  // 右大腿
    painter->drawImage(90,282, m_image_17);  // 左大腿
    painter->drawImage(43,418, m_image_23);  // 右小腿
    painter->drawImage(99,418, m_image_25);  // 左小腿
    // 特殊
    painter->drawImage(53,542, m_image_27);  // 右脚
    painter->drawImage(100,542, m_image_28);  // 左脚
    painter->drawImage(60,0, m_image_29);  // 头部

    // 背面
    int x = 240;
    painter->drawImage(60 + x,0,m_image_29);  // 头部
    painter->drawImage(34 + x,80, m_image_10); // 胸部
    painter->drawImage(5 + x,97, m_image_4);   // 右上臂
    painter->drawImage(145 + x,97, m_image_2); // 左上臂
    painter->drawImage(38 + x,156, m_image_12); //腹部
    painter->drawImage(39 + x,223, m_image_14); // 腰部
    painter->drawImage(4 + x,204, m_image_8);  //右下臂
    painter->drawImage(146 + x,204, m_image_6);  // 左下臂
    painter->drawImage(34 + x,260, m_image_22);  // 右臀部
    painter->drawImage(90 + x,260, m_image_20);  // 左臀部
    painter->drawImage(31 + x,287, m_image_18);  // 右大腿
    painter->drawImage(89 + x,286, m_image_16);  // 左大腿
    painter->drawImage(40 + x,404, m_image_26);  // 右小腿
    painter->drawImage(99 + x,404, m_image_24);  // 左小腿
    painter->drawImage(53 + x,541, m_image_27);  // 右脚
    painter->drawImage(102 + x,541, m_image_28);  // 左脚
}

void DummyView::setAreaColor(QImage& image)
{
    QColor color;
    QColor defaultColor;

    defaultColor.setGreen(100);
    color.setRed(getTempValue());

    int bmpWidth = image.width();
    int bmpHeight = image.height();
        for (int w=0; w<bmpWidth; w++){
            for (int h=0; h<bmpHeight; h++){
                if (image.pixelColor(w,h).value()!=255){
                    if (getTempValue()==0){
                        image.setPixelColor(w,h,defaultColor);
                    } else{
                        image.setPixelColor(w,h,color);
                    }
                }
            }
        }
}

void DummyView::setImage_1(QImage image)
{
    m_image_1 = image;
    this->setAreaColor(m_image_1);
    emit image1Changed();
}

QImage DummyView::getImage_1()
{
    m_image_1.load(":/images/1x/1.png");
    this->setAreaColor(m_image_1);
    return m_image_1;
}


void DummyView::setImage_2(QImage image)
{
    m_image_2 = image;
    this->setAreaColor(m_image_2);
    emit image2Changed();
}

QImage DummyView::getImage_2()
{
    m_image_2.load(":/images/1x/2.png");
    this->setAreaColor(m_image_2);
    return m_image_2;
}


void DummyView::setImage_3(QImage image)
{
    m_image_3 = image;
    this->setAreaColor(m_image_3);
    emit image3Changed();
}

QImage DummyView::getImage_3()
{
    m_image_3.load(":/images/1x/3.png");
    this->setAreaColor(m_image_3);
    return m_image_3;
}


void DummyView::setImage_4(QImage image)
{
    m_image_4 = image;
    this->setAreaColor(m_image_4);
    emit image4Changed();
}

QImage DummyView::getImage_4()
{
    m_image_4.load(":/images/1x/4.png");
    this->setAreaColor(m_image_4);
    return m_image_4;
}

void DummyView::setImage_5(QImage image)
{
    m_image_5 = image;
    this->setAreaColor(m_image_5);
    emit image5Changed();
}

QImage DummyView::getImage_5()
{
    m_image_5.load(":/images/1x/5.png");
    this->setAreaColor(m_image_5);
    return m_image_5;
}

void DummyView::setImage_6(QImage image)
{
    m_image_6 = image;
    this->setAreaColor(m_image_6);
    emit image6Changed();
}

QImage DummyView::getImage_6()
{
    m_image_6.load(":/images/1x/6.png");
    this->setAreaColor(m_image_6);
    return m_image_6;
}


void DummyView::setImage_7(QImage image)
{
    m_image_7 = image;
    this->setAreaColor(m_image_7);
    emit image7Changed();
}

QImage DummyView::getImage_7()
{
    m_image_7.load(":/images/1x/7.png");
    this->setAreaColor(m_image_7);
    return m_image_1;
}


void DummyView::setImage_8(QImage image)
{
    m_image_8 = image;
    this->setAreaColor(m_image_8);
    emit image8Changed();
}

QImage DummyView::getImage_8()
{
    m_image_8.load(":/images/1x/8.png");
    this->setAreaColor(m_image_8);
    return m_image_8;
}


void DummyView::setImage_9(QImage image)
{
    m_image_9 = image;
    this->setAreaColor(m_image_9);
    emit image9Changed();
}

QImage DummyView::getImage_9()
{
    m_image_9.load(":/images/1x/9.png");
    this->setAreaColor(m_image_9);
    return m_image_9;
}

void DummyView::setImage_10(QImage image)
{
    m_image_10 = image;
    this->setAreaColor(m_image_10);
    emit image10Changed();
}

QImage DummyView::getImage_10()
{
    m_image_10.load(":/images/1x/10.png");
    this->setAreaColor(m_image_10);
    return m_image_10;
}


void DummyView::setImage_11(QImage image)
{
    m_image_11 = image;
    this->setAreaColor(m_image_11);
    emit image11Changed();
}

QImage DummyView::getImage_11()
{
    m_image_11.load(":/images/1x/11.png");
    this->setAreaColor(m_image_11);
    return m_image_11;
}


void DummyView::setImage_12(QImage image)
{
    m_image_12 = image;
    this->setAreaColor(m_image_12);
    emit image12Changed();
}

QImage DummyView::getImage_12()
{
    m_image_12.load(":/images/1x/12.png");
    this->setAreaColor(m_image_12);
    return m_image_12;
}


void DummyView::setImage_13(QImage image)
{
    m_image_13 = image;
    this->setAreaColor(m_image_13);
    emit image13Changed();
}

QImage DummyView::getImage_13()
{
    m_image_13.load(":/images/1x/13.png");
    this->setAreaColor(m_image_13);
    return m_image_13;
}


void DummyView::setImage_14(QImage image)
{
    m_image_14 = image;
    this->setAreaColor(m_image_14);
    emit image14Changed();
}

QImage DummyView::getImage_14()
{
    m_image_14.load(":/images/1x/14.png");
    this->setAreaColor(m_image_14);
    return m_image_14;
}


void DummyView::setImage_15(QImage image)
{
    m_image_15 = image;
    this->setAreaColor(m_image_15);
    emit image15Changed();
}

QImage DummyView::getImage_15()
{
    m_image_15.load(":/images/1x/15.png");
    this->setAreaColor(m_image_15);
    return m_image_15;
}


void DummyView::setImage_16(QImage image)
{
    m_image_16 = image;
    this->setAreaColor(m_image_16);
    emit image16Changed();
}

QImage DummyView::getImage_16()
{
    m_image_16.load(":/images/1x/16.png");
    this->setAreaColor(m_image_16);
    return m_image_16;
}


void DummyView::setImage_17(QImage image)
{
    m_image_17 = image;
    this->setAreaColor(m_image_17);
    emit image17Changed();
}

QImage DummyView::getImage_17()
{
    m_image_17.load(":/images/1x/17.png");
    this->setAreaColor(m_image_17);
    return m_image_17;
}


void DummyView::setImage_18(QImage image)
{
    m_image_18 = image;
    this->setAreaColor(m_image_18);
    emit image18Changed();
}

QImage DummyView::getImage_18()
{
    m_image_18.load(":/images/1x/18.png");
    this->setAreaColor(m_image_18);
    return m_image_18;
}


void DummyView::setImage_19(QImage image)
{
    m_image_19 = image;
    this->setAreaColor(m_image_19);
    emit image19Changed();
}

QImage DummyView::getImage_19()
{
    m_image_19.load(":/images/1x/19.png");
    this->setAreaColor(m_image_19);
    return m_image_19;
}


void DummyView::setImage_20(QImage image)
{
    m_image_20 = image;
    this->setAreaColor(m_image_20);
    emit image20Changed();
}

QImage DummyView::getImage_20()
{
    m_image_20.load(":/images/1x/20.png");
    this->setAreaColor(m_image_20);
    return m_image_20;
}

void DummyView::setImage_21(QImage image)
{
    m_image_21 = image;
    this->setAreaColor(m_image_21);
    emit image21Changed();
}

QImage DummyView::getImage_21()
{
    m_image_21.load(":/images/1x/21.png");
    this->setAreaColor(m_image_21);
    return m_image_21;
}

void DummyView::setImage_22(QImage image)
{
    m_image_22 = image;
    this->setAreaColor(m_image_22);
    emit image22Changed();
}

QImage DummyView::getImage_22()
{
    m_image_22.load(":/images/1x/22.png");
    this->setAreaColor(m_image_22);
    return m_image_22;
}

void DummyView::setImage_23(QImage image)
{
    m_image_23 = image;
    this->setAreaColor(m_image_23);
    emit image23Changed();
}

QImage DummyView::getImage_23()
{
    m_image_23.load(":/images/1x/23.png");
    this->setAreaColor(m_image_23);
    return m_image_23;
}

void DummyView::setImage_24(QImage image)
{
    m_image_24 = image;
    this->setAreaColor(m_image_24);
    emit image24Changed();
}

QImage DummyView::getImage_24()
{
    m_image_24.load(":/images/1x/24.png");
    this->setAreaColor(m_image_24);
    return m_image_24;
}

void DummyView::setImage_25(QImage image)
{
    m_image_25 = image;
    this->setAreaColor(m_image_25);
    emit image25Changed();
}

QImage DummyView::getImage_25()
{
    m_image_25.load(":/images/1x/25.png");
    this->setAreaColor(m_image_25);
    return m_image_25;
}

void DummyView::setImage_26(QImage image)
{
    m_image_26 = image;
    this->setAreaColor(m_image_26);
    emit image26Changed();
}

QImage DummyView::getImage_26()
{
    m_image_26.load(":/images/1x/26.png");
    this->setAreaColor(m_image_26);
    return m_image_26;
}

void DummyView::setImage_27(QImage image)
{
    m_image_27 = image;
    this->setAreaColor(m_image_27);
    emit image27Changed();
}

QImage DummyView::getImage_27()
{
    m_image_27.load(":/images/1x/27.png");
    this->setAreaColor(m_image_27);
    return m_image_27;
}

void DummyView::setImage_28(QImage image)
{
    m_image_28 = image;
    this->setAreaColor(m_image_28);
    emit image28Changed();
}

QImage DummyView::getImage_28()
{
    m_image_28.load(":/images/1x/28.png");
    this->setAreaColor(m_image_28);
    return m_image_28;
}

void DummyView::setImage_29(QImage image)
{
    m_image_29 = image;
    this->setAreaColor(m_image_29);
    emit image29Changed();
}

QImage DummyView::getImage_29()
{
    m_image_29.load(":/images/1x/29.png");
    this->setAreaColor(m_image_29);
    return m_image_29;
}

void DummyView::setImageSource(QString imageSource)
{
    Q_UNUSED(imageSource);
    int areaIndex = getAreaIndex();
    switch (areaIndex) {
    case 1:
        this->setAreaColor(m_image_1);
        break;
    case 2:
        this->setAreaColor(m_image_2);
        break;
    case 3:
        this->setAreaColor(m_image_3);
        break;
    case 4:
        this->setAreaColor(m_image_4);
        break;
    case 5:
        this->setAreaColor(m_image_5);
        break;
    case 6:
        this->setAreaColor(m_image_6);
        break;
    case 7:
        this->setAreaColor(m_image_7);
        break;
    case 8:
        this->setAreaColor(m_image_8);
        break;
    case 9:
        this->setAreaColor(m_image_9);
        break;
    case 10:
        this->setAreaColor(m_image_10);
        break;
    case 11:
        this->setAreaColor(m_image_11);
        break;
    case 12:
        this->setAreaColor(m_image_12);
        break;
    case 13:
        this->setAreaColor(m_image_13);
        break;
    case 14:
        this->setAreaColor(m_image_14);
        break;
    case 15:
        this->setAreaColor(m_image_15);
        break;
    case 16:
        this->setAreaColor(m_image_16);
        break;
    case 17:
        this->setAreaColor(m_image_17);
        break;
    case 18:
        this->setAreaColor(m_image_18);
        break;
    case 19:
        this->setAreaColor(m_image_19);
        break;
    case 20:
        this->setAreaColor(m_image_20);
        break;
    case 21:
        this->setAreaColor(m_image_21);
        break;
    case 22:
        this->setAreaColor(m_image_22);
        break;
    case 23:
        this->setAreaColor(m_image_23);
        break;
    case 24:
        this->setAreaColor(m_image_24);
        break;
    case 25:
        this->setAreaColor(m_image_25);
        break;
    case 26:
        this->setAreaColor(m_image_26);
        break;
    case 27:
        this->setAreaColor(m_image_27);
        break;
    case 28:
        this->setAreaColor(m_image_28);
        break;
    case 29:
        this->setAreaColor(m_image_29);
        break;
    default:
        break;
    }

    emit imageSourceChanged();
}

QString DummyView::getImageSource()
{
    return m_imageSource;
}


int DummyView::getAreaIndex()
{
    return m_areaIndex;
}

void DummyView::setAreaIndex(int areaIndex)
{
    m_areaIndex = areaIndex;
    emit areaIndexChanged();
    update();
}

int DummyView::getTempValue()
{
    return m_tempValue;
}

void DummyView::setTempValue(int tempValue)
{
    m_tempValue = tempValue;
    emit tempValueChanged();
    update();

}


