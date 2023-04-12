
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

    void setList( const std::vector<Cafe::Kategori::KategoriItem> &mList);


signals:
    void addNewKategoriBtn();



private:
    std::unique_ptr<QLabel> mTitleLabel;

    std::unique_ptr<QVBoxLayout> mLayout;

    std::unique_ptr<QListView> mListView;

    std::unique_ptr<KategoriListModel> mKategoriModel;


    std::unique_ptr<QHBoxLayout> mControlLayout;
    std::unique_ptr<QPushButton> mYeniEkleSlideButton;

};

} // namespace Kategori

#endif // KATEGORI_KATEGORILISTWIDGET_H
