
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
    this->pushArray(Key::urunItem.data(),item.view());
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
