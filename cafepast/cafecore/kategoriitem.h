
#ifndef CAFE_KATEGORIITEM_H
#define CAFE_KATEGORIITEM_H

#include "mongocore/item.h"
#include <mongocore/listitem.h>

namespace Cafe {

namespace Kategori{

namespace Key {
inline const std::string_view Collection{"Kategoriler"};


}

class KategoriItem : public MongoCore::Item
{
public:
    KategoriItem();
};



 class KategoriManager : public MongoCore::ListItem<KategoriItem>
{
public:
    KategoriManager();


    virtual void onList( const std::vector<KategoriItem> &mList ) override;
};

}





} // namespace Cafe

#endif // CAFE_KATEGORIITEM_H
