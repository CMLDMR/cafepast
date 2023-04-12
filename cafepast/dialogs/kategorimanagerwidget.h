
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



class KategoriManagerWidget : public QDialog
{
    Q_OBJECT
public:
    KategoriManagerWidget();
    virtual ~KategoriManagerWidget(){
        mStackedWidget.get()->removeWidget(mKategorListView);
        delete mKategorListView;
        delete mYeniEkleWidget;

    }


private:

    std::unique_ptr<QVBoxLayout> mLayout;

    KategoriListWidget* mKategorListView;
    std::unique_ptr<SlidingStackedWidget> mStackedWidget;

    YeniEkleWidget* mYeniEkleWidget;
};


}




#endif // KATEGORIMANAGERWIDGET_H
