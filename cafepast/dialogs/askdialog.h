
#ifndef GLOBARVAR_ASKDIALOG_H
#define GLOBARVAR_ASKDIALOG_H

#include <QDialog>

#include <QObject>
class QLabel;
class QVBoxLayout;
class QPushButton;
class QHBoxLayout;

namespace GlobarVar {

class AskDialog : public QDialog
{

    Q_OBJECT
    AskDialog(const QString &mQuestionStr);

public:
    virtual ~AskDialog(){}

    enum AcceptedButton{
        YES = 0,
        NO
    };

    static AskDialog* askQuestion( const QString &questionstr );


    AcceptedButton status() const;

signals:
    void Accepted();
private:

    AcceptedButton mStatus;
    QVBoxLayout* mMainLayout;
    QLabel* mQuestionLabel;
    QHBoxLayout* mControllerLayout;
    QPushButton* mAcceptButton;
    QPushButton* mRejectButton;
};

} // namespace GlobarVar

#endif // GLOBARVAR_ASKDIALOG_H
