
#include "kategorimanagerwidget.h"

KategoriManagerWidget::KategoriManagerWidget()
{
    this->setWindowTitle("Kategori Yönetimi");
}

void KategoriManagerWidget::onList(const std::vector<Cafe::Kategori::KategoriItem> &mList)
{
    for( const auto &item : mList ){
        qDebug() << bsoncxx::to_json(item.view()).c_str();
    }
}

