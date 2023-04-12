
#ifndef KATEGORIMANAGERWIDGET_H
#define KATEGORIMANAGERWIDGET_H

#include <QDialog>
#include <cafecore/kategoriitem.h>


class KategoriManagerWidget : public QDialog, public Cafe::Kategori::KategoriManager
{
    Q_OBJECT
public:
    KategoriManagerWidget();


    virtual void onList( const std::vector<Cafe::Kategori::KategoriItem> &mList ) override;
};

#endif // KATEGORIMANAGERWIDGET_H
