#ifndef URUN_URUNTABLEVIEW_H
#define URUN_URUNTABLEVIEW_H

#include <QTableView>
#include <QObject>

namespace Urun {

class UrunModel;

class UrunTableView : public QTableView
{
    Q_OBJECT
public:
    UrunTableView();

    // QWidget interface
protected:
    virtual void contextMenuEvent(QContextMenuEvent *event) override;

Q_SIGNALS:
    void delClicked( const QString&);
    void priceChangeClicked();

private:
    Urun::UrunModel* mUrunModel{nullptr};
};

} // namespace Urun

#endif // URUN_URUNTABLEVIEW_H
