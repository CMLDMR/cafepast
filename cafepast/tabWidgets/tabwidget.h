
#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include "cafecore/kategoriitem.h"


class TabWidget : public QTabWidget
{
    Q_OBJECT
public:
    TabWidget();
    virtual ~TabWidget();

signals:
    void UrunClicked( const QString &);

    // QWidget interface
protected:
    virtual void contextMenuEvent(QContextMenuEvent *event) override;

    Cafe::Kategori::KategoriManager* mKategoriManager;

};

#endif // TABWIDGET_H
