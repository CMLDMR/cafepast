
#include "languagetextbankdialog.h"
#include "dialogs/askdialog.h"
#include "model/languagetextmodel.h"
#include "model/languagemodel.h"
#include "global/globalVar.h"
#include "global/informationwidget.h"
#include "textbanktableview.h"

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


    mTextTableView = new TextBankTableView();
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
    mEkleBtn = new QPushButton(TR("Ekle"));

    mAddLayout->addWidget(mCurrentLangLineEdit);
    mAddLayout->addWidget(mDestLangLineEdit);
    mAddLayout->addWidget(mDestLangTextEdit);
    mAddLayout->addWidget(mEkleBtn);
    mMainLayout->addLayout(mAddLayout);

    QObject::connect(mEkleBtn,&QPushButton::clicked,[=](){

        if( mEkleBtn->text().contains("Ekle") ){
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
        }else{

            auto silStr = mTextBankModel->list().at(mTextTableView->currentIndex().row()).getText();
            auto silStrOid = mTextBankModel->list().at(mTextTableView->currentIndex().row()).oid().value().to_string();

            Cafe::Language::TextItem filter;
            filter.setOid(silStrOid);
            filter.setText(mCurrentLangLineEdit->text().toStdString(),mCurrentLangComboBox->currentData(LanguageModel::shortName).toString().toStdString(),mDestLangTextEdit->text().toStdString());

            if( mTextBankModel->UpdateItem(filter) ){
                filter.clear();
                filter.setLang(mCurrentLangComboBox->currentData(LanguageModel::shortName).toString().toStdString());

                mTextBankModel->UpdateList(filter);
                GlobarVar::InformationWidget::instance()->setInformation(TR("Kayıt Başarılı Bir Şekilde Güncellendi"));
            }else{
                GlobarVar::InformationWidget::instance()->setInformation(TR("Kayıt Güncellenemedi"));
            }
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



    QObject::connect(mTextTableView,&QTableView::clicked,[=](const QModelIndex &index){
        mEkleBtn->setText(TR("Değiştir"));
        mDestLangTextEdit->setText(mTextBankModel->list().at(index.row()).getDestText().c_str());
        mCurrentLangLineEdit->setText(mTextBankModel->list().at(index.row()).getText().c_str());
    });

    QObject::connect(mTextTableView,&Language::TextBankTableView::yeniEkleClicked,[=](){
        mEkleBtn->setText(TR("Ekle"));
        mDestLangTextEdit->setText("");
        mCurrentLangLineEdit->setText("");
        mCurrentLangLineEdit->setFocus();
    });

    QObject::connect(mTextTableView,&Language::TextBankTableView::silClicked,[=](){
        mEkleBtn->setText(TR("Ekle"));
        auto silStr = mTextBankModel->list().at(mTextTableView->currentIndex().row()).getText();
        auto silStrOid = mTextBankModel->list().at(mTextTableView->currentIndex().row()).oid().value().to_string();

        auto askDialog = GlobarVar::AskDialog::askQuestion(QString("\"<b>")+QString(silStr.c_str())+QString("</b>\" ")+TR("Silmek istediğinize Emin misiniz?"));


        if( askDialog->status() == GlobarVar::AskDialog::YES ){
            Cafe::Language::TextItem filter;
            filter.setOid(silStrOid);

            if( mTextBankModel->DeleteItem(filter) ){
                filter.clear();
                filter.setLang(mCurrentLangComboBox->currentData(LanguageModel::shortName).toString().toStdString());

                mTextBankModel->UpdateList(filter);
                GlobarVar::InformationWidget::instance()->setInformation(TR("Kayıt Başarılı Bir Şekilde Silindi"));
            }else{
                GlobarVar::InformationWidget::instance()->setInformation(TR("Kayıt Silinemedi"));
            }
        }
    });

    {
        this->setMinimumWidth(350);
        this->setMinimumHeight(450);
    }




}

} // namespace Language

