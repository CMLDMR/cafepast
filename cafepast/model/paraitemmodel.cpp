
#include "paraitemmodel.h"

namespace ParaBirimi {

ParaItemModel::ParaItemModel(QObject *parent)
    : QAbstractListModel{parent}
{
    this->UpdateList();
}

} // namespace ParaBirimi



void ParaBirimi::ParaItemModel::errorOccured(const std::string &errorText)
{
}

int ParaBirimi::ParaItemModel::rowCount(const QModelIndex &parent) const
{
    return mList.size();
}

QVariant ParaBirimi::ParaItemModel::data(const QModelIndex &index, int role) const
{
    if( !index.isValid() ){
        return "invalid index";
    }
    if( role == Qt::DisplayRole ){
        if( index.row() >= mList.size() ){
            return "out of range";
        }else{
            return mList.at(index.row()).getParaName().c_str();
        }
    }

    if( role == Qt::UserRole+1 ){
        if( index.row() >= mList.size() ){
            return "";
        }else{
            return mList.at(index.row()).oid().value().to_string().c_str();
        }
    }
    return QVariant{};
}

void ParaBirimi::ParaItemModel::onList(const std::vector<Cafe::ParaBirimi::ParaItem> &mList)
{
    beginResetModel();
    this->mList = mList;
    endResetModel();
}
