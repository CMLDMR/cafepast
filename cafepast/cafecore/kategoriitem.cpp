
#include "kategoriitem.h"
#include "global/globalVar.h"

namespace Cafe {
namespace Kategori {

KategoriItem::KategoriItem()
    :MongoCore::Item(Key::Collection.data())
{

}

KategoriItem &KategoriItem::setName(const std::string &kategoriName)
{
    this->append(Key::kategoriName,kategoriName);
    return *this;
}

std::string KategoriItem::getKategoriName() const
{
    auto val = this->element(Key::kategoriName.data());
    if( val ){
        return val.value().view().get_string().value.data();
    }
    return "";
}

KategoriItem &KategoriItem::operator=(const KategoriItem &other)
{
    this->setDocumentView(other.view());
    return *this;
}

KategoriManager::KategoriManager()
    :MongoCore::ListItem<KategoriItem>(GlobarVar::GlobalDB::DB())
{

}

void KategoriManager::onList(const std::vector<KategoriItem> &mList)
{


    for( const auto &item : mList ){
        std::cout << bsoncxx::to_json(item.view()) << "\n";
    }

}

}

} // namespace Cafe

