
#include "otheroptionsdialog.h"
#include "global/globalVar.h"
#include "global/informationwidget.h"
#include "cafecore/languageitem.h"

#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>


namespace Other {

OtherOptionsDialog::OtherOptionsDialog()
{

    this->setWindowTitle(TR("Şirket Adını Değiştir"));
    mMainLayout = new QVBoxLayout();
    this->setLayout(mMainLayout);

    mTitleLabel = new QLabel();
    mTitleLabel->setText(TR("Şirket Adı"));
    mMainLayout->addWidget(mTitleLabel);

    mCafeNameLineEdit = new QLineEdit();
    mCafeNameLineEdit->setPlaceholderText(TR("Şirket Adını Giriniz"));
    mCafeNameLineEdit->setText(GlobarVar::LocalConfiguration::instance()->getCorpName().c_str());

    mMainLayout->addWidget(mCafeNameLineEdit);

    mControllerLayout = new QHBoxLayout();
    mMainLayout->addLayout(mControllerLayout);

    mAcceptedBtn = new QPushButton(TR("Tamam"));
    mControllerLayout->addWidget(mAcceptedBtn);

    mRejectedBtn = new QPushButton(TR("İptal"));
    mControllerLayout->addWidget(mRejectedBtn);


    QObject::connect(mRejectedBtn,&QPushButton::clicked,[=](){

        this->close();
    });


    QObject::connect(mAcceptedBtn,&QPushButton::clicked,[=](){
        GlobarVar::LocalConfiguration::instance()->setCorpName(mCafeNameLineEdit->text().toStdString().c_str());
        GlobarVar::InformationWidget::instance()->setInformation("Şirket Adı Değiştirildi");
        this->close();

    });

}

} // namespace Other

