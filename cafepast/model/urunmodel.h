
#ifndef URUN_URUNMODEL_H
#define URUN_URUNMODEL_H

#include <QAbstractItemModel>

#include <QObject>


namespace Urun {

class UrunModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit UrunModel(QObject *parent = nullptr);
};

} // namespace Urun

#endif // URUN_URUNMODEL_H
