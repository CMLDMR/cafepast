
#include "adisyonmodel.h"
#include "cafecore/languageitem.h"

namespace Adisyon {


AdisyonModel::AdisyonModel(QObject *parent)
    : QAbstractTableModel(parent)
{


    mUrunList = new AdisyonListItem();

    mAdisyonListManager = new AdisyonListManager();
}

void AdisyonModel::addUrun(const Cafe::Urun::UrunItem &urunItem)
{
    beginResetModel();

    AdisyonItem item;
    item.setAdet(1);
    item.setUrun(urunItem);
    mUrunList->addAdisyon(item);
    endResetModel();

}

void AdisyonModel::reduceUrun(const Cafe::Urun::UrunItem &urunItem)
{

    AdisyonItem item;
    item.setAdet(-1);
    item.setUrun(urunItem);
    mUrunList->addAdisyon(item);
    endResetModel();
}

void AdisyonModel::changeUrun(const Cafe::Urun::UrunItem &urunItem, const double &adet)
{
    AdisyonItem item;
    item.setAdet(adet);
    item.setUrun(urunItem);
    mUrunList->changeAdisyon(item);
    endResetModel();
}

void AdisyonModel::removeUrun(const Cafe::Urun::UrunItem &urunItem)
{
    AdisyonItem item;
    item.setAdet(0);
    item.setUrun(urunItem);
    mUrunList->removeAdisyon(item);
    endResetModel();
}

QVariant AdisyonModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case 0:
                return TR("Ürün Adı");
            case 1:
                return TR("Fiyat");
            case 2:
                return TR("Adet");
            case 3:
                return TR("Toplam");
            }
        }
    }
    return QVariant();
}

int AdisyonModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return mUrunList->adisyonSize();
    // FIXME: Implement me!
}

int AdisyonModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 4;
    // FIXME: Implement me!
}

QVariant AdisyonModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if( role == Qt::DisplayRole ){

        switch (index.column()) {
        case 0:
            return mUrunList->adisyon(index.row()).getUrun().getUrunAdi().c_str();
            break;
        case 1:
            return mUrunList->adisyon(index.row()).getUrun().getUrun(mCurrentParaBirimi.toStdString()).getUrunFiyati();
            break;
        case 2:
            return mUrunList->adisyon(index.row()).getAdet();
            break;
        case 3:
            return mUrunList->adisyon(index.row()).getAdet()*mUrunList->adisyon(index.row()).getUrun().getUrun(mCurrentParaBirimi.toStdString()).getUrunFiyati();
            break;
        default:
            break;
        }

    }

    if( role == Role::Oid ){
        return mUrunList->adisyon(index.row()).getUrun().oid().value().to_string().c_str();
    }

    // FIXME: Implement me!
    return QVariant();
}

void AdisyonModel::setCurrentParaBirimi(const QString &newCurrentParaBirimi)
{
    beginResetModel();
    mCurrentParaBirimi = newCurrentParaBirimi;
    endResetModel();
}

double AdisyonModel::getTotalPrice() const
{

    double totalPrice = 0;
    for( int i = 0 ; i < this->rowCount() ; i++ ){
        totalPrice += this->index(i,1).data(Qt::DisplayRole).toDouble() * this->index(i,2).data(Qt::DisplayRole).toDouble();
    }
    return totalPrice;
}

} // namespace Adisyon

