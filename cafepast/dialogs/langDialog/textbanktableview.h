#ifndef LANGUAGE_TEXTBANKTABLEVIEW_H
#define LANGUAGE_TEXTBANKTABLEVIEW_H

#include <QTableView>
#include <QObject>

namespace Language {

class TextBankTableView : public QTableView
{
    Q_OBJECT
public:
    TextBankTableView();


Q_SIGNALS:
    void yeniEkleClicked();
    void silClicked();

    // QWidget interface
protected:
    virtual void contextMenuEvent(QContextMenuEvent *event) override;
};

} // namespace Language

#endif // LANGUAGE_TEXTBANKTABLEVIEW_H
