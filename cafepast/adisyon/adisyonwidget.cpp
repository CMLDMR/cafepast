
#include "adisyonwidget.h"
#include "adisyonmodel.h"
#include "cafecore/languageitem.h"
#include "cafecore/urunitem.h"
#include "model/paraitemmodel.h"
#include "global/globalVar.h"
#include "dialogs/adisyonDialog/changedialog.h"
#include "global/informationwidget.h"
#include "dialogs/askdialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableView>
#include <QHeaderView>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>
#include <QComboBox>
#include <QDoubleSpinBox>

namespace Adisyon {

AdisyonWidget::AdisyonWidget(QWidget *parent)
    : QWidget{parent}
{

    mMainLayout = new QHBoxLayout();
    this->setLayout(mMainLayout);


    mAdisyonListWidget = new QWidget();
    mMainLayout->addWidget(mAdisyonListWidget);

    mAdisyonListLayout = new QVBoxLayout();
    mAdisyonListWidget->setLayout(mAdisyonListLayout);

    mAdisyonView = new QTableView();
    mAdisyonListLayout->addWidget(mAdisyonView);
    mAdisyonView->horizontalHeader()->setStretchLastSection(true);

    mAdisyonModel = new Adisyon::AdisyonModel();
    mAdisyonView->setModel(mAdisyonModel);

    mControlBirimiLayout = new QHBoxLayout();
    mSayiArtirBtn = new QPushButton(TR("Sayı Artır++"));
    mSayiAzaltBtn = new QPushButton(TR("Sayı Azalt--"));
    mSayiDegisBtn = new QPushButton(TR("Sayı Degiştir"));

    mControlBirimiLayout->addWidget(mSayiArtirBtn);
    mControlBirimiLayout->addWidget(mSayiAzaltBtn);
    mControlBirimiLayout->addWidget(mSayiDegisBtn);

    mAdisyonListLayout->addLayout(mControlBirimiLayout);


    mTotalFiyatLabel = new QLabel(TR("Toplam Fiyat"));
    mAdisyonListLayout->addWidget(mTotalFiyatLabel,0,Qt::AlignmentFlag::AlignJustify);
    mTotalFiyatLabel->setFont(QFont("Tahoma",15));

    mParaBirimiLayout = new QHBoxLayout();
    mParaBirimiDegisLabel = new QLabel(TR("Para Birimi"));
    mParaBirimiComboBox = new QComboBox();
    mParaBirimiLayout->addWidget(mParaBirimiDegisLabel);
    mParaBirimiLayout->addWidget(mParaBirimiComboBox);
    mAdisyonListLayout->addLayout(mParaBirimiLayout);
    mParaItemModel = new ParaBirimi::ParaItemModel();
    mParaBirimiComboBox->setModel(mParaItemModel);
    for( int i = 0 ; i < mParaBirimiComboBox->count() ; i++ ){
        if( mParaBirimiComboBox->itemText(i).toStdString() == GlobarVar::LocalConfiguration::instance()->getCurrentParaBirimi() )  {
            mParaBirimiComboBox->setCurrentIndex(i);
            break;
        }
    }

    mSilSelectedBtn = new QPushButton("Sil");
    mAdisyonListLayout->addWidget(mSilSelectedBtn);


    mAdisyonPreviewWidget = new QWidget();
    mMainLayout->addWidget(mAdisyonPreviewWidget);
    mAdisyonPreviewWidget->setMaximumWidth(400);

    mAdisyonPreviewLayout = new QVBoxLayout();
    mAdisyonPreviewWidget->setLayout(mAdisyonPreviewLayout);

    mAdisyonPreviewTitle = new QLabel(TR("Adisyon Önizleme"));
    mAdisyonPreviewLayout->addWidget(mAdisyonPreviewTitle);

    mAdisyonPreviewScrollArea = new QScrollArea();
    mAdisyonPreviewLayout->addWidget(mAdisyonPreviewScrollArea);
    mAdisyonPreviewScrollArea->setBackgroundRole(QPalette::Dark);

    mAdisyonPreviewLabel = new QLabel("sdfg");
    mAdisyonPreviewLabel->setGeometry(0,0,350,1000);
    mAdisyonPreviewScrollArea->setWidget(mAdisyonPreviewLabel);

    mAdisyonPreviwImage = new QImage("adisyon.jpg");
    if( mAdisyonPreviwImage->load("adisyon.jpg") ){
        *mAdisyonPreviwImage = mAdisyonPreviwImage->scaledToWidth(350);
        mAdisyonPreviewLabel->setGeometry(0,0,350,mAdisyonPreviwImage->height());
        mAdisyonPreviewLabel->setPixmap(QPixmap::fromImage(*mAdisyonPreviwImage));
    }

    mAdisyonPreviewPrintBtn = new QPushButton(TR("Yazdır"));
                              mAdisyonPreviewLayout->addWidget(mAdisyonPreviewPrintBtn);

    mUrunManager = new Cafe::Urun::UrunManager();

    mAdisyonModel->setCurrentParaBirimi(mParaBirimiComboBox->currentText());
    QObject::connect(mParaBirimiComboBox,&QComboBox::currentIndexChanged,[=](const int index){
        mAdisyonModel->setCurrentParaBirimi(mParaBirimiComboBox->itemText(index));
        mTotalFiyatLabel->setText("<b>"+QString(TR("Toplam Fiyat"))+" :"+QString::number(mAdisyonModel->getTotalPrice()) + " " + mParaBirimiComboBox->currentText()+"</b>");
    });

    mAdisyonView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
    mAdisyonView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    mAdisyonView->setSelectionMode(QAbstractItemView::SingleSelection);

    QObject::connect(mSayiArtirBtn,&QPushButton::clicked,this,&AdisyonWidget::incrementUrun);
    QObject::connect(mSayiAzaltBtn,&QPushButton::clicked,this,&AdisyonWidget::decrementUrun);
    QObject::connect(mSayiDegisBtn,&QPushButton::clicked,this,&AdisyonWidget::changeUrunAdet);
    QObject::connect(mSilSelectedBtn,&QPushButton::clicked,this,&AdisyonWidget::removeUrun);

}

void AdisyonWidget::addUrun(const QString &urunOid)
{
    Cafe::Urun::UrunItem filter;
    filter.setOid(urunOid.toStdString());
    auto urunItem = mUrunManager->FindOneItem(filter);

    mAdisyonModel->addUrun(urunItem);

    mTotalFiyatLabel->setText("<b>"+QString(TR("Toplam Fiyat"))+" :"+
                              QString::number(mAdisyonModel->getTotalPrice()) + " " +
                              mParaBirimiComboBox->currentText()+"</b>");
}

void AdisyonWidget::reduceUrun(const QString &urunOid)
{
    Cafe::Urun::UrunItem filter;
    filter.setOid(urunOid.toStdString());
    auto urunItem = mUrunManager->FindOneItem(filter);

    mAdisyonModel->reduceUrun(urunItem);

    mTotalFiyatLabel->setText("<b>"+QString(TR("Toplam Fiyat"))+" :"+
                              QString::number(mAdisyonModel->getTotalPrice()) + " " +
                              mParaBirimiComboBox->currentText()+"</b>");
}

void AdisyonWidget::incrementUrun()
{
    auto index = mAdisyonView->currentIndex();
    if( index.isValid() ){
        this->addUrun(mAdisyonModel->index(index.row(),0).data(AdisyonModel::Oid).toString());
        mAdisyonView->setCurrentIndex(index);
    }
}

void AdisyonWidget::decrementUrun()
{
    auto index = mAdisyonView->currentIndex();
    if( index.isValid() ){
        this->reduceUrun(mAdisyonModel->index(index.row(),0).data(AdisyonModel::Oid).toString());
        mAdisyonView->setCurrentIndex(index);
    }
}

void AdisyonWidget::changeUrunAdet()
{
    auto index = mAdisyonView->currentIndex();
    if( index.isValid() ){
        auto mDialog = new Adisyon::ChangeDialog(mAdisyonModel->index(index.row(),2).data(Qt::DisplayRole).toString().toDouble(),
                                                 mAdisyonModel->index(index.row(),0).data(Qt::DisplayRole).toString());

        QObject::connect(mDialog->acceptBtn(),&QPushButton::clicked,[=](){

            auto urunOid = mAdisyonModel->index(index.row(),0).data(AdisyonModel::Oid).toString();
            Cafe::Urun::UrunItem filter;
            filter.setOid(urunOid.toStdString());
            auto urunItem = mUrunManager->FindOneItem(filter);

            mAdisyonModel->changeUrun(urunItem,mDialog->adetDoubleSpinBox()->value());

            mTotalFiyatLabel->setText("<b>"+QString(TR("Toplam Fiyat"))+" :"+
                                      QString::number(mAdisyonModel->getTotalPrice()) + " " +
                                      mParaBirimiComboBox->currentText()+"</b>");


            mDialog->close();
            delete mDialog;
        });

        QObject::connect(mDialog->rejectBtn(),&QPushButton::clicked,[=](){
            mDialog->close();
            delete mDialog;
        });

        mDialog->exec();
        mAdisyonView->setCurrentIndex(index);
    }else{
        GlobarVar::InformationWidget::instance()->setInformation("Lütfen Listeden Ürün Seçiniz",GlobarVar::InformationWidget::Warn);
    }
}

void AdisyonWidget::removeUrun()
{
    auto index = mAdisyonView->currentIndex();
    if( index.isValid() ){
        auto mDialog = GlobarVar::AskDialog::askQuestion("Silmek İstediğinize Eminsiniz?");
        if( mDialog->status() == GlobarVar::AskDialog::YES ){
            auto urunOid = mAdisyonModel->index(index.row(),0).data(AdisyonModel::Oid).toString();
            Cafe::Urun::UrunItem filter;
            filter.setOid(urunOid.toStdString());
            auto urunItem = mUrunManager->FindOneItem(filter);
            mAdisyonModel->removeUrun(filter);
        }

        delete mDialog;
    }else{
        GlobarVar::InformationWidget::instance()->setInformation("Lütfen Listeden Ürün Seçiniz",GlobarVar::InformationWidget::Warn);
    }
}

} // namespace Adisyon

