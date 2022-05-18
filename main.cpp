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
#include <QHBoxLayout>
#include <QGridLayout>

class CircleDraw : public QWidget
        {
        public:
    CircleDraw() = default;
    explicit CircleDraw(QWidget *parent);
    void paintEvent(QPaintEvent *e) override;
    //QSize sizeHint() const override;
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
   // connect(this, &QPushButton::clicked, this, &ImageButton::setDown);

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


class ImageButton : public QPushButton
{
public:
    ImageButton() = default;
    ImageButton(QWidget *parent);
    void paintEvent(QPaintEvent *e) override;
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void keyPressEvent(QKeyEvent *e) override;
public slots:
    void setUp();
    void setDown();
    QPixmap mCurrentButtonPixmap;
    QPixmap mButtonDownPixmap;
    QPixmap mButtonUpPixmap;
    bool isDown = false;
};

ImageButton::ImageButton(QWidget *parent)
{
    setParent(parent);
    setToolTip("Stop");
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mButtonUpPixmap = QPixmap("CircleGreen.png");
    mButtonDownPixmap = QPixmap("CircleRed.png");
    mCurrentButtonPixmap = mButtonUpPixmap;
            //QPixmap("CircleYellow.png");
    setGeometry(mCurrentButtonPixmap.rect());
    connect(this, &QPushButton::clicked, this, &ImageButton::setDown);

}

void ImageButton::paintEvent(QPaintEvent *e){
    QPainter p(this);
    p.drawPixmap(e->rect(),mCurrentButtonPixmap);
}
QSize ImageButton::sizeHint() const {
    return QSize(100,100);
}
QSize ImageButton::minimumSizeHint() const {
    return sizeHint();
}

void ImageButton::keyPressEvent(QKeyEvent *e) {
    setDown();
}
void ImageButton::setDown() {
//доделать с этого момента (17:18)
    mCurrentButtonPixmap = mButtonDownPixmap;
    update();
    QTimer::singleShot(100, this, &ImageButton::setUp);
}
void ImageButton::setUp() {
    mCurrentButtonPixmap = mButtonUpPixmap;
    update();
}

/*
class Printer:public QObject
{
   // Q_OBJECT
public slots:
    void printFinished(){
        std::cout<<"finished"<<std::endl;
    }
};
*/


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
    /*
    QPushButton *button1 = new QPushButton("One",window);
    QPushButton *button2 = new QPushButton("Two",window);
    QPushButton *button3 = new QPushButton("Three",window);
    QPushButton *button4 = new QPushButton("four",window);
    QPushButton *button5 = new QPushButton("five",window);
   // button1->move(40,50);
   //button2->move(140,150);
   // button3->move(200,200);
    QGridLayout *layout = new QGridLayout(window);
    layout->addWidget(button1,0,0);
    layout->addWidget(button2,0,1);
    layout->addWidget(button3,1,0,1,2);
    layout->addWidget(button4,2,0);
    layout->addWidget(button5,2,1);
     */

    /*
    ImageButton redButton(nullptr);
    redButton.setFixedSize(100,100);
    redButton.move(1000,400);
    QObject::connect(&redButton, &QPushButton::clicked,[](){std::cout<<"clicked\n";});
    redButton.show();
    */
    /*
    auto *slider = new QSlider(Qt::Horizontal);
    auto *spinbox = new QSpinBox();
    slider->setMinimum(0);
    slider->setMaximum(100);
    spinbox->setMinimum(0);
    spinbox->setMaximum(100);
    QObject::connect(slider, &QSlider::valueChanged, spinbox, &QSpinBox::setValue);
    QObject::connect(spinbox, QOverload<int>::of(&QSpinBox::valueChanged), slider, &QSlider::setValue);

    slider->resize(50,10);
    spinbox->resize(20,20);
    spinbox->move(900, 500);
    slider->move(800,500);
    slider->show();
    spinbox->show();
*/

    /*
    QTimer myTimer;
    Printer myPrinter;
    QObject::connect(&myTimer, &QTimer::timeout, &myPrinter, &Printer::printFinished);
    myTimer.start(2000);
*/
  //  QPushButton button("Hello world!", nullptr);
  //  button.resize(200, 100);
  //  button.show();
    return QApplication::exec();
}
