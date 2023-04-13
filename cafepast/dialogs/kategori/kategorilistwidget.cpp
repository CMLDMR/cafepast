
#include "kategorilistwidget.h"

namespace Kategori {

KategoriListWidget::KategoriListWidget(QWidget *parent)
    : QWidget{parent}
{
    mLayout = std::make_unique<QVBoxLayout>();
    this->setLayout(mLayout.get());


    mTitleLabel = std::make_unique<QLabel>();
    mTitleLabel->setText("KategoriListesi");
    mLayout->addWidget(mTitleLabel.get());


    mListView = std::make_unique<QListView>();

    mListView.get()->setViewMode(QListView::ViewMode::ListMode);
    mListView.get()->setResizeMode(QListView::ResizeMode::Adjust);



    mLayout->addWidget(mListView.get());


    mKategoriModel = std::make_unique<KategoriListModel>();

    mListView->setModel(mKategoriModel.get());


    mControlLayout = std::make_unique<QHBoxLayout>();
    mLayout->addLayout(mControlLayout.get());

    mYeniEkleSlideButton = std::make_unique<QPushButton>("Yeni Ekle");
    mControlLayout->addWidget(mYeniEkleSlideButton.get());

    mDeleteBtn = new QPushButton("Sil");
    mControlLayout->addWidget(mDeleteBtn);

    QObject::connect(mYeniEkleSlideButton.get(),&QPushButton::clicked,[=](){
        emit this->addNewKategoriBtn();
    });

    mAdiniDegistirBtn = new QPushButton("Değiştir");
    mControlLayout->addWidget(mAdiniDegistirBtn);

    QObject::connect(mAdiniDegistirBtn,&QPushButton::clicked,[=](){

        if( mListView.get()->currentIndex().row() < 0 ){
            qDebug() << "Error No Model Item Selected";
        }else{
            emit this->changeKategoriName(mListView.get()->currentIndex().data(Qt::DisplayRole).toString());
        }

    });

    QObject::connect(mDeleteBtn,&QPushButton::clicked,[=](){
        auto str = this->mListView->currentIndex().data(Qt::DisplayRole).toString();
        emit this->delClicked(str,"No Oid");
    });

}

KategoriListWidget::~KategoriListWidget()
{
    delete mAdiniDegistirBtn;
}

void KategoriListWidget::setList(const std::vector<Cafe::Kategori::KategoriItem> &mList)
{
    mKategoriModel.get()->setList(mList);
}

KategoriListModel*KategoriListWidget::kategoriModel() const
{
    return mKategoriModel.get();
}




} // namespace Kategori

