
#ifndef CAFE_LANGUAGE_LANGUAGEITEM_H
#define CAFE_LANGUAGE_LANGUAGEITEM_H


#include <mongocore/listitem.h>
#include <optional>

#define TR(x)   Cafe::Language::LanguageTextManager::instance()->tr(x).data()


namespace Cafe {
namespace Language {
namespace Key {
namespace Languages {
inline const std::string_view Collection{"Languages"};
inline const std::string_view lang{"Lang"};
inline const std::string_view shortName{"short"};
}
}


class LanguageItem : public MongoCore::Item
{
public:
    LanguageItem();

    LanguageItem &setLang( const std::string &language , const std::string &shortName );
    std::string getLanguageName() const;
    std::string getShortName() const;
};



class LanguageManager : public MongoCore::ListItem<LanguageItem>
{
public:
    LanguageManager();

    LanguageManager* instance();
    virtual void onList( const std::vector<LanguageItem> &mList ) override;
private:
    static LanguageManager* mLanguageManager;

};

namespace Key {

namespace Text{
inline const std::string_view Collection{"textSource"};
inline const std::string_view destText{"destText"};
inline const std::string_view shortLang{"shortLang"};
inline const std::string_view trText{"trText"};
}

}

class TextItem : public MongoCore::Item
{
public:
    TextItem();

    TextItem &setText(const std::string &trText,
                      const std::string &shortLang,
                      const std::string &destText );

    std::string getText() const;
    std::string getLang() const;
    std::string getDestText() const;
};


class LanguageTextManager : public MongoCore::ListItem<TextItem>
{

public:
    LanguageTextManager();

    static LanguageTextManager* instance();

    std::string tr(const std::string &text );

private:
    static LanguageTextManager* mLanguageTextManager;
    std::string mDestinationShortLang{"tr"};


    // DB interface
public:
    virtual void errorOccured(const std::string &errorText) override;

    // ListItem interface
public:
    virtual void onList(const std::vector<TextItem> &mlist) override;
    void setDestinationShortLang(const std::string &newDestinationShortLang);
    std::string destinationShortLang() const;
};








} // namespace Language
} // namespace Cafe

#endif // CAFE_LANGUAGE_LANGUAGEITEM_H
