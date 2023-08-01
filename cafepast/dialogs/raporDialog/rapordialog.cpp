#include "rapordialog.h"

#include "view.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

#include "cafecore/languageitem.h"


namespace Cafe {
namespace Rapor {

RaporDialog::RaporDialog()
{
    this->setWindowTitle("Rapolar");

    mMainLayout = std::make_unique<QVBoxLayout>();

    this->setLayout(mMainLayout.get());

    mView = std::make_unique<View>();
    mMainLayout->addWidget(mView.get());

    mControlLayout = std::make_unique<QHBoxLayout>();
    mMainLayout->addLayout(mControlLayout.get());


    mGunlukRaporBtn = std::make_unique<QPushButton>(TR("Günlük"));
    mControlLayout->addWidget(mGunlukRaporBtn.get());


    mHaftalikRaporBtn = std::make_unique<QPushButton>(TR("Haftalık"));
    mControlLayout->addWidget(mHaftalikRaporBtn.get());

    mAylikRaporBtn = std::make_unique<QPushButton>(TR("Aylık"));
    mControlLayout->addWidget(mAylikRaporBtn.get());

}

} // namespace Rapor
} // namespace Cafe
