
#include "kategorimanagerwidget.h"

Kategori::KategoriManagerWidget::KategoriManagerWidget()
{
    this->setWindowTitle("Kategori Yönetimi");

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
        mStackedWidget.get()->slideInIdx(1);
    });

    QObject::connect(mKategorListView,&KategoriListWidget::changeKategoriName,[=](const QString &currentName){
        mYeniEkleWidget->setCurrentKategoriName(currentName);
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


    mDeleteWidget = new DeleteWidget(this);
    mStackedWidget->addWidget(mDeleteWidget);

    QObject::connect(mKategorListView,&KategoriListWidget::delClicked,[=](const QString &name, const QString &oid){
        mStackedWidget->slideInIdx(2);
    });

    QObject::connect(mDeleteWidget->iptalBtn(),&QPushButton::clicked,[=](){
        mStackedWidget->slideInIdx(0);
    });

    QObject::connect(mDeleteWidget->delBtn(),&QPushButton::clicked,[=](){
        //TODO: Kategori Silinecek
        qDebug() << "Delete Kategori: "<<mDeleteWidget->kategoriOid()->text();
        mStackedWidget->slideInIdx(0);
    });



    this->setMinimumWidth(450);
    this->setMinimumHeight(350);
}


