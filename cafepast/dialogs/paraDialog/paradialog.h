
#ifndef PARABIRIMI_PARADIALOG_H
#define PARABIRIMI_PARADIALOG_H

#include <QDialog>

#include <QObject>

class QHBoxLayout;
class QLabel;
class QVBoxLayout;
class QComboBox;
class QPushButton;
class QLineEdit;


namespace ParaBirimi {

class ParaItemModel;

class ParaDialog : public QDialog
{
    Q_OBJECT
public:
    ParaDialog();

private:
    QVBoxLayout* mMainLayout;
    QLabel* mParaDialogTitle;

    QHBoxLayout* mParaBirimiLayout;
    QComboBox* mCurrentParaBirimi;
    QPushButton* mVarsayilanParaBirimiSecBtn;
    QPushButton* mParaBiriminiSilBtn;


    QHBoxLayout* mYeniLayout;
    QLineEdit* mYeniParaBirimiLineEdit;
    QPushButton* mYeniParaBirimiEkle;

    ParaItemModel* mParaItemModel;



};

} // namespace ParaBirimi

#endif // PARABIRIMI_PARADIALOG_H
