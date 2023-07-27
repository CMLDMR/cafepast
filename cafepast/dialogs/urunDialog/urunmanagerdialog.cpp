
#include "urunmanagerdialog.h"
#include "global/informationwidget.h"

#include <QVBoxLayout>
#include <QComboBox>
#include <QTableView>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QLabel>

#include "uruntableview.h"


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
    mYeniUrunAdiLineEdit->setPlaceholderText(TR("Yeni Ürün Adını Giriniz"));
    mUrunAdiLangTR = new QLabel("tr");
    mUrunEkle = new QPushButton(TR("Ekle+"));
    mUrunAdiLayout->addWidget(mYeniUrunAdiLineEdit);
    mUrunAdiLayout->addWidget(mUrunAdiLangTR);
    mUrunAdiLayout->addWidget(mUrunEkle);
    mMainLayout->addLayout(mUrunAdiLayout);


    mUrunListView = new UrunTableView();
    mMainLayout->addWidget(mUrunListView);
    mUrunModel = new Urun::UrunModel();
    mUrunListView->setModel(mUrunModel);
    QObject::connect(mUrunListView,&UrunTableView::delClicked,this,&UrunManagerDialog::delClicked);
    QObject::connect(mUrunListView,&UrunTableView::urunAdiniChangeClicked,this,&UrunManagerDialog::urunAdiniChangeClicked);

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
    mFiyatSpinBox->setMaximum(9999999);
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
            mYeniEkleBtn->setText(TR("Ekle+"));
        }
    });




    QObject::connect(mYeniEkleBtn,&QPushButton::clicked,[=](){

        if( mSelectedUrunOid->text().isEmpty() ){
            errorOccured(TR("Ürün Seçmediniz"));
            return;
        }

        Cafe::Urun::UrunItem urunItem;

        for(const auto &item : mUrunModel->List() ){
            if( item.oid()->to_string() == mSelectedUrunOid->text().toStdString() ){
                urunItem.setDocumentView(item.view());
                break;
            }
        }

        if( urunItem.view().empty() ){
            errorOccured(TR("Ürün Bulunamadı"));
            return;
        }

        Cafe::Urun::UrunLanguage langItem;
        langItem.setUrunFiyati(mFiyatSpinBox->value());
        langItem.setUrunParaBirimi(mParaBirimiComboBox->currentData(ParaBirimi::ParaItemModel::ParaItemRole).toString().toStdString());

        if( mYeniEkleBtn->text() == "Değiştir" ){

            if( urunItem.IsUrunExist(mParaBirimiComboBox->currentText().toStdString()) ){
                if( urunItem.change(mParaBirimiComboBox->currentText().toStdString(),langItem) ){
                    auto upt = this->mUrunModel->UpdateItem(urunItem);
                    if( upt ){
                        this->updateUrunList();
                        errorOccured(TR("Fiyat Güncellendi"));
                    }else{
                        errorOccured(TR("Ürün Güncellenemedi"));
                    }
                }else{
                }
            }else{
            if( urunItem.addUrun(langItem) ){
                auto upt = this->mUrunModel->UpdateItem(urunItem);
                if( upt ){
                    this->updateUrunList();
                        errorOccured(TR("Fiyat Eklendi"));

                }else{
                    errorOccured(TR("Ürün Güncellenemedi"));
                }
            }else{
            }
            }


        }else{
            if( urunItem.addUrun(langItem) ){
                auto upt = this->mUrunModel->UpdateItem(urunItem);
                if( upt ){
                    this->updateUrunList();
                }else{
                    errorOccured(TR("Ürün Güncellenemedi"));
                }
            }else{
                errorOccured(TR("Bu Para Biriminde Fiyat Mevcut"));
            }
        }




    });


    QObject::connect(mUrunListView,&QTableView::doubleClicked,[=]( const QModelIndex &index){
        mYeniEkleBtn->setText(TR("Değiştir"));
        mSelectedUrunOid->setText(mUrunModel->index(index.row(),0,index).data(Qt::UserRole+1).toString());
        mFiyatSpinBox->setValue(mUrunModel->price(index.row(),mParaBirimiComboBox->currentText().toStdString()));
    });

    QObject::connect(mUrunListView,&QTableView::clicked,[=]( const QModelIndex &index){
        mYeniEkleBtn->setText(TR("Değiştir"));
        mSelectedUrunOid->setText(mUrunModel->index(index.row(),0,index).data(Qt::UserRole+1).toString());
        mFiyatSpinBox->setValue(mUrunModel->price(index.row(),mParaBirimiComboBox->currentText().toStdString()));
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

void UrunManagerDialog::delClicked(const QString &urunOid)
{

    Cafe::Urun::UrunItem filter;
    filter.setOid(urunOid.toStdString());

    if( this->DeleteItem(filter) ){
        GlobarVar::InformationWidget::instance()->setInformation(TR("Ürün Silindi"));
        this->updateUrunList();
    }else{
        GlobarVar::InformationWidget::instance()->setInformation(TR("Ürün Silindi"),GlobarVar::InformationWidget::Warn);
    }

}

void UrunManagerDialog::priceChangeClicked()
{
    mFiyatSpinBox->setFocus();
}

void UrunManagerDialog::urunAdiniChangeClicked(const QString &urunOid, const QString &UrunAdi)
{

    auto mDialog = std::make_unique<QDialog>();

    mDialog->setWindowTitle("Değiştir");

    auto mHLayout = new QHBoxLayout(mDialog.get());

    mDialog->setLayout(mHLayout);

    auto newNameLineEdit = std::make_unique<QLineEdit>();
    newNameLineEdit->setText(UrunAdi);
    newNameLineEdit->setPlaceholderText(TR("Yeni Ürün Adını Giriniz"));

    mHLayout->addWidget(newNameLineEdit.get());

    auto savebtn = std::make_unique<QPushButton>(TR("Kaydet"));
    mHLayout->addWidget(savebtn.get());

    QObject::connect(savebtn.get(),&QPushButton::clicked,[=,&newNameLineEdit,&mDialog](){

            Cafe::Urun::UrunItem filter;
            filter.setOid(urunOid.toStdString());
            filter.setUrunAdi(newNameLineEdit->text().toStdString());

            if( this->UpdateItem(filter) ){
                GlobarVar::InformationWidget::instance()->setInformation(TR("Ürün Adı Güncellendi"));
                this->updateUrunList();
                mDialog->close();

            }else{
                GlobarVar::InformationWidget::instance()->setInformation(TR("Ürün Adı Güncellenemedi"),GlobarVar::InformationWidget::Warn);
            }

    });




    mDialog->exec();

}

} // namespace Urun



void Urun::UrunManagerDialog::errorOccured(const std::string &errorText)
{
    GlobarVar::InformationWidget::instance()->setInformation(TR(errorText));
}
