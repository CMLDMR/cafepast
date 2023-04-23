
#ifndef LANGUAGE_LANGUAGEDIALOG_H
#define LANGUAGE_LANGUAGEDIALOG_H

#include <QDialog>

#include <QObject>

class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class QComboBox;
class QLineEdit;
class QPushButton;


namespace Language {
class LanguageModel;

class LanguageDialog : public QDialog
{
    Q_OBJECT
public:
    LanguageDialog();


private:
    QVBoxLayout* mMainLayout;
    QLabel* mTitleLabel;

    QHBoxLayout* mSelectLangLayout;
    QPushButton* mVarsayilanYapBtn;
    QComboBox* mDilComboBox;

    QHBoxLayout* mYeniDilEkleLayout;
    QLineEdit* mLanguageNameLineEdit;
    QLineEdit* mLanguageShortNameLineEdit;
    QPushButton* mEkleButton;

    LanguageModel* mLangModel;
};

} // namespace Language

#endif // LANGUAGE_LANGUAGEDIALOG_H
