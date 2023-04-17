
#include "paradialog.h"
#include "model/paraitemmodel.h"
#include "cafecore/languageitem.h"

#include "global/globalVar.h"
#include "global/informationwidget.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLineEdit>


namespace ParaBirimi {

ParaDialog::ParaDialog()
{

    this->setWindowTitle(TR("Para Birimi Seç/Ekle"));

    mMainLayout = new QVBoxLayout();
    this->setLayout(mMainLayout);

    mParaDialogTitle = new QLabel(TR("Şuanki Para Birimi") +QString(": <b><i>") + GlobarVar::LocalConfiguration::instance()->getCurrentParaBirimi().data() + QString("</i></b>"));
                       mParaDialogTitle->setFont(QFont("Tahoma",14));
    mMainLayout->addWidget(mParaDialogTitle);

    mMainLayout->addStretch(1);

    mParaBirimiLayout = new QHBoxLayout();
    mCurrentParaBirimi = new QComboBox();
    mParaItemModel = new ParaItemModel();
    mCurrentParaBirimi->setModel(mParaItemModel);
    mParaBirimiLayout->addWidget(mCurrentParaBirimi);
    mVarsayilanParaBirimiSecBtn = new QPushButton(TR("Varsayılan Yap"));
        mParaBiriminiSilBtn = new QPushButton(TR("Sil"));
    mParaBirimiLayout->addWidget(mVarsayilanParaBirimiSecBtn);
    QObject::connect(mVarsayilanParaBirimiSecBtn,&QPushButton::clicked,this,&ParaDialog::varsayilanParaSec);
    mParaBirimiLayout->addWidget(mParaBiriminiSilBtn);

    mMainLayout->addLayout(mParaBirimiLayout);

    mMainLayout->addStretch(1);

    mYeniLayout = new QHBoxLayout();
    mYeniParaBirimiLineEdit = new QLineEdit();
    mYeniParaBirimiLineEdit->setPlaceholderText(TR("Yeni Para Birimini Giriniz"));
    mYeniLayout->addWidget(mYeniParaBirimiLineEdit);

    mYeniParaBirimiEkle = new QPushButton(TR("Ekle+"));
    mYeniLayout->addWidget(mYeniParaBirimiEkle);
    mMainLayout->addLayout(mYeniLayout);

    QObject::connect(mYeniParaBirimiEkle,&QPushButton::clicked,[=](){

        Cafe::ParaBirimi::ParaItem paraItem;
        paraItem.setParaName(mYeniParaBirimiLineEdit->text().toStdString());

        auto count = mParaItemModel->countItem(paraItem);
        if( count ){
            GlobarVar::InformationWidget::instance()->setInformation(TR("Para Birimi Zaten Var"));
            return;
        }

        auto ins = mParaItemModel->InsertItem(paraItem);

        if( ins.size() ){
            GlobarVar::InformationWidget::instance()->setInformation(TR("Para Birimi Eklendi"));
            mParaItemModel->UpdateList();
        }else{
            GlobarVar::InformationWidget::instance()->setInformation(TR("Hata: "+mParaItemModel->getLastError()));
        }
    });

    mParaItemModel->UpdateList();

    this->setMinimumHeight(150);
    this->setMinimumWidth(350);

}

void ParaDialog::varsayilanParaSec()
{
    auto currentParaBirimiText = mCurrentParaBirimi->currentText().toStdString();
    if( currentParaBirimiText != GlobarVar::LocalConfiguration::instance()->getCurrentParaBirimi() ){
        GlobarVar::LocalConfiguration::instance()->setCurrentParaBirimi(currentParaBirimiText);
        mParaDialogTitle->setText(TR("Şuanki Para Birimi") + QString(": <b><i>") + GlobarVar::LocalConfiguration::instance()->getCurrentParaBirimi().data() + QString("</i></b>"));
            GlobarVar::InformationWidget::instance()->setInformation(TR("Sistem Para Birimi Değiştirildi.\nLütfen Uygulamayı Tekrar Başlatın"));
    }else{
            GlobarVar::InformationWidget::instance()->setInformation(TR("Sistemde Zaten Bu Para Birimi Seçili"));

    }


}

} // namespace ParaBirimi

