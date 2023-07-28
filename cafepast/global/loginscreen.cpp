#include "loginscreen.h"
#include "global/globalVar.h"
#include "cafecore/languageitem.h"
#include "global/informationwidget.h"

#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>



namespace GlobarVar {

LoginScreen::LoginScreen()
{

    mSubeManager = new Cafe::Sube::SubeModel();

    this->setWindowTitle(TR("Giriş"));

    mMainLayout = new QVBoxLayout();
    this->setLayout(mMainLayout);

    mUserNameLineEdit = new QLineEdit();
    mUserNameLineEdit->setPlaceholderText(TR("Kullanıcı Adını Giriniz"));
    mMainLayout->addWidget(mUserNameLineEdit);

    mPasswordLineEdit = new QLineEdit();
    mPasswordLineEdit->setPlaceholderText(TR("Şifrenizi Giriniz"));
        mPasswordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);
        mMainLayout->addWidget(mPasswordLineEdit);

        mSubeComboBox = new QComboBox();
        mSubeComboBox->setModel(mSubeManager);
        mMainLayout->addWidget(mSubeComboBox);


    mLoginPushButton = new QPushButton(TR("Giriş"));
    mMainLayout->addWidget(mLoginPushButton);

    QObject::connect(mLoginPushButton,&QPushButton::clicked,[=](){

        Cafe::User::UserItem filter;
        filter.setUserName(mUserNameLineEdit->text().toStdString());
        filter.setPassword(mPasswordLineEdit->text().toStdString());

        auto val = this->FindOneItem(filter);

        if( val.view().empty() ){
            GlobarVar::InformationWidget::instance()->setInformation("Hatalı Giriş Bilgisi");
        }else{

            GlobarVar::GlobalDB::global()->setCurrentSube(mSubeComboBox->currentText());
            GlobarVar::GlobalDB::global()->setCurrentUser(&val);

            this->close();
        }



    });
}

} // namespace GlobarVar
