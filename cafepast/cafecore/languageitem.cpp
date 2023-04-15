
#include "languageitem.h"
#include "global/globalVar.h"
#include <mutex>

namespace Cafe {
namespace Language {

LanguageItem::LanguageItem()
    :MongoCore::Item(Key::Languages::Collection.data())
{

}

//LanguageItem::LanguageItem(const LanguageItem &other)
//    :MongoCore::Item(Key::Languages::Collection.data())
//{
//    this->setDocumentView(other.view());
//}

//LanguageItem::LanguageItem(LanguageItem &&other)
//    :MongoCore::Item(Key::Languages::Collection.data())
//{
//    this->setDocumentView(other.view());
//}

LanguageItem &LanguageItem::setLang(const std::string &language, const std::string &shortName)
{
    this->append(Key::Languages::lang,language);
    this->append(Key::Languages::shortName,shortName);
    return *this;
}

std::string LanguageItem::getLanguageName() const
{
    auto val = this->element(Key::Languages::lang.data());
    if( val ){
        return val.value().view().get_string().value.data();
    }
    return "";
}

std::string LanguageItem::getShortName() const
{
    auto val = this->element(Key::Languages::shortName.data());
    if( val ){
        return val.value().view().get_string().value.data();
    }
    return "";
}





std::once_flag LanguageManager_flag;
LanguageManager* LanguageManager::mLanguageManager = nullptr;

LanguageManager::LanguageManager()
    :MongoCore::ListItem<LanguageItem>(GlobarVar::GlobalDB::DB())
{
    this->setLimit(10000);

}

LanguageManager *LanguageManager::instance()
{
    std::call_once(LanguageManager_flag, [=](){
        mLanguageManager = new LanguageManager();
    });
    return mLanguageManager;
}

void LanguageManager::onList(const std::vector<LanguageItem> &mList)
{

}

TextItem::TextItem()
    :MongoCore::Item(Key::Text::Collection.data())
{

}

TextItem &TextItem::setText(const std::string &trText, const std::string &shortLang, const std::string &destText)
{
    this->append(Key::Text::trText,trText);
    this->append(Key::Text::shortLang,shortLang);
    this->append(Key::Text::destText,destText);
    return *this;
}

std::string TextItem::getText() const
{
    auto val = this->element(Key::Text::trText.data());
    if( val ){
        return val.value().view().get_string().value.data();
    }
    return "";
}

std::string TextItem::getLang() const
{
    auto val = this->element(Key::Text::shortLang.data());
    if( val ){
        return val.value().view().get_string().value.data();
    }
    return "";
}

std::string TextItem::getDestText() const
{
    auto val = this->element(Key::Text::destText.data());
    if( val ){
        return val.value().view().get_string().value.data();
    }
    return "";
}




std::once_flag LanguageTextManager_flag;
LanguageTextManager* LanguageTextManager::mLanguageTextManager = nullptr;

LanguageTextManager::LanguageTextManager()
    :MongoCore::ListItem<TextItem>(GlobarVar::GlobalDB::DB())
{
    this->setLimit(10000);
    this->UpdateList();
}

LanguageTextManager *LanguageTextManager::instance()
{
    std::call_once(LanguageTextManager_flag, [=](){
        mLanguageTextManager = new LanguageTextManager();
    });
    return mLanguageTextManager;
}

std::string LanguageTextManager::tr(const std::string &text)
{
    bool exist = false;
    auto list = this->List();
    std::string str = text;
    for( auto &item : list ){
        if( item.getText() == text && item.getLang() == mDestinationShortLang ){
            exist = true;
            str = item.getDestText();
        }
    }
    if( exist ){
        return str;
    }else{
        return "!"+text+"!";
    }
}

std::string LanguageTextManager::destinationShortLang() const
{
    return mDestinationShortLang;
}

void LanguageTextManager::setDestinationShortLang(const std::string &newDestinationShortLang)
{
    mDestinationShortLang = newDestinationShortLang;
}



} // namespace Language
} // namespace Cafe



void Cafe::Language::LanguageTextManager::errorOccured(const std::string &errorText)
{
}

void Cafe::Language::LanguageTextManager::onList(const std::vector<TextItem> &mlist)
{
}
