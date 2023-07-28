#ifndef GLOBARVAR_LOGINSCREEN_H
#define GLOBARVAR_LOGINSCREEN_H

#include <QDialog>
#include <QObject>
#include <QWidget>

#include "cafecore/useritem.h"
#include "model/subemodel.h"

class QVBoxLayout;
class QLineEdit;
class QLabel;
class QPushButton;
class QComboBox;

namespace GlobarVar {

class LoginScreen : public QDialog, public Cafe::User::UserManager
{
    Q_OBJECT
public:
    LoginScreen();


private:
    QVBoxLayout* mMainLayout;
    QLineEdit* mUserNameLineEdit;
    QLineEdit* mPasswordLineEdit;
    QComboBox* mSubeComboBox;
    QPushButton* mLoginPushButton;

    Cafe::Sube::SubeModel* mSubeManager;

};

} // namespace GlobarVar

#endif // GLOBARVAR_LOGINSCREEN_H
