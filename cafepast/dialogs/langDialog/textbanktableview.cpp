#include "textbanktableview.h"
#include <QHeaderView>

#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>


namespace Language {

TextBankTableView::TextBankTableView()
{
    setSelectionMode(SelectionMode::SingleSelection);
    setSelectionBehavior(SelectionBehavior::SelectRows);
    setAlternatingRowColors(true);
    horizontalHeader()->setStretchLastSection(true);
    setEditTriggers(NoEditTriggers);
}

} // namespace Language


void Language::TextBankTableView::contextMenuEvent(QContextMenuEvent *event)
{

    QMenu menu;

    menu.addAction("Yeni Ekle",[=](){
        emit yeniEkleClicked();
    });

    menu.addAction("Sil",[=](){
        emit silClicked();
    });






    menu.exec(event->globalPos());
}
