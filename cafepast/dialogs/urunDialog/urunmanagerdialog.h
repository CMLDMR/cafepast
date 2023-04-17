
#ifndef URUN_URUNMANAGERDIALOG_H
#define URUN_URUNMANAGERDIALOG_H


#include <QObject>
#include <QDialog>

#include "model/urunmodel.h"
#include "model/kategorilistmodel.h"
#include "model/languagemodel.h"
#include "model/paraitemmodel.h"

class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class QPushButton;
class QTableView;
class QComboBox;
class QLineEdit;
class QDoubleSpinBox;
class QLabel;


namespace Urun {

class UrunManagerDialog : public QDialog, public Cafe::Urun::UrunManager
{
    Q_OBJECT
public:
    UrunManagerDialog();

private:
    QComboBox* mKategoriComboBox;

    QVBoxLayout* mMainLayout;

    QHBoxLayout* mUrunAdiLayout;
    QLineEdit* mYeniUrunAdiLineEdit;
    QLabel* mUrunAdiLangTR;
    QPushButton* mUrunEkle;



    QTableView* mUrunListView;

    QHBoxLayout* mYeniEkleLayout;
    QLabel* mSelectedUrunOid;
    QLineEdit* mYeniAdLineEdit;
    QComboBox* mLangComboBox;
    QPushButton* mYeniEkleBtn;

    QHBoxLayout* mFiyatLayout;
    QLabel* mParaBirimiSecLabel;
    QDoubleSpinBox* mFiyatSpinBox;
    QComboBox* mParaBirimiComboBox;

    Kategori::KategoriListModel* mKategoriModel;
    Urun::UrunModel* mUrunModel;
    Language::LanguageModel* mLangModel;
    ParaBirimi::ParaItemModel* mParaModel;
};

} // namespace Urun

#endif // URUN_URUNMANAGERDIALOG_H
