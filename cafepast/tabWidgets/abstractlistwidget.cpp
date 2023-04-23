
#include "abstractlistwidget.h"

#include "cafecore/languageitem.h"
#include "global/informationwidget.h"
#include "global/globalVar.h"

#include "model/paraitemmodel.h"
#include "cafecore/languageitem.h"

#include <QComboBox>
#include <QVBoxLayout>
#include <QHeaderView>


AbstractListWidget::AbstractListWidget(const QString &tabWidgetName, QWidget *parent)
    : QWidget{parent},mTabWidgetName(tabWidgetName)
{

    mLayout = new QHBoxLayout();
    this->setLayout(mLayout);




    mListGroupBox = new QGroupBox(this);
    mListGroupBox->setFlat(true);
    mListGroupBox->setTitle(TR(mTabWidgetName.toStdString()));
    mListGroupBox->setContentsMargins(0,10,0,0);
//    mListGroupBox->setMaximumWidth(550);
//    mListGroupBox->setMinimumWidth(250);

    mTableListView = new QTableView(mListGroupBox);
    mProductListLayout = new QVBoxLayout(mListGroupBox);
    mCurrentParaBirimiComboBox = new QComboBox();
    mProductListLayout->addWidget(mCurrentParaBirimiComboBox);
    mParaModel = new ParaBirimi::ParaItemModel();
    mCurrentParaBirimiComboBox->setModel(mParaModel);
    for( int i = 0 ; i < mCurrentParaBirimiComboBox->count() ; i++ ){
        if( mCurrentParaBirimiComboBox->itemText(i).toStdString() == GlobarVar::LocalConfiguration::instance()->getCurrentParaBirimi() )  {
            mCurrentParaBirimiComboBox->setCurrentIndex(i);
            break;
        }
    }
    mProductListLayout->addWidget(mTableListView);

    mLayout->addWidget(mListGroupBox);

    mKategoriManager = new Cafe::Kategori::KategoriManager();

    mUrunModel = new Menu::UrunModel();

    mTableListView->setModel(mUrunModel);

    auto kategoriItem = mKategoriManager->FindOneItem(Cafe::Kategori::KategoriItem().setName(tabWidgetName.toStdString()));

    if( kategoriItem.view().empty() ){
        GlobarVar::InformationWidget::instance()->setInformation(TR("Kategori Bulunamadı"));
    }else{
        mUrunModel->setCurrentParaBirimi(mCurrentParaBirimiComboBox->currentData(ParaBirimi::ParaItemModel::ParaItemRole).toString().toStdString());
        mUrunModel->UpdateList(Cafe::Urun::UrunItem().setKategoriOid(kategoriItem.oid().value().to_string()));
    }

    QObject::connect(mCurrentParaBirimiComboBox,&QComboBox::currentIndexChanged,[=](const int &index){
        mUrunModel->setCurrentParaBirimi(mCurrentParaBirimiComboBox->currentData(ParaBirimi::ParaItemModel::ParaItemRole).toString().toStdString());
        mUrunModel->UpdateList(Cafe::Urun::UrunItem().setKategoriOid(kategoriItem.oid().value().to_string()));
    });

//    mLayout->addStretch(1);

    mTableListView->setSelectionMode(QAbstractItemView::SingleSelection);
    mTableListView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    mTableListView->horizontalHeader()->setStretchLastSection(true);
    mTableListView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);


    QObject::connect(mTableListView,&QTableView::doubleClicked,[=]( const QModelIndex &index){
        emit UrunClicked(index.data(Menu::UrunModel::UrunOid).toString());
    });
}

QString AbstractListWidget::tabWidgetName() const
{
    return mTabWidgetName;
}

