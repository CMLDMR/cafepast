
#ifndef LANGUAGE_LANGUAGETEXTMODEL_H
#define LANGUAGE_LANGUAGETEXTMODEL_H

#include <QAbstractTableModel>

#include <QObject>

#include "cafecore/languageitem.h"

namespace Language {

class LanguageTextModel : public QAbstractTableModel, public Cafe::Language::LanguageTextManager
{
    Q_OBJECT
public:
    explicit LanguageTextModel(QObject *parent = nullptr);

private:
    std::vector<Cafe::Language::TextItem> mList;

    // DB interface
public:
    virtual void errorOccured(const std::string &errorText) override;

    // LanguageTextManager interface
public:
    virtual void onList(const std::vector<Cafe::Language::TextItem> &mlist) override;

    // QAbstractItemModel interface
public:
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    virtual QModelIndex parent(const QModelIndex &child) const override;
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    std::vector<Cafe::Language::TextItem> list() const;
};

} // namespace Language

#endif // LANGUAGE_LANGUAGETEXTMODEL_H
