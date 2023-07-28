#include "usertableview.h"

#include "model/usermodel.h"
#include "global/informationwidget.h"
#include "qheaderview.h"

namespace Cafe {
namespace User {

UserTableView::UserTableView()
{

    setSelectionMode(SelectionMode::SingleSelection);
    setSelectionBehavior(SelectionBehavior::SelectRows);
    setAlternatingRowColors(true);
    horizontalHeader()->setStretchLastSection(true);
    setEditTriggers(NoEditTriggers);

    mModel = new UserModel();

    this->setModel(mModel);

}

void UserTableView::saveUser(const QString &adSoyad, const QString &userName, const QString &password)
{

    UserItem item;
    item.setUserName(userName.toStdString());
    item.setAdSoyad(adSoyad.toStdString());
    item.setPassword(password.toStdString());

    if( this->mModel->InsertItem(item).size() ){
        this->mModel->UpdateList();
    }else{
        GlobarVar::InformationWidget::instance()->setInformation("Kayıt Başarısız");
    }
}

} // namespace User
} // namespace Cafe
