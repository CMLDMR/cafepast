
#ifndef KATEGORIMANAGERWIDGET_H
#define KATEGORIMANAGERWIDGET_H


#include <memory>

#include <QDialog>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QTableView>
#include <QListView>
#include <QPushButton>

#include <stackedWidget/SlidingStackedWidget.h>


#include "kategori/kategorilistwidget.h"
#include "kategori/yenieklewidget.h"

namespace Kategori{



class KategoriManagerWidget : public QDialog, public Cafe::Kategori::KategoriManager
{
    Q_OBJECT
public:
    KategoriManagerWidget();


    virtual void onList( const std::vector<Cafe::Kategori::KategoriItem> &mList ) override;

private:

    std::unique_ptr<QVBoxLayout> mLayout;

    std::unique_ptr<KategoriListWidget> mKategorListView;
    std::unique_ptr<SlidingStackedWidget> mStackedWidget;

    std::unique_ptr<YeniEkleWidget> mYeniEkleWidget;
};


}




#endif // KATEGORIMANAGERWIDGET_H
