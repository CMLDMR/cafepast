
#ifndef ADISYON_ADISYONMODEL_H
#define ADISYON_ADISYONMODEL_H

#include <QAbstractTableModel>

#include "cafecore/adisyonitem.h"

namespace Adisyon {


class AdisyonModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit AdisyonModel(QObject *parent = nullptr);

    void addUrun( const Cafe::Urun::UrunItem &urunItem );

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void setCurrentParaBirimi(const QString &newCurrentParaBirimi);

private:

    Adisyon::AdisyonListItem* mUrunList;
    Adisyon::AdisyonListManager* mAdisyonListManager;

    QString mCurrentParaBirimi;
};

} // namespace Adisyon

#endif // ADISYON_ADISYONMODEL_H
