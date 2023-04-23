
#include "adisyonitem.h"
#include "global/globalVar.h"
#include <QDate>
#include <QDateTime>

namespace Adisyon {

AdisyonItem::AdisyonItem()
    :MongoCore::Item("")
{

}

void AdisyonItem::setAdet(const double adet)
{
    this->append(Key::adet.data(),bsoncxx::types::b_double{adet});
}

void AdisyonItem::setUrun(const Cafe::Urun::UrunItem &item)
{
    this->append(Key::urunItem.data(),item.view());
}

Cafe::Urun::UrunItem AdisyonItem::getUrun() const
{
    auto val = this->element(Key::urunItem.data());
    if( val ){
        Cafe::Urun::UrunItem item;
        item.setDocumentView(val.value().view().get_document().value);
        return item;
    }
    return Cafe::Urun::UrunItem();
}

double AdisyonItem::getAdet() const
{
    auto val = this->element(Key::adet.data());
    if( val ){
        return val.value().view().get_double().value;
    }
    return 0;
}


AdisyonListItem::AdisyonListItem()
    :MongoCore::Item(Key::Collection.data())
{
    this->append(Key::epochTime.data(),bsoncxx::types::b_int64{QDateTime::currentMSecsSinceEpoch()});
    this->append(Key::julianDate.data(),bsoncxx::types::b_int64{QDate::currentDate().toJulianDay()});
}

void AdisyonListItem::addAdisyon(const AdisyonItem &item)
{
    std::vector<AdisyonItem> list;
    auto val = this->element(Key::urunItem.data());
    if( val ){
        auto ar = val.value().view().get_array().value;
        bool exist = false;
        for( const auto &__item : ar ){
            AdisyonItem item_;
            item_.setDocumentView(__item.get_document().view());
            if( item_.getUrun().getUrunAdi() == item.getUrun().getUrunAdi() ){
                if( (item_.getAdet()+item.getAdet()) >= 0 ){
                    item_.setAdet(item_.getAdet()+item.getAdet());
                }
                exist = true;
            }
            list.push_back(item_);
        }
        if( !exist ){
            list.push_back(item);
        }

        this->removeElement(Key::urunItem);
        for( auto &adisyonItem : list ){
            this->pushArray(Key::urunItem.data(),adisyonItem.view());
        }
    }else{
        this->pushArray(Key::urunItem.data(),item.view());
    }
}

void AdisyonListItem::changeAdisyon(const AdisyonItem &item)
{
    std::vector<AdisyonItem> list;
    auto val = this->element(Key::urunItem.data());
    if( val ){
        auto ar = val.value().view().get_array().value;
        bool exist = false;
        for( const auto &__item : ar ){
            AdisyonItem item_;
            item_.setDocumentView(__item.get_document().view());
            if( item_.getUrun().getUrunAdi() == item.getUrun().getUrunAdi() ){
                if( item.getAdet() >= 0 ){
                    item_.setAdet(item.getAdet());
                }
                exist = true;
            }
            list.push_back(item_);
        }
        if( !exist ){
            list.push_back(item);
        }

        this->removeElement(Key::urunItem);
        for( auto &adisyonItem : list ){
            this->pushArray(Key::urunItem.data(),adisyonItem.view());
        }
    }else{
        this->pushArray(Key::urunItem.data(),item.view());
    }
}

void AdisyonListItem::removeAdisyon(const AdisyonItem &item)
{
    std::vector<AdisyonItem> list;
    auto val = this->element(Key::urunItem.data());
    if( val ){
        auto ar = val.value().view().get_array().value;
        for( const auto &__item : ar ){
            AdisyonItem item_;
            item_.setDocumentView(__item.get_document().view());
            if( item_.getUrun().oid() == item.getUrun().oid() ){

            }else{
                list.push_back(item_);
            }
        }

        this->removeElement(Key::urunItem);
        for( auto &adisyonItem : list ){
            this->pushArray(Key::urunItem.data(),adisyonItem.view());
        }
    }else{
        this->pushArray(Key::urunItem.data(),item.view());
    }
}

int AdisyonListItem::adisyonSize() const
{
    auto val = this->element(Key::urunItem.data());
    if( val ){
        auto ar = val.value().view().get_array().value;
        return std::distance(ar.begin(),ar.end());
    }
    return 0;
}

AdisyonItem AdisyonListItem::operator[](const int index)
{
    auto val = this->element(Key::urunItem.data());
    if( val ){
        auto ar = val.value().view().get_array().value;
        auto item = ar.find(index);
        AdisyonItem item_;
        item_.setDocumentView(item->get_document().view());
        return item_;
    }
    return AdisyonItem();
}

AdisyonItem AdisyonListItem::adisyon(const int index)
{
    auto val = this->element(Key::urunItem.data());
    if( val ){
        auto ar = val.value().view().get_array().value;
        auto item = ar.find(index);
        AdisyonItem item_;
        item_.setDocumentView(item->get_document().view());
        return item_;
    }
    return AdisyonItem();
}

std::optional<AdisyonItem> AdisyonListItem::adisyon(const std::string urunName)
{
    AdisyonItem item_;
    auto val = this->element(Key::urunItem.data());
    if( val ){
        auto ar = val.value().view().get_array().value;
        for( const auto &__item : ar ){
            item_.setDocumentView(__item.get_document().view());
            if( item_.getUrun().getUrunAdi() == urunName ){

                break;
            }
        }
        if( !item_.view().empty() ){
            return item_;
        }
    }
    return std::nullopt;
}

AdisyonListManager::AdisyonListManager()
    :MongoCore::ListItem<AdisyonListItem>(GlobarVar::GlobalDB::DB())
{

}

} // namespace Adisyon



void Adisyon::AdisyonListManager::errorOccured(const std::string &errorText)
{
}

void Adisyon::AdisyonListManager::onList(const std::vector<AdisyonListItem> &mlist)
{
}
