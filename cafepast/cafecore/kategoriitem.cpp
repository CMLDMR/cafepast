
#include "kategoriitem.h"
#include "global/globalVar.h"

namespace Cafe {
namespace Kategori {

KategoriItem::KategoriItem()
    :MongoCore::Item(Key::Collection.data())
{

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

