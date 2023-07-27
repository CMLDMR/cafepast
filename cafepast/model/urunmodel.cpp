
#include "urunmodel.h"
#include "cafecore/paraitem.h"
#include "cafecore/languageitem.h"

namespace Urun {

UrunModel::UrunModel(QObject *parent)
    : QAbstractItemModel{parent}
{
    Cafe::ParaBirimi::ParaManager::instance()->UpdateList();

}

} // namespace Urun



void Urun::UrunModel::errorOccured(const std::string &errorText)
{
}

void Urun::UrunModel::onList(const std::vector<Cafe::Urun::UrunItem> &mList)
{
    beginResetModel();
    this->mList = mList;
    endResetModel();
}

QModelIndex Urun::UrunModel::index(int row, int column, const QModelIndex &parent) const
{
    return createIndex(row,column);
}

QModelIndex Urun::UrunModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

int Urun::UrunModel::rowCount(const QModelIndex &parent) const
{
    return static_cast<int>(this->mList.size());
}

int Urun::UrunModel::columnCount(const QModelIndex &parent) const
{
    return Cafe::ParaBirimi::ParaManager::instance()->List().size()+1;
}

QVariant Urun::UrunModel::data(const QModelIndex &index, int role) const
{
    if( !index.isValid() ){
        return "invalid index";
    }

    if( role == Qt::DisplayRole ){
        if( index.row() >= mList.size() ){
            return "out of range";
        }else{
            if( index.column() == 0 ){
                return TR(mList.at(index.row()).getUrunAdi().c_str());
            }else{
                return this->getSubLangFiyat(index.column(),mList.at(index.row()));
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



QVariant Urun::UrunModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    auto list = Cafe::ParaBirimi::ParaManager::instance()->List();

    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {

            if( section == 0 ){
                return TR("Ürün Adı");
            }else{

                QVariant var;
                for( int i = 0 ; i < list.size() ; i++ ){
                    auto item = list.at(i);
                    if( i == section-1 ){
                        var = QVariant{item.getParaName().c_str()};
                        break;
                    }
                }
                return var;
            }
        }
    }
    return QVariant();
}

double Urun::UrunModel::price(const int &row, const std::string &paraBirimi) const
{
    if( row < 0 || row >= mList.size() ) return 0.0;
    return this->mList.at(row).getUrun(paraBirimi).getUrunFiyati();
}

QString Urun::UrunModel::getSubLangFiyat(const int HeaderSection,const Cafe::Urun::UrunItem &item) const
{
    auto paraBirimStr = this->headerData(HeaderSection,Qt::Horizontal,Qt::DisplayRole).toString();
    auto urun = item.getUrun(paraBirimStr.toStdString());
    return QString::number(urun.getUrunFiyati()) + QString(" ") + urun.getParaBirimi().c_str();
}
