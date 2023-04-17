
#include "urunitem.h"
#include "global/globalVar.h"

namespace Cafe {
namespace Urun {

UrunItem::UrunItem()
    :MongoCore::Item(Key::Collection.data())
{

}

UrunItem &UrunItem::setUrunAdi(const std::string &urunAdi)
{
    this->append(Key::urunAdi,urunAdi);
    return *this;
}

UrunItem &UrunItem::setKategoriOid(const std::string &kategoriOid)
{
    this->append(Key::kategoriOid,bsoncxx::oid{kategoriOid});
    return *this;
}

bool UrunItem::addUrun(const UrunLanguage &urun)
{
    if( !IsUrunExist(urun.getParaBirimi() ) ){
        this->pushArray(Key::paraBirimiArray.data(),urun.view());
        return true;
    }
    errorOccured("Bu Ürün Zaten Var");
    return false;
}

bool UrunItem::IsUrunExist(const std::string &paraBirimi) const
{
    UrunLanguage item;
    bool exist = false;
    auto val = this->element(Key::paraBirimiArray.data());
    if( val ){
        auto ar = val.value().view().get_array().value;
        for( const auto &urunView : ar ){
            item.setDocumentView(urunView.get_document().view());
            if( item.getParaBirimi() == paraBirimi ){
                exist = true;
                break;
            }
        }
    }
    return exist;
}

bool UrunItem::change(const std::string &paraBirimi, const UrunLanguage &newUrun)
{
    bool changed = false;
    std::vector<UrunLanguage> mNewList;
    auto val = this->element(Key::paraBirimiArray.data());
    UrunLanguage oldItem;

    if( val ){
        auto ar = val.value().view().get_array().value;
        for( const auto &item : ar ){
            oldItem.setDocumentView(item.get_document().view());
            if( oldItem.getParaBirimi() == paraBirimi ){
                changed = true;
            }else{
                mNewList.push_back(oldItem);
            }
        }
    }

    if( changed ){
        this->removeElement(Key::paraBirimiArray);
        mNewList.push_back(newUrun);
        for( const auto &item : mNewList ){
            this->addUrun(item);
        }
    }else{
        errorOccured("Ürün Değiştirilemedi");
    }
    return changed;
}

std::vector<UrunLanguage> UrunItem::getUrunList() const
{
    std::vector<UrunLanguage> mList;
    auto val = this->element(Key::paraBirimiArray.data());
    if( val ){
        auto ar = val.value().view().get_array().value;
        for( const auto &item : ar ){
            UrunLanguage oldItem;
            oldItem.setDocumentView(item.get_document().view());
            mList.push_back(oldItem);
        }
    }
    return mList;
}

UrunLanguage UrunItem::getUrun(const std::string &paraBirimi) const
{
    UrunLanguage item;
    bool exist = false;
    auto val = this->element(Key::paraBirimiArray.data());
    if( val ){
        auto ar = val.value().view().get_array().value;

        for( const auto &urunView : ar ){
            item.setDocumentView(urunView.get_document().view());
            if( item.getParaBirimi() == paraBirimi ){
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

std::string UrunItem::getUrunAdi() const
{
    auto val = this->element( Key::urunAdi.data());
    if( val ){
        return val.value().view().get_string().value.data();
    }
    return "";
}

UrunLanguage::UrunLanguage()
    :MongoCore::Item("")
{

}




UrunLanguage &UrunLanguage::setUrunFiyati(const double urunFiyati)
{
    this->append(Key::ParaObj::urunFiyati,urunFiyati);
    return *this;
}

UrunLanguage &UrunLanguage::setUrunParaBirimi(const std::string &paraBirimi)
{
    this->append(Key::ParaObj::urunParabirimi,paraBirimi);
    return *this;
}

double UrunLanguage::getUrunFiyati() const
{
    auto val = this->element(Key::ParaObj::urunFiyati.data());
    if( val ){
        return val.value().view().get_double().value;
    }
    return 0;
}


std::string UrunLanguage::getParaBirimi() const
{
    auto val = this->element(Key::ParaObj::urunParabirimi.data());
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

