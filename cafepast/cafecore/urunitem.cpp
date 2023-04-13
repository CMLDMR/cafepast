
#include "urunitem.h"

namespace Cafe {
namespace Urun {

UrunItem::UrunItem()
    :MongoCore::Item(Key::Collection.data())
{

}

UrunItem &UrunItem::addUrun(const UrunLanguage &urun)
{
    this->pushArray(Key::language.data(),urun);
    return *this;
}

UrunLanguage UrunItem::getUrun(const std::string &language)
{
    UrunLanguage item;
    bool exist = false;
    auto val = this->element(Key::language.data());
    if( val ){
        auto ar = val.value().view().get_array().value;

        for( const auto &urunView : ar ){
            item.setDocumentView(urunView.get_document().view());
            if( item.getLanguage() == language ){
                exist = true;
                break;
            }
        }
    }
    if( exist ){
        return item;
    }else{
        return UrunLanguage();
    }
}

UrunLanguage::UrunLanguage()
    :MongoCore::Item("")
{

}

UrunLanguage &UrunLanguage::setLanguage(const std::string &language)
{
    this->append(Key::language,language);
    return *this;
}

UrunLanguage &UrunLanguage::setUrunAdi(const std::string &urunAdi)
{
    this->append(Key::LANG::urunAdi,urunAdi);
    return *this;
}

std::string UrunLanguage::getLanguage() const
{
    auto val = this->element(Key::LANG::lang.data());
    if( val ){
        return val.value().view().get_string().value.data();
    }
    return "";
}

UrunManager::UrunManager()
    :MongoCore::ListItem<UrunItem>(GlobarVar::GlobalDB::DB())
{

}

void UrunManager::onList(const std::vector<UrunItem> &mList)
{

}

} // namespace Urun
} // namespace Cafe

