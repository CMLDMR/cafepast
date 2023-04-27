
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
#include <QPainter>
#include <QPrintDialog>
#include <QPrinter>
#include <QPrintPreviewDialog>


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
    mSayiDegisBtn = new QPushButton(TR("Sayı Değiştir"));

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

    mSilSelectedBtn = new QPushButton(TR("Sil"));
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

    mAdisyonPreviewLabel = new QLabel(TR("Adisyon"));
    mAdisyonPreviewLabel->setGeometry(0,0,350,1000);
    mAdisyonPreviewScrollArea->setWidget(mAdisyonPreviewLabel);

//    mAdisyonPreviwImage = new QImage("adisyon.jpg");
//    if( mAdisyonPreviwImage->load("adisyon.jpg") ){
//        *mAdisyonPreviwImage = mAdisyonPreviwImage->scaledToWidth(350);
//        mAdisyonPreviewLabel->setGeometry(0,0,350,mAdisyonPreviwImage->height());
//        mAdisyonPreviewLabel->setPixmap(QPixmap::fromImage(*mAdisyonPreviwImage));
//    }

    mAdisyonPreviewPrintBtn = new QPushButton(TR("Yazdır"));
                              mAdisyonPreviewLayout->addWidget(mAdisyonPreviewPrintBtn);

    mUrunManager = new Cafe::Urun::UrunManager();

    mAdisyonModel->setCurrentParaBirimi(mParaBirimiComboBox->currentText());
    QObject::connect(mParaBirimiComboBox,&QComboBox::currentIndexChanged,[=](const int index){
        mAdisyonModel->setCurrentParaBirimi(mParaBirimiComboBox->itemText(index));
        mTotalFiyatLabel->setText("<b>"+QString(TR("Toplam Tutar"))+" :"+QString::number(mAdisyonModel->getTotalPrice()) + " " + mParaBirimiComboBox->currentText()+"</b>");
        this->paintAdisyon();

    });

    mAdisyonView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
    mAdisyonView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    mAdisyonView->setSelectionMode(QAbstractItemView::SingleSelection);

    QObject::connect(mSayiArtirBtn,&QPushButton::clicked,this,&AdisyonWidget::incrementUrun);
    QObject::connect(mSayiAzaltBtn,&QPushButton::clicked,this,&AdisyonWidget::decrementUrun);
    QObject::connect(mSayiDegisBtn,&QPushButton::clicked,this,&AdisyonWidget::changeUrunAdet);
    QObject::connect(mSilSelectedBtn,&QPushButton::clicked,this,&AdisyonWidget::removeUrun);
    QObject::connect(mAdisyonPreviewPrintBtn,&QPushButton::clicked,this,&AdisyonWidget::printReceipt);

    paintAdisyon();

}

void AdisyonWidget::addUrun(const QString &urunOid)
{
    Cafe::Urun::UrunItem filter;
    filter.setOid(urunOid.toStdString());
    auto urunItem = mUrunManager->FindOneItem(filter);

    mAdisyonModel->addUrun(urunItem);

    mTotalFiyatLabel->setText("<b>"+QString(TR("Toplam Tutar"))+" :"+
                              QString::number(mAdisyonModel->getTotalPrice()) + " " +
                              mParaBirimiComboBox->currentText()+"</b>");

    this->paintAdisyon();
}

void AdisyonWidget::reduceUrun(const QString &urunOid)
{
    Cafe::Urun::UrunItem filter;
    filter.setOid(urunOid.toStdString());
    auto urunItem = mUrunManager->FindOneItem(filter);

    mAdisyonModel->reduceUrun(urunItem);

    mTotalFiyatLabel->setText("<b>"+QString(TR("Toplam Tutar"))+" :"+
                              QString::number(mAdisyonModel->getTotalPrice()) + " " +
                              mParaBirimiComboBox->currentText()+"</b>");
        this->paintAdisyon();
}

void AdisyonWidget::paintAdisyon()
{

        int heightPix = 200;

        for( int i = 0 ; i < mAdisyonModel->rowCount() ; i++ ){
            heightPix += 20;
        }

        const int imgWidth = 350;

    if( mAdisyonPreviwImage ){
        delete mAdisyonPreviwImage;
        mAdisyonPreviwImage = new QImage(350,heightPix,QImage::Format_RGB888);
    }else{
        mAdisyonPreviwImage = new QImage(350,heightPix,QImage::Format_RGB888);
    }


    mAdisyonPreviwImage->fill(QColor(Qt::GlobalColor::white));

    QPainter painter(mAdisyonPreviwImage);

    auto font = painter.font();

//    painter.drawRect(10,10,330,50);

    painter.setFont(QFont("Tahoma",18));

    painter.drawText(80,40,GlobarVar::LocalConfiguration::instance()->getCorpName().c_str());

        painter.setFont(font);
    painter.drawText(20,75,QDate::currentDate().toString("dd/MM/yyyy"));
        painter.drawText(300,75,QTime::currentTime().toString("hh:mm"));


    painter.setFont(QFont("Tahoma",12));
    painter.drawText(125,100,TR("Siparişler"));
        painter.setFont(font);


        painter.drawText(20,130,TR("Menü"));
        painter.drawText(180,130,TR("Adet"));
        painter.drawText(270,130,TR("Fiyat"));
        painter.drawLine(20,135,330,135);


        double mTotalPrice = 0;
    int lastYPos = 135;
    for( int i = 0 ; i < mAdisyonModel->rowCount() ; i++ ){
        painter.drawText(20,i*20+155,mAdisyonModel->index(i,0).data(Qt::DisplayRole).toString());
        painter.drawText(180,i*20+155,mAdisyonModel->index(i,2).data(Qt::DisplayRole).toString());
        painter.drawText(270,i*20+155,mAdisyonModel->index(i,3).data(Qt::DisplayRole).toString());
        mTotalPrice += mAdisyonModel->index(i,3).data(Qt::DisplayRole).toDouble();
        lastYPos = i*20+155;
    }
    lastYPos += 5;
    painter.drawLine(20,lastYPos,330,lastYPos);

    lastYPos += 15;
    painter.drawText(200,lastYPos,QString(TR("Toplam Tutar") + QString(" :") +QString::number(mTotalPrice)+ " " + mParaBirimiComboBox->currentText()));


    lastYPos += 30;
    painter.setFont(QFont("Tahoma",13,-1,true));
    painter.drawText(125,lastYPos,QString(TR("Teşekkürler")));




    mAdisyonPreviewLabel->setGeometry(0,0,350,mAdisyonPreviwImage->height());
    mAdisyonPreviewLabel->setPixmap(QPixmap::fromImage(*mAdisyonPreviwImage));


}

void AdisyonWidget::incrementUrun()
{
    auto index = mAdisyonView->currentIndex();
    if( index.isValid() ){
        this->addUrun(mAdisyonModel->index(index.row(),0).data(AdisyonModel::Oid).toString());
        mAdisyonView->setCurrentIndex(index);
            this->paintAdisyon();
    }
}

void AdisyonWidget::decrementUrun()
{
    auto index = mAdisyonView->currentIndex();
    if( index.isValid() ){
        this->reduceUrun(mAdisyonModel->index(index.row(),0).data(AdisyonModel::Oid).toString());
        mAdisyonView->setCurrentIndex(index);
            this->paintAdisyon();
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

            mTotalFiyatLabel->setText("<b>"+QString(TR("Toplam Tutar"))+" :"+
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
            this->paintAdisyon();
    }else{
            GlobarVar::InformationWidget::instance()->setInformation(TR("Lütfen Listeden Ürün Seçiniz"),GlobarVar::InformationWidget::Warn);
    }
}

void AdisyonWidget::removeUrun()
{
    auto index = mAdisyonView->currentIndex();
    if( index.isValid() ){
            auto mDialog = GlobarVar::AskDialog::askQuestion(("Silmek İstediğinize Eminsiniz?"));
        if( mDialog->status() == GlobarVar::AskDialog::YES ){
            auto urunOid = mAdisyonModel->index(index.row(),0).data(AdisyonModel::Oid).toString();
            Cafe::Urun::UrunItem filter;
            filter.setOid(urunOid.toStdString());
            auto urunItem = mUrunManager->FindOneItem(filter);
            mAdisyonModel->removeUrun(filter);
        }

        delete mDialog;
            this->paintAdisyon();
    }else{
            GlobarVar::InformationWidget::instance()->setInformation(TR("Lütfen Listeden Ürün Seçiniz"),GlobarVar::InformationWidget::Warn);
    }
}

void AdisyonWidget::printReceipt()
{

    const int yPos = 35;

    QPrinter printer;
    printer.setOutputFormat(QPrinter::NativeFormat);
//    printer.setResolution(QPrinter::PrinterMode::PrinterResolution);
//    printer.setOutputFileName("nonwrite.pdf");
//    printer.setPageSize(QPageSize(printImg.size()));
    QPainter painter;
    if (! painter.begin(&printer)) { // failed to open file
            qWarning("failed to open file, is it writable?");
            return;
    }
    painter.setFont(QFont("Tahoma",20));

    auto font = painter.font();

    painter.setPen(QPen(Qt::SolidLine));
    painter.setPen(QPen(Qt::GlobalColor::black));

    painter.setFont(QFont("Tahoma",16));

    painter.drawText(0,yPos,GlobarVar::LocalConfiguration::instance()->getCorpName().c_str());

    painter.setFont(QFont("Tahoma",7));

    painter.drawText(0,yPos+10,QDate::currentDate().toString("dd/MM/yyyy"));
    painter.drawText(155,yPos+10,QTime::currentTime().toString("hh:mm"));


    painter.setFont(QFont("Tahoma",10));
    painter.drawText(55,60,TR("Siparişler"));

    painter.setFont(QFont("Tahoma",9));
    painter.drawText(0,75,TR("Menü"));
    painter.drawText(120,75,TR("Adet"));
    painter.drawText(150,75,TR("Fiyat"));
//    painter.drawLine(20,72,740,72);


    painter.setFont(QFont("Tahoma",10));
    painter.drawText(0,83,"-------------------------------------------------------------");
    painter.setFont(QFont("Tahoma",8));

    double mTotalPrice = 0;
    int lastYPos = 91;
    for( int i = 0 ; i < mAdisyonModel->rowCount() ; i++ ){
            painter.drawText(0,i*12+94,mAdisyonModel->index(i,0).data(Qt::DisplayRole).toString());
            painter.drawText(120,i*12+94,mAdisyonModel->index(i,2).data(Qt::DisplayRole).toString());
            painter.drawText(160,i*12+94,mAdisyonModel->index(i,3).data(Qt::DisplayRole).toString());
            mTotalPrice += mAdisyonModel->index(i,3).data(Qt::DisplayRole).toDouble();
            lastYPos = i*12+94;
    }
    lastYPos += 13;

    painter.setFont(QFont("Tahoma",10));

    painter.drawText(0,lastYPos,"-------------------------------------------------------------");

    lastYPos += 15;
    painter.setFont(QFont("Tahoma",10));

    painter.drawText(0,lastYPos,QString(TR("Toplam Tutar") + QString(" :") +QString::number(mTotalPrice)+ " " + mParaBirimiComboBox->currentText()));


    lastYPos += 25;
    painter.setFont(QFont("Tahoma",10,-1,true));
    painter.drawText(0,lastYPos,QString(TR("Teşekkürler | ")+QString("Telefon Numarası")));


    painter.end();

    QPrintPreviewDialog preview_dlg(&printer);
    QObject::connect(&preview_dlg, &QPrintPreviewDialog::paintRequested,[=](QPrinter* printer){



    });
    preview_dlg.open();


//    QPrintDialog dialog(&printer, this);
//    dialog.setWindowTitle("Adisyon Yazdır");


//    if(dialog.exec() != QDialog::Accepted){

//    }

}

} // namespace Adisyon

