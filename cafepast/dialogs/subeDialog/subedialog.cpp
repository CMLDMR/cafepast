#include "subedialog.h"
#include "global/informationwidget.h"
#include "cafecore/languageitem.h"

#include "subetableview.h"
#include "model/subemodel.h"

#include <QVBoxLayout>
#include <QTableView>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

namespace Cafe {
namespace Sube {

SubeDialog::SubeDialog()
{

    this->setWindowTitle(TR("Şubeler"));

    mMainLayout = new QVBoxLayout();
    this->setLayout(mMainLayout);

    mSubeTableView = new SubeTableView();
    mMainLayout->addWidget(mSubeTableView);



    mControllerLayout = new QHBoxLayout();
    mMainLayout->addLayout(mControllerLayout);

    mSubeAdiLineEdit = new QLineEdit();
    mSubeAdiLineEdit->setPlaceholderText(TR("Şube Adını Giriniz"));
    mControllerLayout->addWidget(mSubeAdiLineEdit);
    mSubeTelefonLineEdit = new QLineEdit();
    mSubeTelefonLineEdit->setPlaceholderText(TR("Telefon Numarası Giriniz"));
    mControllerLayout->addWidget(mSubeTelefonLineEdit);
    mSubeAdresLineEdit = new QLineEdit();
    mSubeAdresLineEdit->setPlaceholderText(TR("Adresi Giriniz"));

    mControllerLayout->addWidget(mSubeAdresLineEdit);


    mSaveButton = new QPushButton(TR("Kaydet"));
    mControllerLayout->addWidget(mSaveButton);

    QObject::connect(mSaveButton,&QPushButton::clicked,this,&Cafe::Sube::SubeDialog::saveSube);


    QObject::connect(mSubeTableView,&QTableView::clicked,[=](const QModelIndex &index){
        mSaveButton->setText(TR("Değiştir"));
        mSelectedSubeOid = mSubeTableView->model()->list().at(index.row()).oid().value().to_string().c_str();
        mSubeAdiLineEdit->setText(mSubeTableView->model()->list().at(index.row()).getSubeAdi().c_str());
        mSubeAdresLineEdit->setText(mSubeTableView->model()->list().at(index.row()).getSubeAdresi().c_str());
        mSubeTelefonLineEdit->setText(mSubeTableView->model()->list().at(index.row()).getSubeTelefon().c_str());

    });

    QObject::connect(mSubeTableView,&SubeTableView::newSaveClicked,[=](){
        mSaveButton->setText(TR("Ekle+"));
        mSelectedSubeOid = "";
        mSubeAdiLineEdit->setText("");
        mSubeAdresLineEdit->setText("");
        mSubeTelefonLineEdit->setText("");
        mSubeAdiLineEdit->setFocus();
    });

//    this->setGeometry(this->geometry().top(),this->geometry().left(),450,250);
}

SubeDialog::~SubeDialog()
{
    delete mSubeTableView;

    delete mMainLayout;
    mMainLayout = nullptr;
}

} // namespace Sube
} // namespace Cafe



void Cafe::Sube::SubeDialog::saveSube()
{

    if( mSaveButton->text() == "Değiştir" ){

        Sube::SubeItem filter;
        filter.setOid(mSelectedSubeOid.toStdString());
        filter.setSubeAdi(mSubeAdiLineEdit->text().toStdString());
        filter.setSubeAdresi(mSubeAdresLineEdit->text().toStdString());
        filter.setSubeTelefon(mSubeTelefonLineEdit->text().toStdString());



        if( this->mSubeTableView->model()->UpdateItem(filter) ){
            this->mSubeTableView->model()->UpdateList();
            GlobarVar::InformationWidget::instance()->setInformation("Bilgiler Güncellendi");
        }else{
            GlobarVar::InformationWidget::instance()->setInformation("Şube Bilgileri Güncellenemedi");
        }

    }else{

        this->mSubeTableView->saveSube(mSubeAdiLineEdit->text(),
                                       mSubeAdresLineEdit->text(),
                                       mSubeTelefonLineEdit->text());

        mSubeAdiLineEdit->setText("");
        mSubeAdresLineEdit->setText("");
        mSubeTelefonLineEdit->setText("");
    }



}
