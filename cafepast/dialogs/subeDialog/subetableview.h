#ifndef CAFE_SUBE_SUBETABLEVIEW_H
#define CAFE_SUBE_SUBETABLEVIEW_H

#include <QTableView>
#include <QObject>



namespace Cafe {
namespace Sube {

class SubeModel;

class SubeTableView : public QTableView
{
    Q_OBJECT
public:
    SubeTableView();
    virtual ~SubeTableView();

    void saveSube( const QString &subeAdi , const QString &telefon, const QString &adres);

    // QWidget interface
    SubeModel *model() const;

protected:
    virtual void contextMenuEvent(QContextMenuEvent *event) override;

private:
    SubeModel* mModel;

Q_SIGNALS:
    void newSaveClicked();
};

} // namespace Sube
} // namespace Cafe

#endif // CAFE_SUBE_SUBETABLEVIEW_H
