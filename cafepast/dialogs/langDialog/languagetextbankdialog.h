
#ifndef LANGUAGE_LANGUAGETEXTBANKDIALOG_H
#define LANGUAGE_LANGUAGETEXTBANKDIALOG_H




#include <QDialog>

#include <QObject>



class QTableView;
class QVBoxLayout;
class QComboBox;
class QLabel;
class QHBoxLayout;
class QLineEdit;

namespace Language {

class LanguageTextModel;
class LanguageModel;

class LanguageTextBankDialog : public QDialog
{
    Q_OBJECT
public:
    LanguageTextBankDialog();

private:
    QVBoxLayout* mMainLayout;
    QTableView* mTextTableView;

    LanguageTextModel* mTextBankModel;
    LanguageModel* mLanguageModel;

    QHBoxLayout* mTitleLayout;
    QLabel* mCurrentLangLabel;
    QComboBox* mCurrentLangComboBox;

    QHBoxLayout* mAddLayout;
    QLineEdit* mCurrentLangLineEdit;
    QLineEdit* mDestLangLineEdit;
    QLineEdit* mDestLangTextEdit;
    QPushButton* mEkleBtn;


};

} // namespace Language

#endif // LANGUAGE_LANGUAGETEXTBANKDIALOG_H
