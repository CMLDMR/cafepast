
#ifndef LANGUAGE_LANGUAGEMODEL_H
#define LANGUAGE_LANGUAGEMODEL_H

#include <QAbstractListModel>

#include <QObject>

#include "cafecore/languageitem.h"


namespace Language {

class LanguageModel : public QAbstractListModel, public Cafe::Language::LanguageManager
{
    Q_OBJECT
public:
    explicit LanguageModel(QObject *parent = nullptr);

    enum Role{
        oid = Qt::UserRole+1,
        shortName,
        langName
    };

    // DB interface
public:
    virtual void errorOccured(const std::string &errorText) override;

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    // LanguageManager interface
public:
    virtual void onList(const std::vector<Cafe::Language::LanguageItem> &mList) override;


private:
    std::vector<Cafe::Language::LanguageItem> mList;

};

} // namespace Language

#endif // LANGUAGE_LANGUAGEMODEL_H
