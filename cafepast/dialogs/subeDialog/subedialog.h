#ifndef CAFE_SUBE_SUBEDIALOG_H
#define CAFE_SUBE_SUBEDIALOG_H

#include <QObject>
#include <QDialog>

class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class QPushButton;
class QTableView;
class QComboBox;
class QLineEdit;
class QLabel;
class QStandardItemModel;



namespace Cafe {
namespace Sube {

class SubeTableView;

class SubeDialog : public QDialog
{
    Q_OBJECT
public:
    SubeDialog();
    virtual ~SubeDialog();

    // SubeManager interface
public:


private:
    QVBoxLayout* mMainLayout;
    SubeTableView* mSubeTableView;

    QHBoxLayout* mControllerLayout;
    QLineEdit* mSubeAdiLineEdit;
    QLineEdit* mSubeTelefonLineEdit;
    QLineEdit* mSubeAdresLineEdit;

    QPushButton* mSaveButton;

    void saveSube();

    QString mSelectedSubeOid;

};

} // namespace Sube
} // namespace Cafe

#endif // CAFE_SUBE_SUBEDIALOG_H
