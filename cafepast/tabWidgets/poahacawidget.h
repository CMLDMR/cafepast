
#ifndef POAHACAWIDGET_H
#define POAHACAWIDGET_H


#include "abstractlistwidget.h"


class PoahacaWidget : public AbstractListWidget
{
    Q_OBJECT
public:
    explicit PoahacaWidget(const QString &tabName , QWidget *parent = nullptr);

signals:

};

#endif // POAHACAWIDGET_H
