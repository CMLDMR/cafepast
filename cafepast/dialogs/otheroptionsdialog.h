
#ifndef OTHER_OTHEROPTIONSDIALOG_H
#define OTHER_OTHEROPTIONSDIALOG_H

#include <QDialog>


class QVBoxLayout;
class QLabel;
class QLineEdit;
class QPushButton;
class QHBoxLayout;



namespace Other {

class OtherOptionsDialog : public QDialog
{
    Q_OBJECT
public:
    OtherOptionsDialog();

    QVBoxLayout* mMainLayout;
    QLabel* mTitleLabel;
    QLineEdit* mCafeNameLineEdit;

    QHBoxLayout* mControllerLayout;
    QPushButton* mAcceptedBtn;
    QPushButton* mRejectedBtn;
};

} // namespace Other

#endif // OTHER_OTHEROPTIONSDIALOG_H
