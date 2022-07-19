#include "Save.h"
#include "UI/DrawCurve.h"
#include "Misc/Utilities.h"

using namespace EXCEL;
static Save *INSTANCE = nullptr;

Save::Save()
{

}

Save *Save::getInstance()
{
    if (!INSTANCE) {
        INSTANCE = new Save;
    }
    return INSTANCE;
}

void Save::autoSave()
{
    createDir();
    createFileName();

    QXlsx::Document xlsx;

    QXlsx::Format format;
    format.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    format.setVerticalAlignment(QXlsx::Format::AlignVCenter);

    auto ui = UI::DrawCurve::getInstance();
    // 添加数据
    QList<QList<double>> tmpdata;
    addTmpData(tmpdata, ui->getEnvCurveNum(), m_lastframe, ui->getHistoryEnvTemp()[0].size(), ui->getHistoryEnvTemp());
    addTmpData(tmpdata, ui->getHeatPowerCurveNum(), m_lastframe, ui->getHistoryHeatPower()[0].size(), ui->getHistoryHeatPower());
    addTmpData(tmpdata, ui->getTempCurveNum(), m_lastframe, ui->getHistoryTemp()[0].size(), ui->getHistoryTemp());
    QList<unsigned long long> rowCount;
    for (int i = 0; i < tmpdata.size(); ++i) {
        rowCount.append(tmpdata[i].size());
    }
    std::sort(rowCount.begin(), rowCount.end());
    QList<QList<double>> writedata;
    for (unsigned long long i = 0; i < rowCount.last(); ++i) {
        QList<double> tmp_rows;
        for (int j = 0; j < sum_channelNums + 3; ++j) {
            double value;
            unsigned long long  colSize = tmpdata.at(j).size();
            if (colSize > i) {
                value = tmpdata.at(j).at(i);
            } else {
                value = -1;
            }
            tmp_rows.append(value);
        }
        writedata.append(tmp_rows);
    }
    // 写入表头
    createHeader(xlsx);

    // 写入单元格
    for (int i = 0; i < writedata.size(); ++i) {
        for (int j = 0; j < writedata[i].size(); ++j) {
            xlsx.write(i+3, j+1, writedata[i][j], format);
        }
    }


    bool isSave = xlsx.saveAs(this->fileName());
    if (isSave){
        auto utilities = Misc::Utilities::getInstance();
        utilities->showMessageBox("自动保存文件","自动保存文件成功");
    }
}

void Save::addTmpData(QList<QList<double>> &tmpData, int channelNum,
                      unsigned long long start_frame, unsigned long long end_frame,
                      QVector<QVector<QPointF>> historyPointF)
{
    if (start_frame == 0 && end_frame == 0) {
        for (int i = 0; i < channelNum; ++i) {
            unsigned long long frameNums = historyPointF[i].size();
            if (i == 0) {// 添加帧数
                QList<double> frameDatas;
                for(unsigned long long j = 0; j < frameNums; ++j) {
                    frameDatas.append(j  + 1);
                }
                tmpData.append(frameDatas);
            }
            QList<double> colDatas;
            for(unsigned long long j = 0; j < frameNums; ++j) {
                colDatas.append(historyPointF[i][j].y());
            }
            tmpData.append(colDatas);
        }
    } else {
        for (int i = 0; i < channelNum; ++i) {
            if (i == 0) {// 添加帧数
                QList<double> frameDatas;
                for(unsigned long long j = start_frame; j < end_frame; ++j) {
                    frameDatas.append(j + 1);
                }
                tmpData.append(frameDatas);
            }
            QList<double> colDatas;
            // 判断选择帧越界
            if (end_frame > static_cast<unsigned long long>(historyPointF[i].size()) || end_frame == 0) {
                end_frame = historyPointF[i].size();
            }
            for (unsigned long long j = start_frame; j < end_frame; j++) {
                colDatas.append(historyPointF[i][j].y());
            }
            tmpData.append(colDatas);
        }
    }
}

void Save::createHeader(QXlsx::Document &xlsx)
{
    // 写入表头
    QXlsx::Format format;
    format.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    format.setVerticalAlignment(QXlsx::Format::AlignVCenter);

    xlsx.write(1,1,curvedNames.at(0));
    xlsx.write(1,5,curvedNames.at(1));
    xlsx.write(1,35,curvedNames.at(2));
    xlsx.mergeCells(QXlsx::CellRange(1,1,1,4),format);
    xlsx.mergeCells(QXlsx::CellRange(1,5,1,34), format);
    xlsx.mergeCells(QXlsx::CellRange(1,35,1,64),format);
    for (int i=0; i<map_channelNums[curvedNames.at(0)] + 1;i++){
        if (i == 0) {
            xlsx.write(2, 1, "帧", format);
        }
        if (i > 0) {
            QString title = "第" + QString::number(i) + "通道";
            xlsx.write(2, i+1, title, format);
        }
    }

    for(int i=0; i<map_channelNums[curvedNames.at(1)] + 1; i++){
        if (i == 0){
            xlsx.write(2, i + map_channelNums[curvedNames.at(0)] + 2, "帧", format);
        }
        if (i > 0){
            QString title = "第" + QString::number(i) + "通道";
            xlsx.write(2, i + map_channelNums[curvedNames.at(0)] + 2, title, format);
        }
    }

    for(int i=0; i<map_channelNums[curvedNames.at(2)] + 1; i++){
        if (i ==0) {
            xlsx.write(2, i + map_channelNums[curvedNames.at(0)] + map_channelNums[curvedNames.at(1)] + 3, "帧", format);
        }
        if (i > 0){
            QString title = "第" + QString::number(i) + "通道";
            xlsx.write(2, i + map_channelNums[curvedNames.at(0)] + map_channelNums[curvedNames.at(1)] + 3, title, format);
        }
    }
}

void Save::createDir()
{
    QString baseDirStr = "D:/data/";
    QDir basedir(baseDirStr);
    if (!basedir.exists()){
        basedir.mkdir(baseDirStr);
    }
    m_dirName = "D:/data/" + QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QDir dir(m_dirName);
    if(!dir.exists())
    {
        dir.mkdir(m_dirName);
    }
}

void Save::createFileName()
{
    QString strTime = QTime::currentTime().toString("hh-mm-ss");
    m_fileName =m_dirName+"/"+strTime+".xlsx";
}

QString Save::fileName()
{
    return m_fileName;
}
