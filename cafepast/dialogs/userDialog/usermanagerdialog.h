#ifndef CAFE_USER_USERMANAGERDIALOG_H
#define CAFE_USER_USERMANAGERDIALOG_H

#include <QDialog>
#include <QObject>

class QVBoxLayout;
class QHBoxLayout;
class QLineEdit;
class QPushButton;

namespace Cafe {
namespace User {

class UserTableView;

class UserManagerDialog : public QDialog
{
    Q_OBJECT
public:
    UserManagerDialog();

private:
    QVBoxLayout* mMainLayout;
    UserTableView* mUserTableView;

    QHBoxLayout* mControllerLayout;
    QLineEdit* mAdsoyadLineEdit;
    QLineEdit* mUserNameLineEdit;
    QLineEdit* mPasswordLineEdit;
    QPushButton* mSaveButton;


};

} // namespace User
} // namespace Cafe

#endif // CAFE_USER_USERMANAGERDIALOG_H
