
#ifndef KATEGORI_KATEGORILISTWIDGET_H
#define KATEGORI_KATEGORILISTWIDGET_H

#include "kategorilistmodel.h"


#include <QWidget>
#include <QListView>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

namespace Kategori {

class KategoriListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit KategoriListWidget(QWidget *parent = nullptr);
    virtual ~KategoriListWidget();

    void setList( const std::vector<Cafe::Kategori::KategoriItem> &mList);


    KategoriListModel*kategoriModel() const;

signals:
    void addNewKategoriBtn();
    void changeKategoriName( const QString &, const QString &);
    void delClicked( const QString&, const QString&);



private:
    std::unique_ptr<QLabel> mTitleLabel;

    std::unique_ptr<QVBoxLayout> mLayout;

    std::unique_ptr<QListView> mListView;

    std::unique_ptr<KategoriListModel> mKategoriModel;


    std::unique_ptr<QHBoxLayout> mControlLayout;
    std::unique_ptr<QPushButton> mYeniEkleSlideButton;
    QPushButton* mAdiniDegistirBtn;
    QPushButton* mDeleteBtn;

};

} // namespace Kategori

#endif // KATEGORI_KATEGORILISTWIDGET_H
