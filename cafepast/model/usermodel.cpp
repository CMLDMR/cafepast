#include "usermodel.h"

namespace Cafe {
namespace User {

UserModel::UserModel()
{
    this->UpdateList();
}

} // namespace User
} // namespace Cafe


int Cafe::User::UserModel::rowCount(const QModelIndex &parent) const
{
    return mList.size();
}

int Cafe::User::UserModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant Cafe::User::UserModel::data(const QModelIndex &index, int role) const
{
    if( !index.isValid() ) return "invalid index";

    if( role == Qt::DisplayRole ){

        if( index.column() == 0 ) return mList.at(index.row()).getAdSoyad().c_str();

        if( index.column() == 1 ) return mList.at(index.row()).getUserName().c_str();

    }

    return QVariant{};
}

QVariant Cafe::User::UserModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if( role == Qt::DisplayRole ){
        if( orientation == Qt::Horizontal ){
            if( section == 0 ) return "AdSoyad";
            if( section == 1 ) return "Kullanıcı Adı";
        }
    }


    return QVariant{};

}

void Cafe::User::UserModel::onList(const std::vector<UserItem> &mList)
{
    beginResetModel();
    this->mList = mList;
    endResetModel();
}
