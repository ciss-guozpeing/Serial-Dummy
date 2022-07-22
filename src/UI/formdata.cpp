#include "FormData.h"

#include "Logger.h"
#include "IO/Manager.h"
#include "EXCEL/Play.h"

using namespace UI;
static FormData *INSTANCE = nullptr;

FormData::FormData(QObject *parent) : QObject(parent)
{
}

FormData *FormData::getInstance()
{
    if (!INSTANCE) {
        INSTANCE = new FormData();
    }
    return INSTANCE;
}

void FormData::sendWarningMess()
{
    QMessageBox box;
    box.setTextFormat(Qt::RichText);
    box.setIcon(QMessageBox::Critical);
    QString text = tr("目标温度有空值,请确认！");
    box.setInformativeText(text);
    box.setDefaultButton(QMessageBox::Yes);
    if (box.exec() == QMessageBox::Yes) {
        box.exec();
    }
}

void FormData::sendTemps(const QString &data)
{
    QByteArray bin = data.toUtf8();
    IO::Manager::getInstance()->writeData(bin);
}

void FormData::openTempControl()
{
    m_time_control.clear();
    m_temp_control.clear();
    auto play = EXCEL::Play::getInstance();
    QString fileName = play->openExcel();
    QXlsx::Document xlsx(fileName);
    xlsx.selectSheet(xlsx.sheetNames().first());
    int rowCount = xlsx.dimension().rowCount();
    int columnCount = xlsx.dimension().columnCount();
    for (int i=2; i<rowCount + 1; i++) {
        QVector<double> tempVcetor;
        for (int j=1; j<columnCount + 1; j++){
            QString cellValue = xlsx.cellAt(i,j)->value().toString();
            if (j==1){
                 m_time_control.push_back(cellValue.toInt());
            } else {
                tempVcetor.push_back(cellValue.toDouble());
            }
        }
        m_temp_control.push_back(tempVcetor);
    }
}

QVector<double>  FormData::tempControl(int index)
{
    return m_temp_control.at(index);
}

QVector<int> FormData::timeControl()
{
    return m_time_control;
}

void FormData::setConnectBt(bool isConnect)
{
    m_connectBt = isConnect;
    emit connectChange();
}

