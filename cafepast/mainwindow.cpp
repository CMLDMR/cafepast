
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "mongocxx/client.hpp"
#include "tabWidgets/poahacawidget.h"
#include "dialogs/kategorimanagerwidget.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);




    this->initAction();

    this->initWidget();

    if( mEnglishTranslator.load(":/language_en") ){
        qApp->installTranslator(&mEnglishTranslator);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initAction()
{

    mUrunMenu = std::make_unique<QMenu>(QObject::tr("Ürünler"));
    ui->menubar->addMenu(mUrunMenu.get());


    mYeniUrunAction = std::make_unique<QAction>("Yeni Ürün Girişi");
    mUrunMenu->addAction(mYeniUrunAction.get());

    mUrunUpdateAction = std::make_unique<QAction>("Ürün Güncelleme");
    mUrunMenu->addAction(mUrunUpdateAction.get());

    mKategoriManagerList = std::make_unique<QAction>("Kategori Yönetimi");
    mUrunMenu->addAction(mKategoriManagerList.get());
    QObject::connect(mKategoriManagerList.get(),&QAction::triggered,[=](const bool triggered){
        auto mkategoriManager = std::make_unique<KategoriManagerWidget>();
        qDebug() << triggered;
        mkategoriManager.get()->exec();
    });


    mAyarlarMenu = std::make_unique<QMenu>(QObject::tr("Ayarlar"));
    ui->menubar->addMenu(mAyarlarMenu.get());

    mParaBirimiAction = std::make_unique<QAction>("Para Birimi");
    mAyarlarMenu->addAction(mParaBirimiAction.get());

    mDilSecimiAction = std::make_unique<QAction>("Dil Seçimi");
    mAyarlarMenu->addAction(mDilSecimiAction.get());

}

void MainWindow::initWidget()
{

    mTabWidget = std::make_unique<QTabWidget>();

    mCentralWidgetLayout = std::make_unique<QHBoxLayout>();
    ui->centralwidget->setLayout(mCentralWidgetLayout.get());

    mCentralWidgetLayout->addWidget(mTabWidget.get());

    auto pohacaWidget = new PoahacaWidget("Pohaçalar");
    mTabWidget->insertTab(0,pohacaWidget,pohacaWidget->tabWidgetName());



}


