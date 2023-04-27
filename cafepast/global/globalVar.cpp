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


std::once_flag flag_config;
GlobarVar::LocalConfiguration* GlobarVar::LocalConfiguration::mLocalConfiguration = nullptr;



LocalConfiguration::LocalConfiguration()
{
    qDebug() << "Configuration Loaded: " << this->loadConfigurationFile();
}

LocalConfiguration *LocalConfiguration::instance()
{
    std::call_once(flag_config, [=](){
        mLocalConfiguration = new LocalConfiguration();
    });
    return mLocalConfiguration;
}

bool LocalConfiguration::loadConfigurationFile()
{
    QFile file("configure.dat");
    if( file.open(QIODevice::ReadOnly) ){
        auto ar = file.readAll();
        mConfigurations = QJsonDocument::fromJson(ar).object();
        file.close();
        mIsLoaded = true;
        return true;
    }else{
        mIsLoaded = false;
        return false;
    }
}

bool LocalConfiguration::saveConfigurationFile()
{
    QFile file("configure.dat");
    if( file.open(QIODevice::ReadWrite) ){
        file.write(QJsonDocument(mConfigurations).toJson());
        file.close();
        return true;
    }else{
        return false;
    }
}

void LocalConfiguration::setCurrentParaBirimi(const std::string &paraBirimi)
{
    mConfigurations.insert("paraBirimi",paraBirimi.data());
    this->saveConfigurationFile();
}

std::string LocalConfiguration::getCurrentParaBirimi() const
{
    auto val = mConfigurations.value("paraBirimi");
    return val.toString().toStdString();
}

void LocalConfiguration::setCurrentLang(const std::string &langShortName)
{
    mConfigurations.insert("language",langShortName.data());
    this->saveConfigurationFile();
}

std::string LocalConfiguration::getCurrentLang() const
{
    auto val = mConfigurations.value("language");
    return val.toString().toStdString();
}

void LocalConfiguration::setCorpName(const std::string &mCorpName)
{
    mConfigurations.insert("corpName",mCorpName.data());
    this->saveConfigurationFile();
}

std::string LocalConfiguration::getCorpName() const
{
    auto val = mConfigurations.value("corpName");
    return val.toString().toStdString();
}

bool LocalConfiguration::isLoaded() const
{
    return mIsLoaded;
}

}
