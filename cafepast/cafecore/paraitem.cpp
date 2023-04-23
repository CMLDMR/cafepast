
#include "paraitem.h"
#include "global/globalVar.h"
#include <mutex>

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


std::once_flag paraManager_once_flag;
static ParaManager* mParaManager{nullptr};

ParaManager::ParaManager()
    :MongoCore::ListItem<ParaItem>(GlobarVar::GlobalDB::DB())
{

}

ParaManager *ParaManager::instance()
{
    std::call_once(paraManager_once_flag,[=](){
        mParaManager = new ParaManager();
    });
    return mParaManager;
}

void ParaManager::onList(const std::vector<ParaItem> &mList)
{

}

} // namespace ParaBirimi
} // namespace Cafe

