
#ifndef GLOBARVAR_INFORMATIONWIDGET_H
#define GLOBARVAR_INFORMATIONWIDGET_H


#include <QWidget>

class QLabel;
class QVBoxLayout;
class QScreen;
class QTimer;

namespace GlobarVar {

class InformationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InformationWidget(QWidget *parent = nullptr);

    enum Type;


    static InformationWidget* instance();

    void setInformation( const QString &informationText , const Type &type = Type::Info );


    enum Type{
        Info = 0,
        Warn,
        Critic
    };

signals:


private:
    QLabel* mInformationLabel;
    QVBoxLayout* mMainLayout;

    QScreen* mScreen;
    QTimer* mTimer;

    void animateWindow();

    int mCounter{0};

};

} // namespace GlobarVar

#endif // GLOBARVAR_INFORMATIONWIDGET_H
