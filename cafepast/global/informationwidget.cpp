
#include "informationwidget.h"
#include <mutex>

#include <QVBoxLayout>
#include <QLabel>
#include <QScreen>
#include <QGuiApplication>
#include <QTimer>


namespace GlobarVar {

InformationWidget::InformationWidget(QWidget *parent)
    : QWidget{parent}
{

    mMainLayout = new QVBoxLayout();
    this->setLayout(mMainLayout);

    mInformationLabel = new QLabel("information Dialog");
    mInformationLabel->setFont(QFont("Tahoma",14));
    mMainLayout->addWidget(mInformationLabel,1,Qt::AlignCenter);

    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->setWindowFlag(Qt::WindowType::FramelessWindowHint);
    mScreen = QGuiApplication::primaryScreen();
    this->setGeometry(mScreen->geometry().width()/2-this->width()/2,mScreen->geometry().height()-100,300,100);

    mTimer = new QTimer(parent);

    mTimer->setInterval(10);
    QObject::connect(mTimer,&QTimer::timeout,this,&InformationWidget::animateWindow);
}

std::once_flag informationWidget_once_flag;
static InformationWidget* __mInformation{nullptr};

InformationWidget *InformationWidget::instance()
{
    std::call_once(informationWidget_once_flag,[=](){
        __mInformation = new InformationWidget();
    });
    return __mInformation;
}

void InformationWidget::setInformation(const QString &informationText, const Type &type)
{
    mTimer->stop();
    mCounter = 0;
    this->setGeometry(mScreen->geometry().width()/2-this->width()/2,mScreen->geometry().height()-100,300,100);
    mInformationLabel->setText("<b>"+informationText+"</b>");
    this->show();
    mTimer->start();
}

void InformationWidget::animateWindow()
{
    mCounter +=5;
    if( mCounter <= 125 ){
        this->setGeometry(mScreen->geometry().width()/2-this->width()/2,mScreen->geometry().height()-mCounter,300,100);
    }else{
        mTimer->stop();
        mCounter = 0;
        QTimer::singleShot(2500,[=](){
            this->setGeometry(mScreen->geometry().width()/2-this->width()/2,mScreen->geometry().height(),300,100);
        });
    }
}

} // namespace GlobarVar

