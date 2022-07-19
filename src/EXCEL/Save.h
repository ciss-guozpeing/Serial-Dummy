#ifndef SAVE_H
#define SAVE_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QDateTime>
#include <QFileDialog>
#include <QTextStream>
#include <QIODevice>
#include <QString>

#include "xlsxdocument.h"
//#include "xlsxworksheet.h"
//#include "xlsxcellrange.h"
#include "xlsxformat.h"
//#include "xlsxcell.h"
#include "xlsxcellrange.h"

namespace EXCEL
{
    class Save : public QObject
    {
        Q_OBJECT
    private:
        QString m_dirName;
        QString m_fileName;
        void createDir();
        void createFileName();
        void addTmpData(QList<QList<double>> &tmpData, int channelNum,
                        unsigned long long start_frame, unsigned long long end_frame,
                        QVector<QVector<QPointF>> historyPointF);
        QString fileName();
        QList<QString> curvedNames = QList<QString>() << "室内温度曲线" << "热功率曲线" << "体表温度曲线";

        QMap<QString, int> map_channelNums = {{"室内温度曲线", 3}, {"热功率曲线", 29}, {"体表温度曲线", 29}};
        int m_lastframe = 0;
        int sum_channelNums = map_channelNums[curvedNames[0]] + map_channelNums[curvedNames[1]] + map_channelNums[curvedNames[2]];
        void createHeader(QXlsx::Document &xlsx);
    public:
        Save();
        static Save *getInstance();

        Q_INVOKABLE void autoSave();

    signals:

    };
}


#endif // SAVE_H
