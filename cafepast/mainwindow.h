
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>


#include <QAction>
#include <QMenu>

#include <QTabWidget>
#include <QHBoxLayout>

#include "tabWidgets/tabwidget.h"

namespace Adisyon {
class AdisyonWidget;
}


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    mongocxx::client* mClient;
    mongocxx::database m_db;


    void initAction();

    std::unique_ptr<QMenu> mUrunMenu;
    std::unique_ptr<QAction> mUrunManagerDialogAction;
    std::unique_ptr<QAction> mKategoriManagerList;


    std::unique_ptr<QMenu> mAyarlarMenu;
    std::unique_ptr<QAction> mParaBirimiAction;
    std::unique_ptr<QAction> mDilSecimiAction;
    std::unique_ptr<QAction> mTextManagerAction;

    std::unique_ptr<QMenu> mOtherMenu;
    std::unique_ptr<QAction> mCorpNameAction;
    std::unique_ptr<QAction> mCorpContactAction;

    QTranslator mEnglishTranslator;
    QTranslator mMakedonTranslator;


    void initWidget();
    std::unique_ptr<TabWidget> mTabWidget;
    std::unique_ptr<QHBoxLayout> mCentralWidgetLayout;
    Adisyon::AdisyonWidget* mAdisyonWidget;

};

#endif // MAINWINDOW_H
