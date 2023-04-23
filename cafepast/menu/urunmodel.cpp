
#include "urunmodel.h"
#include "cafecore/paraitem.h"
#include "cafecore/languageitem.h"
#include "global/informationwidget.h"
#include "global/globalVar.h"


namespace Menu {

void UrunModel::setCurrentParaBirimi(const std::string &newCurrentParaBirimi)
{
    mCurrentParaBirimi = newCurrentParaBirimi;
    this->UpdateList();
}



UrunModel::UrunModel(QObject *parent)
    : QAbstractItemModel{parent}
{
    mCurrentParaBirimi = GlobarVar::LocalConfiguration::instance()->getCurrentParaBirimi();
}

} // namespace Menu



void Menu::UrunModel::errorOccured(const std::string &errorText)
{
    GlobarVar::InformationWidget::instance()->setInformation(errorText.c_str(),GlobarVar::InformationWidget::Warn);
}

int Menu::UrunModel::rowCount(const QModelIndex &parent) const
{
    return mList.size();
}

QVariant Menu::UrunModel::data(const QModelIndex &index, int role) const
{
    if( !index.isValid() ){
        return QVariant();
    }

    if( role == Qt::UserRole+1 ){
        return QVariant{mList[index.row()].oid().value().to_string().c_str()};
    }

    if( role == Qt::DisplayRole ){
        if( index.column()  == 0 ){
            return TR(mList.at(index.row()).getUrunAdi().c_str());
        }

        if( index.column()  == 1 ){
            auto uList = mList[index.row()].getUrunList();

            double price = 0 ;

            for( const auto &item : uList ){
                if( item.getParaBirimi() == mCurrentParaBirimi ){
                    price = item.getUrunFiyati();
                    break;
                }
            }

            return QVariant{price};
        }
    }

    return QVariant();

}

QVariant Menu::UrunModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    auto list = Cafe::ParaBirimi::ParaManager::instance()->List();

    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {

            if( section == 0 ){
                return QVariant{TR("Ürün Adı")};
            }
            if( section == 1 ){
                return QVariant{TR("Ürün Fiyatı")};
            }
        }
    }
    return QVariant();
}

void Menu::UrunModel::onList(const std::vector<Cafe::Urun::UrunItem> &mList)
{
    beginResetModel();
    this->mList = mList;
    endResetModel();
}


QModelIndex Menu::UrunModel::index(int row, int column, const QModelIndex &parent) const
{
    return createIndex(row,column);
}

QModelIndex Menu::UrunModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

int Menu::UrunModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}
