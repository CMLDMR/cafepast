
#include "languagetextmodel.h"

namespace Language {

LanguageTextModel::LanguageTextModel(QObject *parent)
    : QAbstractTableModel{parent}
{
    this->setLimit(10000);
    //    this->UpdateList();
}

std::vector<Cafe::Language::TextItem> LanguageTextModel::list() const
{
    return mList;
}

} // namespace Language



void Language::LanguageTextModel::errorOccured(const std::string &errorText)
{
}

void Language::LanguageTextModel::onList(const std::vector<Cafe::Language::TextItem> &mlist)
{
    beginResetModel();
    this->mList = mlist;
    endResetModel();
}

QModelIndex Language::LanguageTextModel::index(int row, int column, const QModelIndex &parent) const
{
    return createIndex(row,column);
}

QModelIndex Language::LanguageTextModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

int Language::LanguageTextModel::rowCount(const QModelIndex &parent) const
{
    return mList.size();
}

int Language::LanguageTextModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant Language::LanguageTextModel::data(const QModelIndex &index, int role) const
{
    if( !index.isValid() ){
        return "invalid index";
    }

    if( role == Qt::DisplayRole ){
        if( index.row() >= mList.size() ){
            return "out of range";
        }else{
            switch (index.column()) {
            case 0:
                return QString{mList.at(index.row()).getText().c_str()};
                break;
            case 1:
                return QString{mList.at(index.row()).getLang().c_str()};
                break;
            case 2:
                return QString{mList.at(index.row()).getDestText().c_str()};
                break;
            default:
                break;
            }
        }
    }
    return QVariant{};
}



QVariant Language::LanguageTextModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case 0:
                return TR("Sözcük");
            case 1:
                return TR("Dil");
            case 2:
                return TR("Çeviri");
            }
        }
    }
    return QVariant();
}
