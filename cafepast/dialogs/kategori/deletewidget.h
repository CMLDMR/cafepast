
#ifndef KATEGORI_DELETEWIDGET_H
#define KATEGORI_DELETEWIDGET_H


#include <QWidget>

class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class QPushButton;


namespace Kategori {

class DeleteWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DeleteWidget(QWidget *parent = nullptr);
    virtual ~DeleteWidget();

    QPushButton *iptalBtn() const;

    QPushButton *delBtn() const;

    QLabel *kategoriOid() const;

    void setKategoriNameOid( const QString &kategoriName , const QString &kategoriOid );

signals:


private:

    QVBoxLayout* mMainLayout;
    QLabel* mTitle;
    QLabel* mKategoriName;
    QLabel* mKategoriOid;

    QHBoxLayout* mControlLayout;
    QPushButton* mDelBtn;
    QPushButton* mIptalBtn;

};

} // namespace Kategori

#endif // KATEGORI_DELETEWIDGET_H
