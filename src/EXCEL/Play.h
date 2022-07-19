#ifndef PLAY_H
#define PLAY_H
#include <QFile>
#include <QJsonDocument>
#include <QMap>
#include <QObject>
#include <QSet>
#include <QStringList>
#include <QTimer>
#include <QIODevice>
#include <QStandardPaths>
#include <QDateTime>
#include <QTextStream>

namespace EXCEL{
    class Play: public QObject
    {
    public:
        Play();
        static Play *getInstance();
    };
}


#endif // PLAY_H
