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

    public:
        static FormData *getInstance();
        explicit FormData(QObject *parent = nullptr);
        Q_INVOKABLE QVector<int> timeControl();
        Q_INVOKABLE QVector<double>  tempControl(int index);
        Q_INVOKABLE void openTempControl();
        bool connectBt() {return m_connectBt;};
        QVector<int> beepState() {return m_beepState;};
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
