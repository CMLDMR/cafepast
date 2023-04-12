
#ifndef KATEGORI_YENIEKLEWIDGET_H
#define KATEGORI_YENIEKLEWIDGET_H


#include <QWidget>
#include <memory>
#include <QLineEdit>

class QVBoxLayout;
class QPushButton;
class QLineEdit;
namespace Kategori {

class YeniEkleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit YeniEkleWidget(QWidget *parent = nullptr);


    void setCurrentKategoriName( const QString &currentKategoriName );
signals:

    void iptalClicked();
    void yeniClicked( const QString&);

private:

    std::unique_ptr<QVBoxLayout> mLayout;
    std::unique_ptr<QLineEdit> mKategoriAdiLineEdit;
    std::unique_ptr<QPushButton> mEkleBtn;
    std::unique_ptr<QPushButton> mIptalBtn;

};

} // namespace Kategori

#endif // KATEGORI_YENIEKLEWIDGET_H
