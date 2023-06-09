
#ifndef KATEGORI_KATEGORILISTMODEL_H
#define KATEGORI_KATEGORILISTMODEL_H

#include <QAbstractListModel>

#include <QObject>
#include <cafecore/kategoriitem.h>
#include <memory>

namespace Kategori {

class KategoriListModel : public QAbstractListModel, public Cafe::Kategori::KategoriManager
{
public:
    enum Role{
        KategoriOidRole = Qt::UserRole+1
    };
    explicit KategoriListModel(QObject *parent = nullptr);

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    void setList(const std::vector<Cafe::Kategori::KategoriItem> &newList);

    virtual void onList( const std::vector<Cafe::Kategori::KategoriItem> &mList ) override;

    void updateKategoriList();

private:
    std::vector<Cafe::Kategori::KategoriItem> mList;
};

} // namespace Kategori

#endif // KATEGORI_KATEGORILISTMODEL_H
