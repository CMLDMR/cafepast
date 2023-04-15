
#include "kategorimanagerwidget.h"
#include "cafecore/languageitem.h"


Kategori::KategoriManagerWidget::KategoriManagerWidget()
{
    this->setWindowTitle(TR("Kategori Yönetimi"));

    mLayout = std::make_unique<QVBoxLayout>();

    this->setLayout(mLayout.get());

    mStackedWidget = std::make_unique<SlidingStackedWidget>(this);
    mLayout->addWidget(mStackedWidget.get());



    mKategorListView = new KategoriListWidget(this);
    mStackedWidget->addWidget(mKategorListView);





    mYeniEkleWidget = new YeniEkleWidget(this);
    mStackedWidget->addWidget(mYeniEkleWidget);

    QObject::connect(mKategorListView,&KategoriListWidget::addNewKategoriBtn,[=](){
        mYeniEkleWidget->setCurrentKategoriName("");
        mYeniEkleWidget->title()->setText(TR("Yeni Kategori Ekle+"));
        mStackedWidget.get()->slideInIdx(1);
    });

    QObject::connect(mKategorListView,&KategoriListWidget::changeKategoriName,[=](const QString &currentName,const QString &kategoriOid){
        mYeniEkleWidget->setCurrentKategoriName(currentName,kategoriOid);
        mYeniEkleWidget->title()->setText(TR("Değiştir"));
        mStackedWidget.get()->slideInIdx(1);
    });


    QObject::connect(mYeniEkleWidget,&YeniEkleWidget::iptalClicked,[=](){
        mYeniEkleWidget->setCurrentKategoriName("");
        mStackedWidget->slideInIdx(0);
    });

    QObject::connect(mYeniEkleWidget,&YeniEkleWidget::yeniClicked,[=](const QString& newKategoriName){
        Cafe::Kategori::KategoriItem item;
        item.setName(newKategoriName.toStdString());
        auto ins = mKategorListView->kategoriModel()->InsertItem(item);
        if( ins.size() ){
            mKategorListView->kategoriModel()->UpdateList();
        }
        mStackedWidget->slideInIdx(0);
    });


    QObject::connect(mYeniEkleWidget,&YeniEkleWidget::degisClicked,[=](const QString& newKategoriName, const QString &kategoriOid){

        if( kategoriOid.size() ){
            Cafe::Kategori::KategoriItem item;
            item.setOid(kategoriOid.toStdString());
            item.setName(newKategoriName.toStdString());
            auto ins = mKategorListView->kategoriModel()->UpdateItem(item);
            if( ins ){
                mKategorListView->kategoriModel()->UpdateList();
            }
            mStackedWidget->slideInIdx(0);
        }

    });




    mDeleteWidget = new DeleteWidget(this);
    mStackedWidget->addWidget(mDeleteWidget);

    QObject::connect(mKategorListView,&KategoriListWidget::delClicked,[=](const QString &name, const QString &oid){
        mDeleteWidget->setKategoriNameOid(name,oid);
        mStackedWidget->slideInIdx(2);
    });

    QObject::connect(mDeleteWidget->iptalBtn(),&QPushButton::clicked,[=](){
        mStackedWidget->slideInIdx(0);
    });

    QObject::connect(mDeleteWidget->delBtn(),&QPushButton::clicked,[=](){
        Cafe::Kategori::KategoriItem item;
        item.setOid(mDeleteWidget->kategoriOid()->text().toStdString());
        auto ins = mKategorListView->kategoriModel()->DeleteItem(item);
        if( ins ){
            mKategorListView->kategoriModel()->UpdateList();
        }
        mStackedWidget->slideInIdx(0);
    });



    this->setMinimumWidth(450);
    this->setMinimumHeight(350);
}


