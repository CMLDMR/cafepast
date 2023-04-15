
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>


#include <QAction>
#include <QMenu>

#include <QTabWidget>
#include <QHBoxLayout>

#include "tabWidgets/tabwidget.h"


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
    std::unique_ptr<QAction> mYeniUrunAction;
    std::unique_ptr<QAction> mUrunUpdateAction;
    std::unique_ptr<QAction> mKategoriManagerList;


    std::unique_ptr<QMenu> mAyarlarMenu;
    std::unique_ptr<QAction> mParaBirimiAction;
    std::unique_ptr<QAction> mDilSecimiAction;
    std::unique_ptr<QAction> mTextManagerAction;

    QTranslator mEnglishTranslator;
    QTranslator mMakedonTranslator;


    void initWidget();
    std::unique_ptr<TabWidget> mTabWidget;
    std::unique_ptr<QHBoxLayout> mCentralWidgetLayout;

};

#endif // MAINWINDOW_H
