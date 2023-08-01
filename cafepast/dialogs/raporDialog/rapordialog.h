#ifndef CAFE_RAPOR_RAPORDIALOG_H
#define CAFE_RAPOR_RAPORDIALOG_H

#include <QDialog>
#include <QObject>

#include <memory>

class QVBoxLayout;
class QPushButton;
class QHBoxLayout;


namespace Cafe {
namespace Rapor {

class View;

class RaporDialog : public QDialog
{
    Q_OBJECT
public:
    RaporDialog();


private:
    std::unique_ptr<QVBoxLayout> mMainLayout;
    std::unique_ptr<QHBoxLayout> mControlLayout;
    std::unique_ptr<QPushButton> mGunlukRaporBtn;
    std::unique_ptr<QPushButton> mHaftalikRaporBtn;
    std::unique_ptr<QPushButton> mAylikRaporBtn;

    std::unique_ptr<View> mView;
};

} // namespace Rapor
} // namespace Cafe

#endif // CAFE_RAPOR_RAPORDIALOG_H
