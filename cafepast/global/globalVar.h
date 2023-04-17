
#ifndef GLOBALVAR_H
#define GLOBALVAR_H

#include <mongocore/db.h>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonDocument>

namespace GlobarVar{


class LocalConfiguration
{
    LocalConfiguration();
public:


    static LocalConfiguration* instance();

    bool loadConfigurationFile();
    bool saveConfigurationFile();

    void setCurrentParaBirimi(const std::string &paraBirimi);
    std::string getCurrentParaBirimi() const;

    void setCurrentLang( const std::string &langShortName );
    std::string getCurrentLang() const;

    bool isLoaded() const;

private:
    static LocalConfiguration* mLocalConfiguration;
    bool mIsLoaded{false};
    QJsonObject mConfigurations;

};


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
