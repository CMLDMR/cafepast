
#include "abstractlistwidget.h"

#include "cafecore/languageitem.h"
#include "global/informationwidget.h"

AbstractListWidget::AbstractListWidget(const QString &tabWidgetName, QWidget *parent)
    : QWidget{parent},mTabWidgetName(tabWidgetName)
{

    mLayout = new QHBoxLayout();
    this->setLayout(mLayout);
    mListGroupBox = new QGroupBox(this);
    mListGroupBox->setFlat(true);
    mListGroupBox->setTitle(mTabWidgetName);
    mListGroupBox->setContentsMargins(0,10,0,0);
    mListGroupBox->setMaximumWidth(550);
    mListGroupBox->setMinimumWidth(450);

    mTableListView = new QTableView(mListGroupBox);
    mProductListLayout = new QHBoxLayout(mListGroupBox);
    mProductListLayout->addWidget(mTableListView);

    mLayout->addWidget(mListGroupBox);

    mKategoriManager = new Cafe::Kategori::KategoriManager();

    mUrunModel = new Urun::UrunModel();

    mTableListView->setModel(mUrunModel);

    auto kategoriItem = mKategoriManager->FindOneItem(Cafe::Kategori::KategoriItem().setName(tabWidgetName.toStdString()));

    if( kategoriItem.view().empty() ){
        GlobarVar::InformationWidget::instance()->setInformation(TR("Kategori Bulunamadı"));
    }else{
        mUrunModel->UpdateList(Cafe::Urun::UrunItem().setKategoriOid(kategoriItem.oid().value().to_string()));
    }

    mLayout->addStretch(1);

    mTableListView->setSelectionMode(QAbstractItemView::SingleSelection);
    mTableListView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

}

QString AbstractListWidget::tabWidgetName() const
{
    return mTabWidgetName;
}

