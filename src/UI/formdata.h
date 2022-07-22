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
    private:
        QVector<QVector<double>> m_temp_control;
        QVector<int> m_time_control;
        bool m_connectBt;
        Q_PROPERTY(bool connectBt
                   READ connectBt
                   WRITE setConnectBt
                   NOTIFY connectChange)
    public:
        static FormData *getInstance();
        explicit FormData(QObject *parent = nullptr);
        Q_INVOKABLE QVector<int> timeControl();
        Q_INVOKABLE QVector<double>  tempControl(int index);
        Q_INVOKABLE void openTempControl();
        bool connectBt() {return m_connectBt;};
        void setConnectBt(bool isConnect);
    signals:
       void connectChange();
    public slots:
        void sendWarningMess();
        void sendTemps(const QString &data);
    };
}

#endif // FORMDATA_H
