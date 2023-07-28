#include "subetableview.h"
#include <QHeaderView>

#include "cafecore/languageitem.h"
#include "global/informationwidget.h"
#include "model/subemodel.h"
#include "qevent.h"

#include <QAction>
#include <QMenu>
#include <QMessageBox>
#include <QPushButton>
#include <QContextMenuEvent>

namespace Cafe {
namespace Sube {

SubeModel *SubeTableView::model() const
{
    return mModel;
}



SubeTableView::SubeTableView()
{
    setSelectionMode(SelectionMode::SingleSelection);
    setSelectionBehavior(SelectionBehavior::SelectRows);
    setAlternatingRowColors(true);
    horizontalHeader()->setStretchLastSection(true);
    setEditTriggers(NoEditTriggers);

    mModel = new SubeModel();
    this->setModel(mModel);
}

SubeTableView::~SubeTableView()
{
    delete mModel;

}

void SubeTableView::saveSube(const QString &subeAdi, const QString &telefon, const QString &adres)
{

    Cafe::Sube::SubeItem item;
    item.setSubeAdi(subeAdi.toStdString());
    item.setSubeAdresi(telefon.toStdString());
    item.setSubeTelefon(adres.toStdString());


    auto ins = this->mModel->InsertItem(item);
    if( !ins.empty() ){
        GlobarVar::InformationWidget::instance()->setInformation("Şube Kayıt Edildi");
        this->mModel->UpdateList();
    }else{
        GlobarVar::InformationWidget::instance()->setInformation("Şube Kayıt Edilemedi!");
    }
}

} // namespace Sube
} // namespace Cafe


void Cafe::Sube::SubeTableView::contextMenuEvent(QContextMenuEvent *event)
{

    if( this->currentIndex().row() < 0 ){
        return;
    }



    QMenu menu;

    auto urunAdiChangeAction = menu.addAction(TR("Yeni Ekle"));
    QObject::connect(urunAdiChangeAction,&QAction::triggered,[=](){
        emit newSaveClicked();
    });


    auto delAction = menu.addAction(TR("Sil"));
    QObject::connect(delAction,&QAction::triggered,[=](){

        auto msgBox = std::make_unique<QMessageBox>();

        msgBox->setWindowTitle(TR("Sil")+QString("?"));

        msgBox->setText(this->currentIndex().data(Qt::DisplayRole).toString() + " "+ TR("Silmek istediğinize Emin misiniz?"));

            auto yesButton = msgBox->addButton(TR("Evet"),QMessageBox::AcceptRole);
        msgBox->addButton(TR("Hayır"),QMessageBox::AcceptRole);

            QObject::connect(yesButton,&QPushButton::clicked,[=](){
//                emit this->delClicked(this->currentIndex().data(Qt::UserRole+1).toString());

            SubeItem filter;
            filter.setOid(this->currentIndex().data(Qt::UserRole+1).toString().toStdString());

            if( this->mModel->DeleteItem(filter) ){
                this->mModel->UpdateList();
            }else{
                GlobarVar::InformationWidget::instance()->setInformation("Şube Kayıttan Silinemedi");
            }
        });

        msgBox->exec();

    });





    menu.exec(event->globalPos());

}
