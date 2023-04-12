
#include "kategorilistmodel.h"

namespace Kategori {

KategoriListModel::KategoriListModel(QObject *parent)
    : QAbstractListModel{parent}
{

    this->setLimit(1000);

    this->UpdateList();

}


int Kategori::KategoriListModel::rowCount(const QModelIndex &parent) const
{
    return mList.size();
}

QVariant Kategori::KategoriListModel::data(const QModelIndex &index, int role) const
{
    if( !index.isValid() ){
        return "invalid index";
    }
    if( role == Qt::DisplayRole ){
        if( index.row() >= mList.size() ){
            return "out of range";
        }else{
            return mList.at(index.row()).getKategoriName().c_str();
        }
    }
    return QVariant{};
}


void KategoriListModel::setList(const std::vector<Cafe::Kategori::KategoriItem> &newList)
{
    beginResetModel();
    mList = newList;
    endResetModel();
}

void KategoriListModel::onList(const std::vector<Cafe::Kategori::KategoriItem> &mList)
{
    beginResetModel();
    this->mList = mList;
    endResetModel();

}

void KategoriListModel::updateKategoriList()
{
    this->UpdateList();
}

} // namespace Kategori

