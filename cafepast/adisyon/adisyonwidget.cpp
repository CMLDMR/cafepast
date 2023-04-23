
#include "adisyonwidget.h"
#include "adisyonmodel.h"
#include "cafecore/languageitem.h"
#include "cafecore/urunitem.h"
#include "model/paraitemmodel.h"
#include "global/globalVar.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableView>
#include <QHeaderView>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>
#include <QComboBox>

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
    });
}

void AdisyonWidget::addUrun(const QString &urunOid)
{
    Cafe::Urun::UrunItem filter;
    filter.setOid(urunOid.toStdString());
    auto urunItem = mUrunManager->FindOneItem(filter);

    mAdisyonModel->addUrun(urunItem);
}

} // namespace Adisyon

