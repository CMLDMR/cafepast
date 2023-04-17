
#ifndef URUN_URUNMODEL_H
#define URUN_URUNMODEL_H

#include <QAbstractItemModel>

#include <QObject>

#include "cafecore/urunitem.h"


namespace Urun {

class UrunModel : public QAbstractItemModel, public Cafe::Urun::UrunManager
{
    Q_OBJECT
public:
    explicit UrunModel(QObject *parent = nullptr);

    // DB interface
public:
    virtual void errorOccured(const std::string &errorText) override;

    // UrunManager interface
public:
    virtual void onList(const std::vector<Cafe::Urun::UrunItem> &mList) override;

    // QAbstractItemModel interface
public:
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    virtual QModelIndex parent(const QModelIndex &child) const override;
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    // QAbstractItemModel interface
public:
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

private:
    std::vector<Cafe::Urun::UrunItem> mList;

    QString getSubLangFiyat(const int HeaderSection , const Cafe::Urun::UrunItem &item ) const;
};

} // namespace Urun

#endif // URUN_URUNMODEL_H
