
#include "languagetextbankdialog.h"
#include "model/languagetextmodel.h"
#include "model/languagemodel.h"
#include "global/globalVar.h"

#include <QVBoxLayout>
#include <QTableView>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>

namespace Language {

LanguageTextBankDialog::LanguageTextBankDialog()
{

    this->setWindowTitle(TR("Sözlük"));

    mLanguageModel = new LanguageModel();
    mLanguageModel->UpdateList();


    mMainLayout = new QVBoxLayout();
    this->setLayout(mMainLayout);

    mTitleLayout = new QHBoxLayout();
    mCurrentLangLabel = new QLabel(QString(TR("Şuanki Sistem Dili"))+QString(": <b>") + GlobarVar::LocalConfiguration::instance()->getCurrentLang().data()+QString("</b>"));
    mCurrentLangComboBox = new QComboBox();
    mCurrentLangComboBox->setModel(mLanguageModel);


    mTitleLayout->addWidget(mCurrentLangLabel);
    mTitleLayout->addWidget(mCurrentLangComboBox);

    mMainLayout->addLayout(mTitleLayout);


    mTextTableView = new QTableView();
    mTextBankModel = new LanguageTextModel();
    mTextTableView->setModel(mTextBankModel);
    mTextBankModel->setDestinationShortLang(GlobarVar::LocalConfiguration::instance()->getCurrentLang());
    mMainLayout->addWidget(mTextTableView);



    mAddLayout = new QHBoxLayout();
    mCurrentLangLineEdit = new QLineEdit();
    mCurrentLangLineEdit->setPlaceholderText(TR("Türkçe Metni Giriniz"));
    mDestLangLineEdit = new QLineEdit();
    mDestLangLineEdit->setEnabled(false);
    mDestLangLineEdit->setText(mCurrentLangComboBox->currentData(LanguageModel::shortName).toString());
    mDestLangTextEdit = new QLineEdit();
    mDestLangTextEdit->setPlaceholderText(TR("Çeviriyi Giriniz"));
    mEkleBtn = new QPushButton(TR("Ekle+"));

    mAddLayout->addWidget(mCurrentLangLineEdit);
    mAddLayout->addWidget(mDestLangLineEdit);
    mAddLayout->addWidget(mDestLangTextEdit);
    mAddLayout->addWidget(mEkleBtn);
    mMainLayout->addLayout(mAddLayout);

    QObject::connect(mEkleBtn,&QPushButton::clicked,[=](){

        Cafe::Language::TextItem item;
        item.setText(mCurrentLangLineEdit->text().toStdString(),
                     mDestLangLineEdit->text().toStdString(),
                     mDestLangTextEdit->text().toStdString());

        auto ins = mTextBankModel->InsertItem(item);
        if( ins.size() ){
            Cafe::Language::TextItem filter;
            filter.setLang(mCurrentLangComboBox->currentData(LanguageModel::shortName).toString().toStdString());
            mTextBankModel->UpdateList(filter);
        }

    });


    QObject::connect(mCurrentLangComboBox,&QComboBox::currentTextChanged,[=]( const QString &currentText){
        if( GlobarVar::LocalConfiguration::instance()->getCurrentLang().data() == mCurrentLangComboBox->currentData(LanguageModel::shortName).toString() ){
            auto str = "<b>"+mCurrentLangComboBox->currentData(LanguageModel::shortName).toString()+"</b>";
            mCurrentLangLabel->setText(QString(TR("Şuanki Sistem Dili")+QString(": "))+str);
                mDestLangLineEdit->setText(mCurrentLangComboBox->currentData(LanguageModel::shortName).toString());

            Cafe::Language::TextItem filter;
            filter.setLang(mCurrentLangComboBox->currentData(LanguageModel::shortName).toString().toStdString());
            mTextBankModel->UpdateList(filter);

        }else{
            auto str = mCurrentLangComboBox->currentData(LanguageModel::langName).toString() + " | "+ mCurrentLangComboBox->currentData(LanguageModel::shortName).toString();
            mCurrentLangLabel->setText(str);
            Cafe::Language::TextItem filter;
            filter.setLang(mCurrentLangComboBox->currentData(LanguageModel::shortName).toString().toStdString());
            mTextBankModel->UpdateList(filter);
            mDestLangLineEdit->setText(mCurrentLangComboBox->currentData(LanguageModel::shortName).toString());

        }

    });


}

} // namespace Language

