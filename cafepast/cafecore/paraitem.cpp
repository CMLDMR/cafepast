
#include "paraitem.h"
#include "global/globalVar.h"

namespace Cafe {
namespace ParaBirimi {

ParaItem::ParaItem()
    :MongoCore::Item(Key::Collection.data())
{

}

ParaItem &ParaItem::setParaName(const std::string &paraName)
{
    this->append(Key::para,paraName);
    return *this;
}

std::string ParaItem::getParaName() const
{
    auto val = this->element(Key::para.data());
    if( val ){
        return val.value().view().get_string().value.data();
    }
    return "";
}

ParaManager::ParaManager()
    :MongoCore::ListItem<ParaItem>(GlobarVar::GlobalDB::DB())
{

}

void ParaManager::onList(const std::vector<ParaItem> &mList)
{

}

} // namespace ParaBirimi
} // namespace Cafe

