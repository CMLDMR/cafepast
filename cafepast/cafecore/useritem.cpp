#include "useritem.h"

#include "global/globalVar.h"

namespace Cafe {
namespace User {

UserItem::UserItem()
:MongoCore::Item(Key::Collection.data())
{

}

UserItem &UserItem::setUserName(const std::string &userName)
{
    this->append(Key::username,userName);
    return *this;
}

UserItem &UserItem::setPassword(const std::string &password)
{
    this->append(Key::password,password);
    return *this;
}

UserItem &UserItem::setAdSoyad(const std::string &adSoyad)
{
    this->append(Key::adsoyad,adSoyad);
    return *this;
}

std::string UserItem::getUserName() const
{
    auto val = this->element(Key::username.data());
    if( val ){
        return val.value().view().get_string().value.data();
    }
    return "";
}

std::string UserItem::getPassword() const
{
    auto val = this->element(Key::password.data());
    if( val ){
        return val.value().view().get_string().value.data();
    }
    return "";
}

std::string UserItem::getAdSoyad() const
{
    auto val = this->element(Key::adsoyad.data());
    if( val ){
        return val.value().view().get_string().value.data();
    }
    return "";
}

UserManager::UserManager()
    :MongoCore::ListItem<UserItem>(GlobarVar::GlobalDB::DB())
{

}

void UserManager::onList(const std::vector<UserItem> &mList)
{

}

} // namespace User
} // namespace Cafe
