
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>


#include <QAction>
#include <QMenu>

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




    void initAction();

    std::unique_ptr<QMenu> mUrunMenu;
    std::unique_ptr<QAction> mYeniUrunAction;
    std::unique_ptr<QAction> mUrunUpdateAction;


    std::unique_ptr<QMenu> mAyarlarMenu;

    QTranslator mEnglishTranslator;
    QTranslator mMakedonTranslator;

};

#endif // MAINWINDOW_H
