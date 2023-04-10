
#include "abstractlistwidget.h"

AbstractListWidget::AbstractListWidget(const QString &tabWidgetName, QWidget *parent)
    : QWidget{parent},mTabWidgetName(tabWidgetName)
{

    mLayout = new QHBoxLayout();
    this->setLayout(mLayout);
    mListGroupBox = new QGroupBox(this);
    mListGroupBox->setFlat(true);
    mListGroupBox->setTitle(mTabWidgetName);
    mListGroupBox->setContentsMargins(0,10,0,0);
    mListGroupBox->setMaximumWidth(250);

    mTableListView = new QTableView(mListGroupBox);
    mProductListLayout = new QHBoxLayout(mListGroupBox);
    mProductListLayout->addWidget(mTableListView);

    mLayout->addWidget(mListGroupBox);


}

QString AbstractListWidget::tabWidgetName() const
{
    return mTabWidgetName;
}

