
#ifndef ADISYON_ADISYONWIDGET_H
#define ADISYON_ADISYONWIDGET_H


#include <QWidget>

class QVBoxLayout;
class QTableView;
class QHBoxLayout;
class QPushButton;
class QLabel;
class QScrollArea;
class QImage;
class QComboBox;

namespace Cafe {
namespace Urun {
class UrunManager;
}
}

namespace ParaBirimi {
class ParaItemModel;
}

namespace Adisyon {

class AdisyonModel;

class AdisyonWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AdisyonWidget(QWidget *parent = nullptr);

signals:

public slots:
    void addUrun( const QString &urunOid );
    void reduceUrun( const QString &urunOid );


private:

    QHBoxLayout* mMainLayout;

    QWidget* mAdisyonListWidget;
    QVBoxLayout* mAdisyonListLayout;
    QTableView* mAdisyonView;
    AdisyonModel* mAdisyonModel;
    QPushButton* mSilSelectedBtn;

    QHBoxLayout* mControlBirimiLayout;
    QPushButton* mSayiArtirBtn;
    QPushButton* mSayiAzaltBtn;
    QPushButton* mSayiDegisBtn;

    QLabel* mTotalFiyatLabel;

    QHBoxLayout* mParaBirimiLayout;
    QLabel* mParaBirimiDegisLabel;
    QComboBox* mParaBirimiComboBox;
    ParaBirimi::ParaItemModel* mParaItemModel;

    QWidget* mAdisyonPreviewWidget;
    QVBoxLayout* mAdisyonPreviewLayout;
    QLabel* mAdisyonPreviewTitle;
    QScrollArea* mAdisyonPreviewScrollArea;
    QLabel* mAdisyonPreviewLabel;
    QImage* mAdisyonPreviwImage{nullptr};
    QPushButton* mAdisyonPreviewPrintBtn;

    Cafe::Urun::UrunManager* mUrunManager;


    void paintAdisyon();

private slots:
    void incrementUrun();
    void decrementUrun();
    void changeUrunAdet();
    void removeUrun();



};

} // namespace Adisyon

#endif // ADISYON_ADISYONWIDGET_H
