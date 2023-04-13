
#ifndef GLOBALVAR_H
#define GLOBALVAR_H

#include <mongocore/db.h>


namespace GlobarVar{



class GlobalDB
{
public:
    GlobalDB();


    ///
    /// \brief singletor instance DB
    /// \return static MongoCore::DB*
    static MongoCore::DB* DB();



private:
    MongoCore::DB* mDB;
    mongocxx::client *mClient;
    mongocxx::database db;
    static GlobalDB* mGlobal;
    GlobalDB *global() const;

};




}


#endif // GLOBALVAR_H
