
#include "urunmanagerdialog.h"

#include <QVBoxLayout>
#include <QComboBox>
#include <QTableView>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QLabel>

namespace Urun {

UrunManagerDialog::UrunManagerDialog()
{
    this->setWindowTitle(TR("Ürün Yönetimi"));

    //TODO: delete from destruction
    mKategoriModel = new Kategori::KategoriListModel();

    mMainLayout = new QVBoxLayout();
    this->setLayout(mMainLayout);

    mKategoriComboBox = new QComboBox();
    mMainLayout->addWidget(mKategoriComboBox);
    mKategoriComboBox->setModel(this->mKategoriModel);



    mUrunAdiLayout = new QHBoxLayout();
    mYeniUrunAdiLineEdit = new QLineEdit();
    mYeniUrunAdiLineEdit->setPlaceholderText("Yeni Ürün Adını Giriniz");
    mUrunAdiLangTR = new QLabel("tr");
    mUrunEkle = new QPushButton(TR("Ekle+"));
    mUrunAdiLayout->addWidget(mYeniUrunAdiLineEdit);
    mUrunAdiLayout->addWidget(mUrunAdiLangTR);
    mUrunAdiLayout->addWidget(mUrunEkle);
    mMainLayout->addLayout(mUrunAdiLayout);


    mUrunListView = new QTableView();
    mMainLayout->addWidget(mUrunListView);
    mUrunModel = new Urun::UrunModel();
    mUrunListView->setModel(mUrunModel);

    mSelectedUrunOid = new QLabel("mSelectedUrunOid");
    mMainLayout->addWidget(mSelectedUrunOid);

//    mYeniEkleLayout = new QHBoxLayout();
//    mLangAdLineEdit = new QLineEdit();
//    mLangAdLineEdit->setPlaceholderText(TR("Yeni Ürün Adı Ekle"));
//    mYeniEkleLayout->addWidget(mLangAdLineEdit);

    mLangModel = new Language::LanguageModel();
//    mLangComboBox = new QComboBox();
//    mLangComboBox->setModel(mLangModel);
//    mYeniEkleLayout->addWidget(mLangComboBox);



//    mMainLayout->addLayout(mYeniEkleLayout);


    mFiyatLayout = new QHBoxLayout();
    mParaBirimiSecLabel = new QLabel(TR("Para Birimi Seç"));
    mFiyatSpinBox = new QDoubleSpinBox();
    mParaBirimiComboBox = new QComboBox();
    mYeniEkleBtn = new QPushButton(TR("Ekle+"));

    mFiyatLayout->addWidget(mParaBirimiSecLabel);
    mFiyatLayout->addWidget(mParaBirimiComboBox);
    mFiyatLayout->addWidget(mFiyatSpinBox);
    mFiyatLayout->addWidget(mYeniEkleBtn);

    mParaModel = new ParaBirimi::ParaItemModel();
    mParaBirimiComboBox->setModel(mParaModel);

    mMainLayout->addLayout(mFiyatLayout);



    QObject::connect(mUrunEkle,&QPushButton::clicked,[=](){
        Cafe::Urun::UrunItem urunItem;
        urunItem.setKategoriOid(mKategoriComboBox->currentData(Kategori::KategoriListModel::Role::KategoriOidRole).toString().toStdString());
        urunItem.setUrunAdi(mYeniUrunAdiLineEdit->text().toStdString());
        auto ins = this->mUrunModel->InsertItem(urunItem);
        if( ins.size() ){
            this->updateUrunList();
        }
    });




    QObject::connect(mYeniEkleBtn,&QPushButton::clicked,[=](){


        Cafe::Urun::UrunItem urunItem;

        for(const auto &item : mUrunModel->List() ){
            if( item.oid()->to_string() == mSelectedUrunOid->text().toStdString() ){
                urunItem.setDocumentView(item.view());
                break;
            }
        }

        Cafe::Urun::UrunLanguage langItem;
        langItem.setUrunFiyati(mFiyatSpinBox->value());
        langItem.setUrunParaBirimi(mParaBirimiComboBox->currentData(ParaBirimi::ParaItemModel::ParaItemRole).toString().toStdString());


        if( urunItem.addUrun(langItem) ){
            auto upt = this->mUrunModel->UpdateItem(urunItem);
            if( upt ){
                this->updateUrunList();
            }else{
                //TODO: Pop Up Penceresi Yapılacak. Yapılan işler için uyarı yada bilgilendirme amaçlı. singleton bir sınıf için.
                qDebug() << "Güncellenemedi";
            }
        }else{
            errorOccured("Bu Çeviri Zaten Var");
        }


    });


    QObject::connect(mUrunListView,&QTableView::doubleClicked,[=]( const QModelIndex &index){
        mSelectedUrunOid->setText(mUrunModel->index(index.row(),0,index).data(Qt::UserRole+1).toString());
    });




    QObject::connect(mKategoriComboBox,&QComboBox::currentIndexChanged,[=](const int &index){
        this->updateUrunList();
    });
    this->updateUrunList();
}

void UrunManagerDialog::updateUrunList()
{

    Cafe::Urun::UrunItem filter;
    filter.setKategoriOid(mKategoriComboBox->currentData(Kategori::KategoriListModel::KategoriOidRole).toString().toStdString());
    mUrunModel->UpdateList(filter);
}

} // namespace Urun

