
#include "tabwidget.h"
#include <QMenu>
#include <QContextMenuEvent>

#include "cafecore/languageitem.h"
#include "abstractlistwidget.h"

TabWidget::TabWidget()
{
    mKategoriManager = new Cafe::Kategori::KategoriManager();
    this->setTabsClosable(true);
    this->setTabShape(QTabWidget::TabShape::Rounded);

    QObject::connect(this,&QTabWidget::tabCloseRequested,[=](const int index){
        this->removeTab(index);
    });
}

TabWidget::~TabWidget()
{
    delete mKategoriManager;
}



void TabWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);

    mKategoriManager->UpdateList();
    auto list = mKategoriManager->List();

    for( const auto &kategoriItem : list ){
        auto action = menu.addAction(TR(kategoriItem.getKategoriName().c_str()));
        action->setData(kategoriItem.getKategoriName().c_str());

        QObject::connect(action,&QAction::triggered,[=](const bool checked){

            bool exist = false;
            for( int i = 0 ; i < this->count() ; i++ ){
                auto text = static_cast<AbstractListWidget*>(this->widget(i));
                if( action->text() == text->tabWidgetName() ){
                    exist = true;
                    break;
                }
            }
            if( !exist ){
                auto pohacaWidget = new AbstractListWidget(action->data().toString());
                QObject::connect(pohacaWidget,&AbstractListWidget::UrunClicked,this,&TabWidget::UrunClicked);
                this->insertTab(this->count(),pohacaWidget,TR(pohacaWidget->tabWidgetName().toStdString()));
                this->setCurrentIndex(this->count()-1);
            }
        });
    }

    menu.addAction(TR("Kapat"));

    menu.exec(event->globalPos());

}
