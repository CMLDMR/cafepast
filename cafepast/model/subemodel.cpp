#include "subemodel.h"

#include "cafecore/languageitem.h"
#include "global/informationwidget.h"

namespace Cafe {
namespace Sube {

std::vector<Cafe::Sube::SubeItem> SubeModel::list() const
{
    return mList;
}



SubeModel::SubeModel()
{

    this->UpdateList();

}

} // namespace Sube
} // namespace Cafe


void Cafe::Sube::SubeModel::errorOccured(const std::string &errorText)
{
    GlobarVar::InformationWidget::instance()->setInformation(errorText.c_str(),GlobarVar::InformationWidget::Type::Warn);
}

void Cafe::Sube::SubeModel::onList(const std::vector<SubeItem> &mList)
{
    beginResetModel();
    this->mList = mList;
    endResetModel();

}


int Cafe::Sube::SubeModel::rowCount(const QModelIndex &parent) const
{
    return static_cast<int>(this->mList.size());
}

QVariant Cafe::Sube::SubeModel::data(const QModelIndex &index, int role) const
{
    if( !index.isValid() ){
        return "invalid index";
    }

    if( role == Qt::DisplayRole ){
        if( index.row() >= mList.size() ){
            return "out of range";
        }else{
            if( index.column() == 0 ){
                return TR(mList.at(index.row()).getSubeAdi().c_str());
            }else if( index.column() == 1 ){
                return mList.at(index.row()).getSubeTelefon().c_str();
            }else{
                return mList.at(index.row()).getSubeAdresi().c_str();
            }
        }
    }

    if( role == Qt::UserRole+1 ){
        if( index.row() >= mList.size() ){
            return "out of range";
        }else{
            return QString{mList.at(index.row()).oid().value().to_string().c_str()};
        }
    }
    return QVariant{};
}

QVariant Cafe::Sube::SubeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {

            if( section == 0 ){
                return TR("Şube Adı");
            }else if( section == 1){
                return TR("Telefon");
            }else{
                return TR("Adres");
            }
        }
    }
    return QVariant();
}



int Cafe::Sube::SubeModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}
