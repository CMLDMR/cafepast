
#ifndef PARABIRIMI_PARAITEMMODEL_H
#define PARABIRIMI_PARAITEMMODEL_H

#include <QAbstractListModel>

#include <QObject>

#include "cafecore/paraitem.h"

namespace ParaBirimi {

class ParaItemModel : public QAbstractListModel, public Cafe::ParaBirimi::ParaManager
{
    Q_OBJECT
public:
    explicit ParaItemModel(QObject *parent = nullptr);


    // DB interface
public:
    virtual void errorOccured(const std::string &errorText) override;

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    // ParaManager interface
public:
    virtual void onList(const std::vector<Cafe::ParaBirimi::ParaItem> &mList) override;


private:
    std::vector<Cafe::ParaBirimi::ParaItem> mList;

};

} // namespace ParaBirimi

#endif // PARABIRIMI_PARAITEMMODEL_H
