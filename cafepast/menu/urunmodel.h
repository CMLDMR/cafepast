
#ifndef MENU_URUNMODEL_H
#define MENU_URUNMODEL_H

#include <QAbstractItemModel>

#include <QObject>
#include "cafecore/urunitem.h"


namespace Menu {

class UrunModel : public QAbstractItemModel, public Cafe::Urun::UrunManager
{
    Q_OBJECT
public:
    explicit UrunModel(QObject *parent = nullptr);

    // DB interface
public:
    virtual void errorOccured(const std::string &errorText) override;

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    // UrunManager interface
public:
    virtual void onList(const std::vector<Cafe::Urun::UrunItem> &mList) override;


private:
    std::vector<Cafe::Urun::UrunItem> mList;
    std::string mCurrentParaBirimi;

    // QAbstractItemModel interface
public:
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    virtual QModelIndex parent(const QModelIndex &child) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    void setCurrentParaBirimi(const std::string &newCurrentParaBirimi);
};

} // namespace Menu

#endif // MENU_URUNMODEL_H
