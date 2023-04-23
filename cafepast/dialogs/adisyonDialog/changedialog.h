
#ifndef ADISYON_CHANGEDIALOG_H
#define ADISYON_CHANGEDIALOG_H

#include <QDialog>

class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class QDoubleSpinBox;
class QPushButton;

namespace Adisyon {

class ChangeDialog : public QDialog
{
public:
    ChangeDialog(const double Adet, const QString &urunAdi);


    QDoubleSpinBox *adetDoubleSpinBox() const;

    QPushButton *acceptBtn() const;

    QPushButton *rejectBtn() const;

private:
    double mAdet;

private:
    QVBoxLayout* mMainLayout;
    QLabel* mTitleLabel;
    QDoubleSpinBox* mAdetDoubleSpinBox;

    QHBoxLayout* mControllerLayout;
    QPushButton* mAcceptBtn;
    QPushButton* mRejectBtn;
};

} // namespace Adisyon

#endif // ADISYON_CHANGEDIALOG_H
