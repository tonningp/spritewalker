#ifndef SEQUENTIALGUID_H
#define SEQUENTIALGUID_H

#include <QObject>
#include <QUuid>
#include <QByteArray>
#include <QDateTime>
#include <QDataStream>
#include <QTime>


class SequentialGUID : public QObject
{
    Q_OBJECT
public:
    explicit SequentialGUID(QObject *parent = 0);

    enum SequentialGUIDType {
        SequentialAsString = 0,
        SequentialAsBinary = 1,
        SequentialAtEnd = 2
    };

    static QUuid GetSequentialGUID(SequentialGUIDType guid_type);


signals:

public slots:

private:
    static void InitRand();
    static int randInt(int low, int high);

    static bool rand_init;
};

#endif // SEQUENTIALGUID_H
