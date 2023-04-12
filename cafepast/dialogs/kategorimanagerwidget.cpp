
#include "kategorimanagerwidget.h"

Kategori::KategoriManagerWidget::KategoriManagerWidget()
{
    this->setWindowTitle("Kategori Yönetimi");

    mLayout = std::make_unique<QVBoxLayout>();

    this->setLayout(mLayout.get());

    mStackedWidget = std::make_unique<SlidingStackedWidget>(this);
    mLayout->addWidget(mStackedWidget.get());



    mKategorListView = std::make_unique<KategoriListWidget>();
    mStackedWidget->addWidget(mKategorListView.get());

    QObject::connect(mKategorListView.get(),&KategoriListWidget::addNewKategoriBtn,[=](){
        mStackedWidget.get()->slideInIdx(1);
    });







    mYeniEkleWidget = std::make_unique<YeniEkleWidget>();
    mStackedWidget->addWidget(mYeniEkleWidget.get());

    QObject::connect(mYeniEkleWidget.get(),&YeniEkleWidget::iptalClicked,[=](){
        mStackedWidget->slideInIdx(0);
    });

    QObject::connect(mYeniEkleWidget.get(),&YeniEkleWidget::yeniClicked,[=](const QString& newKategoriName){
        Cafe::Kategori::KategoriItem item;
        item.setName(newKategoriName.toStdString());
        auto ins = this->InsertItem(item);
        if( ins.size() ){
            this->UpdateList();
        }
        mStackedWidget->slideInIdx(0);
    });

    this->setMinimumWidth(450);
    this->setMinimumHeight(350);

    this->setLimit(100);
    this->UpdateList();


}

void Kategori::KategoriManagerWidget::onList(const std::vector<Cafe::Kategori::KategoriItem> &mList)
{
    mKategorListView->setList(mList);
    for( const auto &item : mList ){
        qDebug() << bsoncxx::to_json(item.view()).c_str();
    }
}


