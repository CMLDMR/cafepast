
#ifndef CAFE_KATEGORIITEM_H
#define CAFE_KATEGORIITEM_H

#include "mongocore/item.h"
#include <mongocore/listitem.h>

namespace Cafe {

namespace Kategori{

namespace Key {
inline const std::string_view Collection{"Kategoriler"};
inline const std::string_view kategoriName{"KategoriAdi"};


}

class KategoriItem : public MongoCore::Item
{
public:
    KategoriItem();

    KategoriItem &setName( const std::string &kategoriName);

    std::string getKategoriName() const;

    KategoriItem &operator=( const KategoriItem &other);
};



 class KategoriManager : public MongoCore::ListItem<KategoriItem>
{
public:
    explicit KategoriManager();
    virtual ~KategoriManager(){}

    virtual void onList( const std::vector<KategoriItem> &mList ) override;
};

}





} // namespace Cafe

#endif // CAFE_KATEGORIITEM_H
