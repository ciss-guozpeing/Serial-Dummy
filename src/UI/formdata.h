#ifndef FORMDATA_H
#define FORMDATA_H
#include <QObject>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QMap>
#include <QVector>

#include "xlsxdocument.h"
#include "xlsxworksheet.h"
#include "xlsxcellrange.h"
#include "xlsxformat.h"
#include "xlsxcell.h"

namespace UI
{
    class FormData : public QObject
    {
        Q_OBJECT
        QVector<QVector<double>> m_temp_control;
        QVector<int> m_time_control;
        bool m_connectBt;
        QVector<int> m_beepState = {0,0,0,0,0,0,0,0,0};
        QVector<int> m_areaSortWareMap={9,10,13,14,11,12,15,16,23,24,25,26,27,28,5,6,7,8,1,2,3,4,17,18,20,21,22,19,29};
        QVector<int> m_areaHardWareMap={19,20,21,22,15,16,17,18,1,2,5,6,3,4,7,8,23,24,28,25,26,27,9,10,11,12,13,14,29};
        int m_beepIndex;
    private:
        Q_PROPERTY(bool connectBt
                   READ connectBt
                   WRITE setConnectBt
                   NOTIFY connectChange)
        Q_PROPERTY(QVector<int> beepState
                   READ beepState
                   WRITE setBeepState
                   NOTIFY beepStateChanged)
        Q_PROPERTY(int beepIndex
                   READ beepIndex
                   WRITE setBeepIndex
                   NOTIFY beepIndexChanged)
        Q_PROPERTY(QVector<int> areaSortWareMap
                   READ areaSortWareMap)
        Q_PROPERTY(QVector<int> areaHardWareMap
                   READ areaHardWareMap)

    public:
        static FormData *getInstance();
        explicit FormData(QObject *parent = nullptr);
        Q_INVOKABLE QVector<int> timeControl();
        Q_INVOKABLE QVector<double>  tempControl(int index);
        Q_INVOKABLE void openTempControl();
        bool connectBt() {return m_connectBt;};
        QVector<int> beepState() {return m_beepState;};
        QVector<int> areaSortWareMap() {return m_areaSortWareMap;};
        QVector<int> areaHardWareMap() {return m_areaHardWareMap;};
        int beepIndex() {return m_beepIndex;};
        void setConnectBt(bool isConnect);
        void setBeepState(QVector<int> beepState);
        void setBeepIndex(int index);

    signals:
       void connectChange();
       void beepStateChanged();
       void beepIndexChanged();
    public slots:
        void sendWarningMess();
        void sendData(const QString &data);
    };
}

#endif // FORMDATA_H
