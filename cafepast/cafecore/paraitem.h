
#ifndef CAFE_PARABIRIMI_PARAITEM_H
#define CAFE_PARABIRIMI_PARAITEM_H


#include <mongocore/listitem.h>


namespace Cafe {
namespace ParaBirimi {

namespace Key {
inline const std::string_view Collection{"ParaBirimi"};
inline const std::string_view para{"para"};
}


class ParaItem : public MongoCore::Item
{
public:
    ParaItem();

    ParaItem &setParaName( const std::string &paraName );
    std::string getParaName() const;
};




class ParaManager : public MongoCore::ListItem<ParaItem>
{
public:
    ParaManager();

    static ParaManager* instance();
    virtual void onList( const std::vector<ParaItem> &mList ) override;

};



} // namespace ParaBirimi
} // namespace Cafe

#endif // CAFE_PARABIRIMI_PARAITEM_H
