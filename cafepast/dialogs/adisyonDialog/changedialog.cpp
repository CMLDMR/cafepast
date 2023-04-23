
#include "changedialog.h"
#include "cafecore/languageitem.h"

#include <QHBoxLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QPushButton>


namespace Adisyon {

ChangeDialog::ChangeDialog(const double Adet, const QString &urunAdi)
    :mAdet(Adet)
{


    mMainLayout = new QVBoxLayout();
    this->setLayout(mMainLayout);

    mMainLayout->addStretch(1);

    mTitleLabel = new QLabel(TR("Adet Değiştir"));
    mMainLayout->addWidget(mTitleLabel);

    mAdetDoubleSpinBox = new QDoubleSpinBox();
    mAdetDoubleSpinBox->setValue(mAdet);
    mMainLayout->addWidget(mAdetDoubleSpinBox);

    mControllerLayout = new QHBoxLayout();
    mAcceptBtn = new QPushButton(TR("Değiştir"));
    mRejectBtn = new QPushButton(TR("İptal"));
                 mControllerLayout->addWidget(mAcceptBtn);
    mControllerLayout->addWidget(mRejectBtn);
    mMainLayout->addLayout(mControllerLayout);
    setWindowTitle(QString(TR(urunAdi.toStdString()))+QString(" | ")+TR("Adet Değiştir"));
}

QDoubleSpinBox *ChangeDialog::adetDoubleSpinBox() const
{
    return mAdetDoubleSpinBox;
}

QPushButton *ChangeDialog::acceptBtn() const
{
    return mAcceptBtn;
}

QPushButton *ChangeDialog::rejectBtn() const
{
    return mRejectBtn;
}

} // namespace Adisyon

