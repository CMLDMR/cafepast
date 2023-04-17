
#ifndef CAFE_URUN_URUNITEM_H
#define CAFE_URUN_URUNITEM_H


#include <mongocore/listitem.h>

namespace Cafe {
namespace Urun {

namespace Key{
inline const std::string_view Collection{"Urunler"};

inline const std::string_view language{"lang"};
inline const std::string_view kategoriOid{"kategoriOid"};
inline const std::string_view urunAdi{"urunadi"};


namespace LANG{
inline const std::string_view lang{"lang"};
inline const std::string_view urunAdi{"urunadi"};
inline const std::string_view urunFiyati{"urunFiyati"};
inline const std::string_view urunParabirimi{"urunParaBirimi"};
}

}

class UrunLanguage : public MongoCore::Item
{
public:
    UrunLanguage();

    UrunLanguage &setLanguage( const std::string &language );
    UrunLanguage &setUrunAdi( const std::string &urunAdi );

    std::string getLanguage() const;
};

class UrunItem : public MongoCore::Item
{
public:
    UrunItem();

    UrunItem &addUrun( const UrunLanguage &urun );

    UrunLanguage getUrun( const std::string &language );
};

class UrunManager : public MongoCore::ListItem<UrunItem>
{
public:
    UrunManager();

    virtual void onList( const std::vector<UrunItem> &mList ) override;
};

} // namespace Urun
} // namespace Cafe

#endif // CAFE_URUN_URUNITEM_H
