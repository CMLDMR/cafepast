#include "uruntableview.h"

#include <QHeaderView>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <QMessageBox>
#include <QAbstractButton>
#include <QPushButton>

#include <memory>

#include "cafecore/languageitem.h"
#include "model/urunmodel.h"

namespace Urun {

UrunTableView::UrunTableView()
{

    setSelectionMode(SelectionMode::SingleSelection);
    setSelectionBehavior(SelectionBehavior::SelectRows);
    setAlternatingRowColors(true);
    horizontalHeader()->setStretchLastSection(true);

}

} // namespace Urun


void Urun::UrunTableView::contextMenuEvent(QContextMenuEvent *event)
{

    if( this->currentIndex().row() < 0 ){
        return;
    }



    QMenu menu;

    auto delAction = menu.addAction(TR("Sil"));


    QObject::connect(delAction,&QAction::triggered,[=](){

        auto msgBox = std::make_unique<QMessageBox>();

        msgBox->setWindowTitle(TR("Sil")+QString("?"));

        msgBox->setText(this->currentIndex().data(Qt::DisplayRole).toString() + " "+ TR("Silmek istediğinize Emin misiniz?"));

        auto yesButton = msgBox->addButton(TR("Evet"),QMessageBox::AcceptRole);
        msgBox->addButton(TR("Hayır"),QMessageBox::AcceptRole);

        QObject::connect(yesButton,&QPushButton::clicked,[=](){
            emit this->delClicked(this->currentIndex().data(Qt::UserRole+1).toString());
        });

        msgBox->exec();

    });



    auto priceChangeAction = menu.addAction(TR("Fiyat Değiştir"));

    QObject::connect(priceChangeAction,&QAction::triggered,[=](){

        emit priceChangeClicked();

    });

    menu.exec(event->globalPos());

}
