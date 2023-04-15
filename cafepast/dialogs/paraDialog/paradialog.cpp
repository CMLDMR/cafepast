
#include "paradialog.h"
#include "model/paraitemmodel.h"
#include "global/globalVar.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLineEdit>


namespace ParaBirimi {

ParaDialog::ParaDialog()
{

    this->setWindowTitle("Para Birimi Seç/Ekle");

    mMainLayout = new QVBoxLayout();
    this->setLayout(mMainLayout);

    mParaDialogTitle = new QLabel(QString("Şuanki Para Birimi: <b><i>") + GlobarVar::LocalConfiguration::instance()->getCurrentParaBirimi().data() + QString("</i></b>"));
                       mParaDialogTitle->setFont(QFont("Tahoma",14));
    mMainLayout->addWidget(mParaDialogTitle);

    mMainLayout->addStretch(1);

    mParaBirimiLayout = new QHBoxLayout();
    mCurrentParaBirimi = new QComboBox();
    mParaItemModel = new ParaItemModel();
    mCurrentParaBirimi->setModel(mParaItemModel);
    mParaBirimiLayout->addWidget(mCurrentParaBirimi);
    mVarsayilanParaBirimiSecBtn = new QPushButton("Varsayılan Seç");
    mParaBiriminiSilBtn = new QPushButton("Sil");
    mParaBirimiLayout->addWidget(mVarsayilanParaBirimiSecBtn);
    QObject::connect(mVarsayilanParaBirimiSecBtn,&QPushButton::clicked,this,&ParaDialog::varsayilanParaSec);
    mParaBirimiLayout->addWidget(mParaBiriminiSilBtn);

    mMainLayout->addLayout(mParaBirimiLayout);

    mMainLayout->addStretch(1);

    mYeniLayout = new QHBoxLayout();
    mYeniParaBirimiLineEdit = new QLineEdit();
    mYeniParaBirimiLineEdit->setPlaceholderText("Yeni Para Birimini Giriniz");
    mYeniLayout->addWidget(mYeniParaBirimiLineEdit);

    mYeniParaBirimiEkle = new QPushButton("Ekle+");
    mYeniLayout->addWidget(mYeniParaBirimiEkle);
    mMainLayout->addLayout(mYeniLayout);

    QObject::connect(mYeniParaBirimiEkle,&QPushButton::clicked,[=](){

        Cafe::ParaBirimi::ParaItem paraItem;
        paraItem.setParaName(mYeniParaBirimiLineEdit->text().toStdString());

        auto ins = mParaItemModel->InsertItem(paraItem);

        if( ins.size() ){
            mParaItemModel->UpdateList();
        }
    });

    mParaItemModel->UpdateList();

    this->setMinimumHeight(150);
    this->setMinimumWidth(350);

}

void ParaDialog::varsayilanParaSec()
{
    auto currentParaBirimiText = mCurrentParaBirimi->currentText().toStdString();
    GlobarVar::LocalConfiguration::instance()->setCurrentParaBirimi(currentParaBirimiText);

    mParaDialogTitle->setText(QString("Şuanki Para Birimi: <b><i>") + GlobarVar::LocalConfiguration::instance()->getCurrentParaBirimi().data() + QString("</i></b>"));

}

} // namespace ParaBirimi

