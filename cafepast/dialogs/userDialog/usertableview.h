#ifndef CAFE_USER_USERTABLEVIEW_H
#define CAFE_USER_USERTABLEVIEW_H

#include <QTableView>
#include <QObject>

namespace Cafe {
namespace User {

class UserModel;

class UserTableView : public QTableView
{
    Q_OBJECT
public:
    UserTableView();


    void saveUser( const QString &adSoyad,
                  const QString &userName,
                  const QString &password);

private:
    UserModel* mModel;


};

} // namespace User
} // namespace Cafe

#endif // CAFE_USER_USERTABLEVIEW_H
