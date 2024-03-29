
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

class UrunTableView;


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



    UrunTableView* mUrunListView;

    QHBoxLayout* mYeniEkleLayout;
    QLabel* mSelectedUrunOid;
//    QLineEdit* mLangAdLineEdit;
    QPushButton* mYeniEkleBtn;

    QHBoxLayout* mFiyatLayout;
    QLabel* mParaBirimiSecLabel;
    QDoubleSpinBox* mFiyatSpinBox;
    QComboBox* mParaBirimiComboBox;

    Kategori::KategoriListModel* mKategoriModel;
    Urun::UrunModel* mUrunModel;
    Language::LanguageModel* mLangModel;
    ParaBirimi::ParaItemModel* mParaModel;

private:
    void updateUrunList();

    void delClicked( const QString &urunOid );
    void priceChangeClicked( );
    void urunAdiniChangeClicked( const QString &urunOid, const QString &UrunAdi );



    // DB interface
public:
    virtual void errorOccured(const std::string &errorText) override;
};

} // namespace Urun

#endif // URUN_URUNMANAGERDIALOG_H
