
#ifndef ADISYON_ADISYONITEM_H
#define ADISYON_ADISYONITEM_H


#include <mongocore/listitem.h>
#include "urunitem.h"

namespace Adisyon {

namespace Key{
inline const std::string_view urunItem{"urun"};
inline const std::string_view adet{"adet"};
}

class AdisyonItem : public MongoCore::Item
{
public:
    AdisyonItem();

    void setAdet( const double adet );
    void setUrun( const Cafe::Urun::UrunItem &item );

    Cafe::Urun::UrunItem getUrun() const;
    double getAdet() const;
};



namespace Key{
inline const std::string_view Collection{"Adisyon"};
inline const std::string_view urunler{"urunler"};
inline const std::string_view julianDate{"julianDate"};
inline const std::string_view epochTime{"epochTime"};
}

class AdisyonListItem : public MongoCore::Item
{
public:
    AdisyonListItem();

    void addAdisyon( const AdisyonItem &item );

    int adisyonSize() const;

    AdisyonItem operator[](const int index);
    AdisyonItem adisyon(const int index);

};

class AdisyonListManager : public MongoCore::ListItem<AdisyonListItem>
{
public:
    AdisyonListManager();

    // DB interface
public:
    virtual void errorOccured(const std::string &errorText) override;

    // ListItem interface
public:
    virtual void onList(const std::vector<AdisyonListItem> &mlist) override;
};

} // namespace Adisyon

#endif // ADISYON_ADISYONITEM_H
