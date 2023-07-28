#ifndef CAFE_SUBE_SUBEITEM_H
#define CAFE_SUBE_SUBEITEM_H

#include "mongocore/item.h"
#include <mongocore/listitem.h>

namespace Cafe {
namespace Sube {

namespace Key{
inline const std::string_view Collection{"subeler"};
inline const std::string_view subeAdi{"subeAdi"};
inline const std::string_view subeAdresi{"subeAdresi"};
inline const std::string_view subeTelefon{"subeTelefon"};
}

class SubeItem : public MongoCore::Item
{
public:
    SubeItem();

    SubeItem& setSubeAdi( const std::string& subeAdi );
    SubeItem& setSubeAdresi( const std::string &subeAdresi );
    SubeItem& setSubeTelefon( const std::string &subeTelefon );

    std::string getSubeAdi() const;
    std::string getSubeAdresi() const;
    std::string getSubeTelefon() const;
};


class SubeManager : public MongoCore::ListItem<SubeItem>
{
public:
    explicit SubeManager();
    virtual ~SubeManager(){}

    virtual void onList( const std::vector<SubeItem> &mList ) override;
};


} // namespace Sube
} // namespace Cafe

#endif // CAFE_SUBE_SUBEITEM_H
