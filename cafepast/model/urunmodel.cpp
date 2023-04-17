
#include "urunmodel.h"
#include "cafecore/languageitem.h"

namespace Urun {

UrunModel::UrunModel(QObject *parent)
    : QAbstractItemModel{parent}
{
    Cafe::Language::LanguageManager::instance()->UpdateList();

}

} // namespace Urun



void Urun::UrunModel::errorOccured(const std::string &errorText)
{
}

void Urun::UrunModel::onList(const std::vector<Cafe::Urun::UrunItem> &mList)
{
}

QModelIndex Urun::UrunModel::index(int row, int column, const QModelIndex &parent) const
{
    return QModelIndex();
}

QModelIndex Urun::UrunModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

int Urun::UrunModel::rowCount(const QModelIndex &parent) const
{
    return 5;
}

int Urun::UrunModel::columnCount(const QModelIndex &parent) const
{
    return Cafe::Language::LanguageManager::instance()->List().size();
}

QVariant Urun::UrunModel::data(const QModelIndex &index, int role) const
{
    return QVariant{};
}



QVariant Urun::UrunModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    auto list = Cafe::Language::LanguageManager::instance()->List();

    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {

            if( section == 0 ){
                return TR("Ürün Adı");
            }else{

                QVariant var;
                for( int i = 1 ; i < list.size() ; i++ ){
                    auto item = list.at(i);
                    if( i == section ){
                        var = QVariant{item.getLanguageName().c_str()};
                        break;
                    }
                }
                return var;
            }
        }
    }
    return QVariant();
}
