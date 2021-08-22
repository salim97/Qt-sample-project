#ifndef MYDATAMODEL_H
#define MYDATAMODEL_H

#include <QObject>

class MyDataModel : public QObject
{
    Q_OBJECT
public:
    explicit MyDataModel(QObject *parent = nullptr);

    //header
    QString label ;
    QString transducer;
    QString units; // TODO: convert QString to enum
    double min, max;
    int dmin, dmax;
    QString preFilter;
    int smp_rec;
    QString reserved;

    //body
//    QMap<float, float> data;

    QString toJSON()
    {
        // TODO: model to JSON
        return QString();
    }
    bool fromJSON(QString json)
    {
        // TODO: model from JSON
        Q_UNUSED(json)
        return true;
    }
};

#endif // MYDATAMODEL_H
