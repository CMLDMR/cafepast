
#include "askdialog.h"
#include "cafecore/languageitem.h"
#include <mutex>

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>




namespace GlobarVar {



AskDialog::AskDialog(const QString &mQuestionStr,Type type)
{

    mMainLayout = new QVBoxLayout();
    this->setLayout(mMainLayout);

    mQuestionLabel = new QLabel(TR(mQuestionStr.toStdString()));
    mMainLayout->addWidget(mQuestionLabel,0,Qt::AlignmentFlag::AlignCenter);

    mControllerLayout = new QHBoxLayout();

    if( type == Type::Question ){
        mAcceptButton = new QPushButton(TR("Evet"));
        mControllerLayout->addWidget(mAcceptButton);

        mRejectButton = new QPushButton(TR("Hayır"));
        mControllerLayout->addWidget(mRejectButton);
    }else if(type == Type::Message){
        mRejectButton = new QPushButton(TR("Tamam"));
        mControllerLayout->addWidget(mRejectButton);
    }


    mMainLayout->addLayout(mControllerLayout);


}

AskDialog *AskDialog::askQuestion(const QString &questionstr)
{
    auto mDialog = new AskDialog(questionstr,Type::Question);

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

AskDialog *AskDialog::informationDialog(const QString &messageStr)
{
    auto mDialog = new AskDialog(messageStr,Type::Message);

    QObject::connect(mDialog->mRejectButton,&QPushButton::clicked,[=](){
        mDialog->mStatus = NO;
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

