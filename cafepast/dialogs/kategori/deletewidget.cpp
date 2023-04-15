
#include "deletewidget.h"
#include "cafecore/languageitem.h"


#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

namespace Kategori {

DeleteWidget::DeleteWidget(QWidget *parent)
    : QWidget{parent}
{

    mMainLayout = new QVBoxLayout();
    this->setLayout(mMainLayout);

    mTitle = new QLabel();
    mTitle->setText(TR("Silmek İstediğinize Emin misiniz?"));
    mMainLayout->addWidget(mTitle);
    mMainLayout->addStretch(1);

    mKategoriName = new QLabel();
    mKategoriName->setText(TR("Kategori Adı"));
        mMainLayout->addWidget(mKategoriName);

    mKategoriOid = new QLabel();
        mKategoriOid->setText("Oid");
    mMainLayout->addWidget(mKategoriOid);

        mMainLayout->addStretch(1);



    mControlLayout = new QHBoxLayout();
    mMainLayout->addLayout(mControlLayout);

    mDelBtn = new QPushButton(TR("Evet"));
    mControlLayout->addWidget(mDelBtn);

    mIptalBtn = new QPushButton(TR("Hayır"));
    mControlLayout->addWidget(mIptalBtn);


}

DeleteWidget::~DeleteWidget()
{

    delete mTitle;  mTitle = nullptr;
    delete mKategoriName; mKategoriName = nullptr;
    delete mKategoriOid; mKategoriOid = nullptr;

    delete mDelBtn; mDelBtn = nullptr;
    delete mIptalBtn; mIptalBtn = nullptr;
    delete mControlLayout; mControlLayout = nullptr;

    delete mMainLayout; mMainLayout = nullptr;

}

QPushButton *DeleteWidget::iptalBtn() const
{
    return mIptalBtn;
}

QPushButton *DeleteWidget::delBtn() const
{
    return mDelBtn;
}

QLabel *DeleteWidget::kategoriOid() const
{
    return mKategoriOid;
}

void DeleteWidget::setKategoriNameOid(const QString &kategoriName, const QString &kategoriOid)
{
    this->mKategoriName->setText(TR(kategoriName.toStdString()));
    this->mKategoriOid->setText(kategoriOid);
}

} // namespace Kategori

