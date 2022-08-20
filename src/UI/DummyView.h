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
    Q_PROPERTY(QImage image_1
               READ getImage_1
               WRITE setImage_1
               NOTIFY image1Changed)

    Q_PROPERTY(QImage image_2
               READ getImage_2
               WRITE setImage_2
               NOTIFY image2Changed)

    Q_PROPERTY(QImage image_3
               READ getImage_3
               WRITE setImage_3
               NOTIFY image3Changed)

    Q_PROPERTY(QImage image_4
               READ getImage_4
               WRITE setImage_4
               NOTIFY image4Changed)

    Q_PROPERTY(QImage image_5
               READ getImage_5
               WRITE setImage_5
               NOTIFY image5Changed)

    Q_PROPERTY(QImage image_6
               READ getImage_6
               WRITE setImage_6
               NOTIFY image6Changed)

    Q_PROPERTY(QImage image_7
               READ getImage_7
               WRITE setImage_7
               NOTIFY image7Changed)

    Q_PROPERTY(QImage image_8
               READ getImage_8
               WRITE setImage_8
               NOTIFY image8Changed)

    Q_PROPERTY(QImage image_9
               READ getImage_9
               WRITE setImage_9
               NOTIFY image9Changed)

    Q_PROPERTY(QImage image_10
               READ getImage_10
               WRITE setImage_10
               NOTIFY image10Changed)

    Q_PROPERTY(QImage image_11
               READ getImage_11
               WRITE setImage_11
               NOTIFY image11Changed)

    Q_PROPERTY(QImage image_12
               READ getImage_12
               WRITE setImage_12
               NOTIFY image12Changed)

    Q_PROPERTY(QImage image_13
               READ getImage_13
               WRITE setImage_13
               NOTIFY image13Changed)

    Q_PROPERTY(QImage image_14
               READ getImage_14
               WRITE setImage_14
               NOTIFY image14Changed)

    Q_PROPERTY(QImage image_15
               READ getImage_15
               WRITE setImage_15
               NOTIFY image15Changed)

    Q_PROPERTY(QImage image_16
               READ getImage_16
               WRITE setImage_16
               NOTIFY image16Changed)

    Q_PROPERTY(QImage image_17
               READ getImage_17
               WRITE setImage_17
               NOTIFY image17Changed)

    Q_PROPERTY(QImage image_18
               READ getImage_18
               WRITE setImage_18
               NOTIFY image18Changed)

    Q_PROPERTY(QImage image_19
               READ getImage_19
               WRITE setImage_19
               NOTIFY image19Changed)

    Q_PROPERTY(QImage image_20
               READ getImage_20
               WRITE setImage_20
               NOTIFY image20Changed)

    Q_PROPERTY(QImage image_22
               READ getImage_22
               WRITE setImage_22
               NOTIFY image22Changed)

    Q_PROPERTY(QImage image_22
               READ getImage_22
               WRITE setImage_22
               NOTIFY image22Changed)

    Q_PROPERTY(QImage image_23
               READ getImage_23
               WRITE setImage_23
               NOTIFY image23Changed)

    Q_PROPERTY(QImage image_24
               READ getImage_24
               WRITE setImage_24
               NOTIFY image24Changed)

    Q_PROPERTY(QImage image_25
               READ getImage_25
               WRITE setImage_25
               NOTIFY image25Changed)

    Q_PROPERTY(QImage image_26
               READ getImage_26
               WRITE setImage_26
               NOTIFY image26Changed)
    Q_PROPERTY(QImage image_27
               READ getImage_27
               WRITE setImage_27
               NOTIFY image27Changed)
    Q_PROPERTY(QImage image_28
               READ getImage_28
               WRITE setImage_28
               NOTIFY image28Changed)
    Q_PROPERTY(QImage image_29
               READ getImage_29
               WRITE setImage_29
               NOTIFY image29Changed)

    Q_PROPERTY(int areaIndex
               READ getAreaIndex
               WRITE setAreaIndex
               NOTIFY areaIndexChanged)
    Q_PROPERTY(int tempValue
               READ getTempValue
               WRITE setTempValue
               NOTIFY tempValueChanged)
    Q_PROPERTY(QString imageSource
               READ getImageSource
               WRITE setImageSource
               NOTIFY imageSourceChanged)
private:
    QMap<int,QVector<QPoint>> m_area_ponints;
    QVector<QImage> *m_vector_images = new QVector<QImage>(29);
    QVector<QRect> *m_vector_leds = new QVector<QRect>(9);
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

    QImage m_image_1;
    QImage m_image_2;
    QImage m_image_3;
    QImage m_image_4;
    QImage m_image_5;
    QImage m_image_6;
    QImage m_image_7;
    QImage m_image_8;
    QImage m_image_9;
    QImage m_image_10;
    QImage m_image_11;
    QImage m_image_12;
    QImage m_image_13;
    QImage m_image_14;
    QImage m_image_15;
    QImage m_image_16;
    QImage m_image_17;
    QImage m_image_18;
    QImage m_image_19;
    QImage m_image_20;
    QImage m_image_21;
    QImage m_image_22;
    QImage m_image_23;
    QImage m_image_24;
    QImage m_image_25;
    QImage m_image_26;
    QImage m_image_27;
    QImage m_image_28;
    QImage m_image_29;
    QImage m_image_f27;
    QImage m_image_f28;
    QImage m_image_f29;
    QString m_imageSource_1;
    QString m_imageSource_2;
    QString m_imageSource_3;
    QString m_imageSource_4;
    QString m_imageSource_5;
    QString m_imageSource_6;
    QString m_imageSource_7;
    QString m_imageSource_8;
    QString m_imageSource_9;
    QString m_imageSource_10;
    QString m_imageSource_11;
    QString m_imageSource_12;
    QString m_imageSource_13;
    QString m_imageSource_14;
    QString m_imageSource_15;
    QString m_imageSource_16;
    QString m_imageSource_17;
    QString m_imageSource_18;
    QString m_imageSource_19;
    QString m_imageSource_20;
    QString m_imageSource_21;
    QString m_imageSource_22;
    QString m_imageSource_23;
    QString m_imageSource_24;
    QString m_imageSource_25;
    QString m_imageSource_26;
    QString m_imageSource_27;
    QString m_imageSource_28;
    QString m_imageSource_29;

    int m_areaIndex;
    int m_tempValue;
    QString m_imageSource;

public:
    DummyView();
    virtual void paint(QPainter* painter);
    virtual   void  mousePressEvent(QMouseEvent *event);

    void setImage_1(QImage image);
    QImage getImage_1();

    void setImage_2(QImage image);
    QImage getImage_2();

    void setImage_3(QImage image);
    QImage getImage_3();

    void setImage_4(QImage image);
    QImage getImage_4();

    void setImage_5(QImage image);
    QImage getImage_5();

    void setImage_6(QImage image);
    QImage getImage_6();

    void setImage_7(QImage image);
    QImage getImage_7();

    void setImage_8(QImage image);
    QImage getImage_8();

    void setImage_9(QImage image);
    QImage getImage_9();

    void setImage_10(QImage image);
    QImage getImage_10();

    void setImage_11(QImage image);
    QImage getImage_11();

    void setImage_12(QImage image);
    QImage getImage_12();

    void setImage_13(QImage image);
    QImage getImage_13();

    void setImage_14(QImage image);
    QImage getImage_14();

    void setImage_15(QImage image);
    QImage getImage_15();

    void setImage_16(QImage image);
    QImage getImage_16();

    void setImage_17(QImage image);
    QImage getImage_17();

    void setImage_18(QImage image);
    QImage getImage_18();

    void setImage_19(QImage image);
    QImage getImage_19();

    void setImage_20(QImage image);
    QImage getImage_20();

    void setImage_21(QImage image);
    QImage getImage_21();

    void setImage_22(QImage image);
    QImage getImage_22();

    void setImage_23(QImage image);
    QImage getImage_23();

    void setImage_24(QImage image);
    QImage getImage_24();

    void setImage_25(QImage image);
    QImage getImage_25();

    void setImage_26(QImage image);
    QImage getImage_26();

    void setImage_27(QImage image);
    QImage getImage_27();

    void setImage_28(QImage image);
    QImage getImage_28();

    void setImage_29(QImage image);
    QImage getImage_29();;

    void setImageSource(QString imageSources);
    QString getImageSource();

    void setAreaIndex(int index);
    int getAreaIndex();

    void setTempValue(int tempValue);
    int getTempValue();

    Q_INVOKABLE void areaClicked(int mouseX, int mouseY);
    Q_INVOKABLE void setAreaColor(QImage& image);

signals:
    void image1Changed();
    void image2Changed();
    void image3Changed();
    void image4Changed();
    void image5Changed();
    void image6Changed();
    void image7Changed();
    void image8Changed();
    void image9Changed();
    void image10Changed();
    void image11Changed();
    void image12Changed();
    void image13Changed();
    void image14Changed();
    void image15Changed();
    void image16Changed();
    void image17Changed();
    void image18Changed();
    void image19Changed();
    void image20Changed();
    void image21Changed();
    void image22Changed();
    void image23Changed();
    void image24Changed();
    void image25Changed();
    void image26Changed();
    void image27Changed();
    void image28Changed();
    void image29Changed();

    void imageSourceChanged();
    void areaIndexChanged();
    void tempValueChanged();
};
}

#endif // DUMMYVIEW_H
