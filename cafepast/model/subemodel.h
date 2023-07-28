#ifndef CAFE_SUBE_SUBEMODEL_H
#define CAFE_SUBE_SUBEMODEL_H

#include <QObject>
#include <QAbstractListModel>

#include "cafecore/subeitem.h"

namespace Cafe {
namespace Sube {

class SubeModel : public QAbstractListModel, public Cafe::Sube::SubeManager
{
    Q_OBJECT
public:
    SubeModel();

    // DB interface
public:
    virtual void errorOccured(const std::string &errorText) override;

    // SubeManager interface
public:
    virtual void onList(const std::vector<SubeItem> &mList) override;

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

private:
    std::vector<Cafe::Sube::SubeItem> mList;


    // QAbstractItemModel interface
public:
    virtual int columnCount(const QModelIndex &parent) const override;
    std::vector<Cafe::Sube::SubeItem> list() const;
};

} // namespace Sube
} // namespace Cafe

#endif // CAFE_SUBE_SUBEMODEL_H
