
#ifndef ABSTRACTLISTWIDGET_H
#define ABSTRACTLISTWIDGET_H


#include <QWidget>
#include <QString>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QTableView>

#include "menu/urunmodel.h"
#include "cafecore/kategoriitem.h"

namespace ParaBirimi {
class ParaItemModel;
}

class QComboBox;
class QVBoxLayout;

class AbstractListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractListWidget(const QString &tabWidgetName,QWidget *parent =nullptr);

    QString tabWidgetName() const;

signals:
    void UrunClicked( const QString& );


private:
    QString mTabWidgetName;

    QHBoxLayout* mLayout;
    QGroupBox* mListGroupBox;

    QVBoxLayout *mProductListLayout;
    QTableView* mTableListView;

    Cafe::Kategori::KategoriManager* mKategoriManager;
    Menu::UrunModel* mUrunModel;

    QComboBox* mCurrentParaBirimiComboBox;
    ParaBirimi::ParaItemModel* mParaModel;

};

#endif // ABSTRACTLISTWIDGET_H
