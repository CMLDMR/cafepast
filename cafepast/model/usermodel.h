#ifndef CAFE_USER_USERMODEL_H
#define CAFE_USER_USERMODEL_H

#include <QObject>
#include <QAbstractListModel>

#include "cafecore/useritem.h"

namespace Cafe {
namespace User {

class UserModel : public QAbstractListModel, public Cafe::User::UserManager
{
    Q_OBJECT
public:
    UserModel();

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    // UserManager interface
public:
    virtual void onList(const std::vector<UserItem> &mList) override;

private:
    std::vector<UserItem> mList;

};

} // namespace User
} // namespace Cafe

#endif // CAFE_USER_USERMODEL_H
