
#ifndef CAFE_URUN_URUNITEM_H
#define CAFE_URUN_URUNITEM_H


#include <mongocore/listitem.h>

namespace Cafe {
namespace Urun {

namespace Key{
inline const std::string_view Collection{"Urunler"};

inline const std::string_view paraBirimiArray{"paraBirimiArray"};
inline const std::string_view kategoriOid{"kategoriOid"};
inline const std::string_view urunAdi{"urunadi"};


namespace ParaObj{
inline const std::string_view urunFiyati{"urunFiyati"};
inline const std::string_view urunParabirimi{"urunParaBirimi"};
}

}

class UrunLanguage : public MongoCore::Item
{
public:
    UrunLanguage();

    UrunLanguage &setUrunFiyati( const double urunFiyati );
    UrunLanguage &setUrunParaBirimi( const std::string &paraBirimi );

    double getUrunFiyati() const;

    std::string getParaBirimi() const;
};

class UrunItem : public MongoCore::Item
{
public:
    UrunItem();

    UrunItem &setUrunAdi( const std::string &urunAdi );
    UrunItem &setKategoriOid( const std::string &kategoriOid );

    bool addUrun( const UrunLanguage &urun );

    bool IsUrunExist( const std::string &paraBirimi ) const;
    bool change(const std::string &paraBirimi , const UrunLanguage &newUrun );
    std::vector<UrunLanguage> getUrunList() const;
    UrunLanguage getUrun(const std::string &paraBirimi ) const;
    std::string getUrunAdi() const;
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
