
#include "mainwindow.h"
#include "./ui_mainwindow.h"


#include "dialogs/kategorimanagerwidget.h"
#include "dialogs/paraDialog/paradialog.h"
#include "dialogs/langDialog/languagedialog.h"
#include "dialogs/langDialog/languagetextbankdialog.h"
#include "cafecore/languageitem.h"
#include "global/globalVar.h"

using Cafe::Language::LanguageTextManager;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Cafe::Language::LanguageTextManager::instance()->setDestinationShortLang(GlobarVar::LocalConfiguration::instance()->getCurrentLang().data());

    this->setWindowTitle("Cafe Del Mar - " + QString(GlobarVar::LocalConfiguration::instance()->getCurrentLang().data()).toUpper());
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

    mUrunMenu = std::make_unique<QMenu>(TR("Ürünler"));
    ui->menubar->addMenu(mUrunMenu.get());


    mYeniUrunAction = std::make_unique<QAction>(TR("Yeni Ürün Girişi"));
    mUrunMenu->addAction(mYeniUrunAction.get());

    mUrunUpdateAction = std::make_unique<QAction>(TR("Ürün Güncelleme"));
    mUrunMenu->addAction(mUrunUpdateAction.get());

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

}

void MainWindow::initWidget()
{

    mTabWidget = std::make_unique<TabWidget>();

    mCentralWidgetLayout = std::make_unique<QHBoxLayout>();
    ui->centralwidget->setLayout(mCentralWidgetLayout.get());

    mCentralWidgetLayout->addWidget(mTabWidget.get());


}


