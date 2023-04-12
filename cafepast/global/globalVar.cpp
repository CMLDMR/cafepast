#include "globalVar.h"
#include "mongocxx/client.hpp"
#include <mutex>
#include "../../url.h"

#include <QDebug>


std::once_flag flag1;

GlobarVar::GlobalDB* GlobarVar::GlobalDB::GlobalDB::mGlobal = nullptr;

GlobarVar::GlobalDB::GlobalDB()
    :mDB{nullptr}
{
    try {
        mClient = new mongocxx::client(mongocxx::uri{_url});
    } catch (mongocxx::exception &e) {

    }
    db = mClient->database("CAFEDB");


    mDB = new MongoCore::DB(&db);

}

MongoCore::DB *GlobarVar::GlobalDB::DB()
{
    std::call_once(flag1, [=](){
        mGlobal = new GlobalDB();
    });
    return mGlobal->mDB;
}


namespace GlobarVar {
GlobalDB *GlobalDB::global() const
{
    return mGlobal;
}

}
