
#include "yenieklewidget.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

namespace Kategori {

YeniEkleWidget::YeniEkleWidget(QWidget *parent)
    : QWidget{parent}
{

    mLayout = std::make_unique<QVBoxLayout>();

    this->setLayout(mLayout.get());


    mLayout->addWidget(new QLabel("Yeni Ekle"));


    mKategoriAdiLineEdit = std::make_unique<QLineEdit>();
    mKategoriAdiLineEdit->setPlaceholderText("Yeni Kategori Adını Giriniz");
    mLayout->addWidget(mKategoriAdiLineEdit.get());

    mLayout->addStretch(1);

    mEkleBtn = std::make_unique<QPushButton>("Ekle+");
    mLayout->addWidget(mEkleBtn.get());
    QObject::connect(mEkleBtn.get(),&QPushButton::clicked,[=](){
        mEkleBtn->setText("Ekle+");
        emit yeniClicked(this->mKategoriAdiLineEdit->text());
    });

    mIptalBtn = std::make_unique<QPushButton>("İptal");
                mLayout->addWidget(mIptalBtn.get());
    QObject::connect(mIptalBtn.get(),&QPushButton::clicked,[=](){
                    mEkleBtn->setText("Ekle+");
                    mKategoriAdiLineEdit->setText("");
                    emit this->iptalClicked();
    });



}

void YeniEkleWidget::setCurrentKategoriName(const QString &currentKategoriName)
{
    this->mKategoriAdiLineEdit->setText(currentKategoriName);
    qDebug() << currentKategoriName;
    if( currentKategoriName.isEmpty() ){
        mEkleBtn->setText("Ekle+");
    }else{
        mEkleBtn->setText("Değiştir");
    }
}



} // namespace Kategori

