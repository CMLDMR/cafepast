#include "subeitem.h"
#include "global/globalVar.h"

namespace Cafe {
namespace Sube {

SubeItem::SubeItem()
    :MongoCore::Item(Key::Collection.data())
{

}

SubeItem &SubeItem::setSubeAdi(const std::string &subeAdi)
{
    this->append(Key::subeAdi,subeAdi);
    return *this;
}

SubeItem &SubeItem::setSubeAdresi(const std::string &subeAdresi)
{
    this->append(Key::subeAdresi,subeAdresi);
    return *this;
}

SubeItem &SubeItem::setSubeTelefon(const std::string &subeTelefon)
{
    this->append(Key::subeTelefon,subeTelefon);
    return *this;
}

std::string SubeItem::getSubeAdi() const
{
    auto val = this->element(Key::subeAdi.data());
    if( val ){
        return val.value().view().get_string().value.data();
    }
    return "";
}

std::string SubeItem::getSubeAdresi() const
{
    auto val = this->element(Key::subeAdresi.data());
    if( val ){
        return val.value().view().get_string().value.data();
    }
    return "";
}

std::string SubeItem::getSubeTelefon() const
{
    auto val = this->element(Key::subeTelefon.data());
    if( val ){
        return val.value().view().get_string().value.data();
    }
    return "";
}



SubeManager::SubeManager()
    :MongoCore::ListItem<SubeItem>(GlobarVar::GlobalDB::DB())
{

}

void SubeManager::onList(const std::vector<SubeItem> &mList)
{

}

} // namespace Sube
} // namespace Cafe
