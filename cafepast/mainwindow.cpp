
#include "mainwindow.h"
#include "./ui_mainwindow.h"


#include "dialogs/kategorimanagerwidget.h"
#include "dialogs/paraDialog/paradialog.h"
#include "dialogs/langDialog/languagedialog.h"
#include "dialogs/langDialog/languagetextbankdialog.h"
#include "dialogs/urunDialog/urunmanagerdialog.h"
#include "dialogs/otheroptionsdialog.h"

#include "adisyon/adisyonwidget.h"

#include "cafecore/languageitem.h"
#include "global/globalVar.h"

using Cafe::Language::LanguageTextManager;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Cafe::Language::LanguageTextManager::instance()->setDestinationShortLang(GlobarVar::LocalConfiguration::instance()->getCurrentLang().data());

    this->setWindowTitle(QString(GlobarVar::LocalConfiguration::instance()->getCorpName().data())+" - " + QString(GlobarVar::LocalConfiguration::instance()->getCurrentLang().data()).toUpper());
    this->initAction();

    this->initWidget();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initAction()
{

    mUrunMenu = std::make_unique<QMenu>(TR("Ürünler"));
    ui->menubar->addMenu(mUrunMenu.get());


    mUrunManagerDialogAction = std::make_unique<QAction>(TR("Ürün Yönetimi"));
    QObject::connect(mUrunManagerDialogAction.get(),&QAction::triggered,[=](const bool triggered){
        auto mUrunManagerDialog = new Urun::UrunManagerDialog();
        mUrunManagerDialog->exec();
        delete mUrunManagerDialog;
    });
    mUrunMenu->addAction(mUrunManagerDialogAction.get());

    mKategoriManagerList = std::make_unique<QAction>(TR("Kategori Yönetimi"));
    mUrunMenu->addAction(mKategoriManagerList.get());
    QObject::connect(mKategoriManagerList.get(),&QAction::triggered,[=](const bool triggered){
        auto mkategoriManager = new Kategori::KategoriManagerWidget();
        mkategoriManager->exec();
        delete mkategoriManager;
    });


    mAyarlarMenu = std::make_unique<QMenu>(TR("Ayarlar"));
    ui->menubar->addMenu(mAyarlarMenu.get());

    mParaBirimiAction = std::make_unique<QAction>(TR("Para Birimi"));
    QObject::connect(mParaBirimiAction.get(),&QAction::triggered,[=](const bool triggered){
        auto mParaManagerDialog = new ParaBirimi::ParaDialog();
        mParaManagerDialog->exec();
        delete mParaManagerDialog;
    });
    mAyarlarMenu->addAction(mParaBirimiAction.get());

    mDilSecimiAction = std::make_unique<QAction>(TR("Dil Seçimi"));
    QObject::connect(mDilSecimiAction.get(),&QAction::triggered,[=](const bool triggered){
        auto mLanguageDialog = new Language::LanguageDialog();
        mLanguageDialog->exec();
        delete mLanguageDialog;
    });
    mAyarlarMenu->addAction(mDilSecimiAction.get());

    mTextManagerAction = std::make_unique<QAction>(TR("Sözlük"));
        QObject::connect(mTextManagerAction.get(),&QAction::triggered,[=](const bool triggered){
        auto mLanguageTextBankDialog = new Language::LanguageTextBankDialog();
            mLanguageTextBankDialog->exec();
            delete mLanguageTextBankDialog;
        });
    mAyarlarMenu->addAction(mTextManagerAction.get());


    mOtherMenu = std::make_unique<QMenu>(TR("Diğer Ayarlar"));
    mAyarlarMenu.get()->addMenu(mOtherMenu.get());

    mCorpNameAction = std::make_unique<QAction>(TR("Şirket Adı Değiştir"));
       QObject::connect(mCorpNameAction.get(),&QAction::triggered,[=](const bool triggered){
        //TODO: Cafe Adı Ayarları Eklenecek
           auto mLanguageTextBankDialog = new Other::OtherOptionsDialog();
           mLanguageTextBankDialog->exec();
           delete mLanguageTextBankDialog;
       });
    mOtherMenu->addAction(mCorpNameAction.get());

       mCorpContactAction = std::make_unique<QAction>(TR("Telefon Numarası Değiştir"));
       QObject::connect(mCorpContactAction.get(),&QAction::triggered,[=](const bool triggered){
           //TODO: Cafe Adı Ayarları Eklenecek
           auto mLanguageTextBankDialog = new Other::OtherOptionsDialog();
           mLanguageTextBankDialog->exec();
           delete mLanguageTextBankDialog;
       });
       mOtherMenu->addAction(mCorpNameAction.get());

}

void MainWindow::initWidget()
{

    mTabWidget = std::make_unique<TabWidget>();
    mTabWidget->setMaximumWidth(450);
    mCentralWidgetLayout = std::make_unique<QHBoxLayout>();
    ui->centralwidget->setLayout(mCentralWidgetLayout.get());

    mCentralWidgetLayout->addWidget(mTabWidget.get());


    mAdisyonWidget = new Adisyon::AdisyonWidget();

    mCentralWidgetLayout->addWidget(mAdisyonWidget);

    QObject::connect(mTabWidget.get(),&TabWidget::UrunClicked,mAdisyonWidget,&Adisyon::AdisyonWidget::addUrun);


}


