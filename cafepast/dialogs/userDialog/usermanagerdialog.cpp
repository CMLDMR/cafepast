#include "usermanagerdialog.h"
#include "cafecore/languageitem.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>


#include "usertableview.h"

namespace Cafe {
namespace User {

UserManagerDialog::UserManagerDialog()
{

    this->setWindowTitle(TR("Kullanıcı Yönetimi"));

    mMainLayout = new QVBoxLayout();
    this->setLayout(mMainLayout);


    mUserTableView = new UserTableView();

    mMainLayout->addWidget(mUserTableView);


    mControllerLayout = new QHBoxLayout();
    mMainLayout->addLayout(mControllerLayout);

    mAdsoyadLineEdit = new QLineEdit();
    mAdsoyadLineEdit->setPlaceholderText("AdSoyad Giriniz");
    mControllerLayout->addWidget(mAdsoyadLineEdit);

    QLineEdit* mPasswordLineEdit;

    mUserNameLineEdit = new QLineEdit();
    mUserNameLineEdit->setPlaceholderText("Kullanıcı Adı Giriniz");
    mControllerLayout->addWidget(mUserNameLineEdit);

    mPasswordLineEdit = new QLineEdit();
    mPasswordLineEdit->setPlaceholderText("Şifre Giriniz");
        mPasswordLineEdit->setEchoMode(QLineEdit::EchoMode::PasswordEchoOnEdit);
    mControllerLayout->addWidget(mPasswordLineEdit);

    QPushButton* mSaveButton;

    mSaveButton = new QPushButton("Kaydet");
    mControllerLayout->addWidget(mSaveButton);

    QObject::connect(mSaveButton,&QPushButton::clicked,[=](){
        this->mUserTableView->saveUser(mAdsoyadLineEdit->text(),
                                       mUserNameLineEdit->text(),
                                       mPasswordLineEdit->text());
    });
}

} // namespace User
} // namespace Cafe
