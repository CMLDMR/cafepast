
#ifndef GLOBALVAR_H
#define GLOBALVAR_H

#include <mongocore/db.h>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonDocument>

#include "cafecore/useritem.h"

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

    void setCorpName( const std::string &mCorpName );
    std::string getCorpName() const;

    void setContactName( const std::string &mContactName );
    std::string getContactName() const;

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

    Cafe::User::UserItem *currentUser() const;
    void setCurrentUser(Cafe::User::UserItem *newCurrentUser);

    QString currentSube() const;
    void setCurrentSube(const QString &newCurrentSube);

    static GlobalDB *global() ;

private:
    MongoCore::DB* mDB;
    mongocxx::client *mClient;
    mongocxx::database db;
    static GlobalDB* mGlobal;

    Cafe::User::UserItem* mCurrentUser;
    QString mCurrentSube;

};







}


#endif // GLOBALVAR_H
