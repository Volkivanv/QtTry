#include <QApplication>
#include <QPushButton>
#include <iostream>
#include <QPixmap>
#include <QTimer>
//#include "main.moc"
#include <QSlider>
#include <QSpinBox>
#include <QPainter>
#include <QPaintEvent>
#include <QVBoxLayout>


class CircleDraw : public QWidget
        {
        public:
    CircleDraw() = default;
    explicit CircleDraw(QWidget *parent);
    void paintEvent(QPaintEvent *e) override;

    QSize minimumSizeHint() const override;
public slots:
    void setGreen();
    void setYellow();
    void setRed();
    QPixmap mGreenCircle;
    QPixmap mYellowCircle;
    QPixmap mRedCircle;
    QPixmap mCurrentCircle;
    //bool isDown = false;

};

CircleDraw::CircleDraw(QWidget *parent)
{
    setParent(parent);
    setToolTip("Stop");
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mGreenCircle = QPixmap("CircleGreen.png");
    mRedCircle = QPixmap("CircleRed.png");
    mYellowCircle = QPixmap("CircleYellow.png");
    mCurrentCircle = mGreenCircle;

    setGeometry(mCurrentCircle.rect());


}
void CircleDraw::paintEvent(QPaintEvent *e){
    QPainter p(this);
    p.drawPixmap(e->rect(),mCurrentCircle);
}

QSize CircleDraw::minimumSizeHint() const {
    return QSize(100,100);
}

void CircleDraw::setGreen() {
    mCurrentCircle = mGreenCircle;
    update();
}

void CircleDraw::setYellow() {
    mCurrentCircle = mYellowCircle;
    update();
}

void CircleDraw::setRed() {
    mCurrentCircle = mRedCircle;
    update();
}




int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    QWidget *window = new QWidget;
    auto *slider = new QSlider(Qt::Horizontal,window);
    auto *circle = new CircleDraw(window);

    QVBoxLayout *layout = new QVBoxLayout(window);
    layout->addWidget(slider);
    layout->addWidget(circle);
    QObject::connect(slider, &QSlider::valueChanged, [&slider, &circle](int newValue)
    {
        if(newValue <= 33){
            circle->setGreen();
        } else if((newValue > 33)&& (newValue <= 67) ){
            circle->setYellow();
        } else{
            circle->setRed();
        }
    });

    window->setFixedSize(200,250);
    window->move(500,200);
    window->show();

    return QApplication::exec();
}
