
#include "languagemodel.h"

namespace Language {

LanguageModel::LanguageModel(QObject *parent)
    : QAbstractListModel{parent}
{
    this->UpdateList();
}

} // namespace Language



void Language::LanguageModel::errorOccured(const std::string &errorText)
{
}

int Language::LanguageModel::rowCount(const QModelIndex &parent) const
{
    return mList.size();
}

QVariant Language::LanguageModel::data(const QModelIndex &index, int role) const
{
    if( !index.isValid() ){
        return "invalid index";
    }
    if( role == Qt::DisplayRole ){
        if( index.row() >= mList.size() ){
            return "out of range";
        }else{
            return QString{mList.at(index.row()).getLanguageName().c_str()}+" | "+QString{mList.at(index.row()).getShortName().c_str()};
        }
    }

    if( role == Role::oid ){
        if( index.row() >= mList.size() ){
            return "";
        }else{
            return mList.at(index.row()).oid().value().to_string().c_str();
        }
    }
    if( role == Role::shortName ){
        if( index.row() >= mList.size() ){
            return "";
        }else{
            return QString{mList.at(index.row()).getShortName().c_str()};
        }
    }
    if( role == Role::langName ){
        if( index.row() >= mList.size() ){
            return "";
        }else{
            return QString{mList.at(index.row()).getLanguageName().c_str()};
        }
    }
    return QVariant{};
}

void Language::LanguageModel::onList(const std::vector<Cafe::Language::LanguageItem> &mList)
{
    beginResetModel();
    this->mList = mList;
    endResetModel();
}
