
#include "deletewidget.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

namespace Kategori {

DeleteWidget::DeleteWidget(QWidget *parent)
    : QWidget{parent}
{

    mMainLayout = new QVBoxLayout(this);
//    this->setLayout(mMainLayout);

    mTitle = new QLabel(this);
    mTitle->setText("Silmek İstediğinize Emin misiniz?");
    mMainLayout->addWidget(mTitle);
    mMainLayout->addStretch(1);

    mKategoriName = new QLabel(this);
    mKategoriName->setText("Kategori Adı");
        mMainLayout->addWidget(mKategoriName);

    mKategoriOid = new QLabel(this);
        mKategoriOid->setText("Oid");
    mMainLayout->addWidget(mKategoriOid);

        mMainLayout->addStretch(1);



    mControlLayout = new QHBoxLayout();
    mDelBtn = new QPushButton("Evet");
    mControlLayout->addWidget(mDelBtn);

    mIptalBtn = new QPushButton("Hayır");
    mControlLayout->addWidget(mIptalBtn);

    mMainLayout->addLayout(mControlLayout);


}

DeleteWidget::~DeleteWidget()
{
    delete mMainLayout; mMainLayout = nullptr;
    delete mTitle;  mTitle = nullptr;
    delete mKategoriName; mKategoriName = nullptr;
    delete mKategoriOid; mKategoriOid = nullptr;
    delete mControlLayout; mControlLayout = nullptr;
    delete mDelBtn; mDelBtn = nullptr;
    delete mIptalBtn; mIptalBtn = nullptr;
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

} // namespace Kategori

