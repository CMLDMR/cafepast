
#include "languagedialog.h"
#include "model/languagemodel.h"
#include "global/globalVar.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

namespace Language {

LanguageDialog::LanguageDialog()
{

    setWindowTitle("Dil Seçimi/Düzenleme");

    mLangModel = new LanguageModel();

    mMainLayout = new QVBoxLayout();
    this->setLayout(mMainLayout);

    mTitleLabel = new QLabel(QString("Şuanki Dil: <b><i>") + GlobarVar::LocalConfiguration::instance()->getCurrentLang().data()+QString("</i></b>"));
    mTitleLabel->setFont(QFont("Tahoma",14));
    mMainLayout->addWidget(mTitleLabel);

    mMainLayout->addStretch(1);

    mSelectLangLayout = new QHBoxLayout();
    mDilComboBox = new QComboBox();
    mDilComboBox->setModel(mLangModel);
    mSelectLangLayout->addWidget(mDilComboBox);

    mVarsayilanYapBtn = new QPushButton("Varsayılan Yap");
    mSelectLangLayout->addWidget(mVarsayilanYapBtn);
    mMainLayout->addLayout(mSelectLangLayout);


    mMainLayout->addStretch(1);

    mYeniDilEkleLayout = new QHBoxLayout();
    mLanguageNameLineEdit = new QLineEdit();
    mLanguageShortNameLineEdit = new QLineEdit();
    mEkleButton = new QPushButton("Ekle+");

    mYeniDilEkleLayout->addWidget(mLanguageNameLineEdit);
    mLanguageNameLineEdit->setPlaceholderText("Yeni Dilin Tam Adını Giriniz");
    mYeniDilEkleLayout->addWidget(mLanguageShortNameLineEdit);
    mLanguageShortNameLineEdit->setPlaceholderText("Yeni Dilin Kısaltmasını Giriniz... (en)");
    mYeniDilEkleLayout->addWidget(mEkleButton);

    mMainLayout->addLayout(mYeniDilEkleLayout);

    QObject::connect(mEkleButton,&QPushButton::clicked,[=](){
        Cafe::Language::LanguageItem item;
        item.setLang(mLanguageNameLineEdit->text().toStdString(),mLanguageShortNameLineEdit->text().toStdString());

        auto ins = this->mLangModel->InsertItem(item);
        if( ins.size() ){
            mLangModel->UpdateList();
        }
    });


    QObject::connect(mVarsayilanYapBtn,&QPushButton::clicked,[=](){
        GlobarVar::LocalConfiguration::instance()->setCurrentLang(mDilComboBox->currentData(Language::LanguageModel::shortName).toString().toStdString());
        mTitleLabel->setText(QString("Şuanki Dil: <b><i>") + GlobarVar::LocalConfiguration::instance()->getCurrentLang().data()+QString("</i></b>"));

    });


}

} // namespace Language

