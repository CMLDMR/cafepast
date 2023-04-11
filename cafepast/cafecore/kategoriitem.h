
#ifndef CAFE_KATEGORIITEM_H
#define CAFE_KATEGORIITEM_H

#include "mongocore/item.h"


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

}





} // namespace Cafe

#endif // CAFE_KATEGORIITEM_H
