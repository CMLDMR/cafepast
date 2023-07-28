#ifndef CAFE_USER_USERITEM_H
#define CAFE_USER_USERITEM_H

#include "mongocore/item.h"
#include <mongocore/listitem.h>

namespace Cafe {
namespace User {

namespace Key{
inline const std::string_view Collection{"Users"};
inline const std::string_view username{"username"};
inline const std::string_view password{"password"};
inline const std::string_view adsoyad{"adSoyad"};
}

class UserItem : public MongoCore::Item
{
public:
    UserItem();

    UserItem& setUserName( const std::string& userName );
    UserItem& setPassword( const std::string &password );
    UserItem& setAdSoyad( const std::string &adSoyad );

    std::string getUserName() const;
    std::string getPassword() const;
    std::string getAdSoyad() const;
};



class UserManager : public MongoCore::ListItem<UserItem>
{
public:
    explicit UserManager();
    virtual ~UserManager(){}

    virtual void onList( const std::vector<UserItem> &mList ) override;
};

} // namespace User
} // namespace Cafe

#endif // CAFE_USER_USERITEM_H
