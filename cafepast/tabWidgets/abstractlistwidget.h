
#ifndef ABSTRACTLISTWIDGET_H
#define ABSTRACTLISTWIDGET_H


#include <QWidget>
#include <QString>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QTableView>

class AbstractListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractListWidget(const QString &tabWidgetName,QWidget *parent =nullptr);

    QString tabWidgetName() const;

signals:


private:
    QString mTabWidgetName;

    QHBoxLayout* mLayout;
    QGroupBox* mListGroupBox;

    QHBoxLayout *mProductListLayout;
    QTableView* mTableListView;

};

#endif // ABSTRACTLISTWIDGET_H
