
#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->initAction();

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


    mAyarlarMenu = std::make_unique<QMenu>(QObject::tr("Ayarlar"));
    ui->menubar->addMenu(mAyarlarMenu.get());

}


