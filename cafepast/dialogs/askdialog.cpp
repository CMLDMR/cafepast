
#include "askdialog.h"
#include "cafecore/languageitem.h"
#include <mutex>

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>




namespace GlobarVar {



AskDialog::AskDialog(const QString &mQuestionStr)
{

    mMainLayout = new QVBoxLayout();
    this->setLayout(mMainLayout);

    mQuestionLabel = new QLabel(TR(mQuestionStr.toStdString()));
    mMainLayout->addWidget(mQuestionLabel,0,Qt::AlignmentFlag::AlignCenter);

    mControllerLayout = new QHBoxLayout();
    mAcceptButton = new QPushButton(TR("Evet"));
    mControllerLayout->addWidget(mAcceptButton);

    mRejectButton = new QPushButton(TR("Hayır"));
    mControllerLayout->addWidget(mRejectButton);

    mMainLayout->addLayout(mControllerLayout);


}

AskDialog *AskDialog::askQuestion(const QString &questionstr)
{
    auto mDialog = new AskDialog(questionstr);

    QObject::connect(mDialog->mRejectButton,&QPushButton::clicked,[=](){
        mDialog->mStatus = NO;
        mDialog->close();
    });

    QObject::connect(mDialog->mAcceptButton,&QPushButton::clicked,[=](){
        mDialog->mStatus = YES;
        mDialog->close();
    });

    mDialog->exec();

    return mDialog;
}

AskDialog::AcceptedButton AskDialog::status() const
{
    return mStatus;
}

} // namespace GlobarVar

