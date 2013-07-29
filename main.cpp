#include <QtGui>
#include <iostream>
#include <QxtGlobalShortcut>
#include "glidenote.h"
#include <QStringList>
#include <ctime>
#include <QSplashScreen>
using namespace std;

bool debugstatus;

char* timestamp(){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [256];
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime (buffer,256,"%b %d %Y %T",timeinfo);
    return buffer;
}
void delay(int timedur)
{
    QTime dieTime= QTime::currentTime().addMSecs(timedur);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);    
}

Glidenote::Glidenote() : QMainWindow(NULL, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint)
{
    //QWidget::setWindowFlags( Qt::X11BypassWindowManagerHint );
    winstatus=0;

    // Declarations    
    openAction = new QAction(tr("&Load"), this);
    saveAction = new QAction(tr("&Save"), this);
    animAction = new QAction(tr("&Animate"), this);
    exitAction = new QAction(tr("E&xit"), this);
    aboutAction = new QAction(tr("A&bout"), this);

    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
    connect(animAction, SIGNAL(triggered()), this, SLOT(anim()));
    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    // Make a File menu
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    fileMenu->addAction(animAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
    fileMenu = menuBar()->addMenu(tr("&Help"));
    fileMenu->addAction(aboutAction);

    mainWidget = new QWidget;
    textEdit = new QTextEdit;
    searchEdit = new QLineEdit;
    addButton = new QPushButton;
    mainLayout = new QGridLayout;
    setCentralWidget(mainWidget);
    mainLayout->setSpacing(2);
    mainLayout->setContentsMargins(4, 4, 4, 4);
    searchEdit->setObjectName(QString::fromUtf8("searchEdit"));
    searchEdit->setGeometry(QRect(100, 21, 376, 21));
    mainLayout->addWidget(searchEdit, 0, 0, 1, 1);
    mainLayout->addWidget(textEdit, 1, 0, 1, 2);
    textEdit->setGeometry(QRect(0, 41, 376, 21));
    mainLayout->addWidget(addButton, 0,1,1,1);
    //addButton->setObjectName(QString::fromUtf8("addButton"));
    //addButton->setGeometry(QRect(378, 1, 21, 21));
    mainWidget->setLayout(mainLayout);

    animation = new QPropertyAnimation(this, "geometry");
    shortcut = new QxtGlobalShortcut;
    connect(shortcut, SIGNAL(activated()), this, SLOT(anim()));
    shortcut->setShortcut(QKeySequence("Shift+F12"));

    setWindowTitle(tr("Glidenote"));
    
    animdur=250;

    // Generate information on sizing based on the desktop size.
    heightratio=0.70;
    QDesktopWidget* desktop = QApplication::desktop();
    screenwidth=desktop->frameGeometry().width();
    screenheight=desktop->frameGeometry().height();
    appheight=screenheight*(heightratio);
    appvpos=(screenheight*(1-heightratio))/2;
    appwidth=400;
    apphpos=-400;
    
    // Output to console info about the sizing
    // For debugging purposes
    if(debugstatus==1){
        cout<<"Desktop: "<<screenwidth<<"x"<<screenheight<<endl;
        cout<<"App Height:"<<appheight<<"@"<<appvpos<<" per "<<heightratio<<endl;
        cout<<"App Width: "<<appwidth<<"@"<<apphpos<<endl;
    }
    // Set the start position and size
    this->setGeometry(QRect(apphpos,appvpos,appwidth,appheight));
}

void Glidenote::open()
{
    cout<<"Open"<<endl;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
        tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        QTextStream in(&file);
        textEdit->setText(in.readAll());
        file.close();
    }
}

void Glidenote::save()
{
    cout<<"save"<<endl;
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "",
        tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            // error message
        } else {
            QTextStream stream(&file);
            stream << textEdit->toPlainText();
            stream.flush();
            file.close();
        }
    }
}

void Glidenote::anim()
{
    if(winstatus==1){
        animation->setDuration(animdur);
        animation->setStartValue(QRect(0,appvpos,400,appheight));
        animation->setEndValue(QRect(-500,appvpos,400,appheight));
        animation->start();
        winstatus=0;
        if(debugstatus==1){
            cout<<timestamp()<<" - Closed window."<<endl;
        }
        delay(animdur);
        this->hide();
    }else if(winstatus==0){
        this->show();
        animation->setDuration(animdur);
        animation->setStartValue(QRect(-500,appvpos,400,appheight));
        animation->setEndValue(QRect(0,appvpos,400,appheight));
        animation->start();
        winstatus=1;
        if(debugstatus==1){

            cout<<timestamp()<<" - Opened window."<<endl;
        }
    }
    /*animation->setDuration(500);
    animation->setStartValue(QRect(-300,100,400,300));
    animation->setEndValue(QRect(0,100,400,300));
    animation->start();*/
}

void Glidenote::about(){
    
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    // Check for debug status
    for (int i = 1; i < argc; i++){
        if (i + 1 >= argc){
            if(argc>2){
                cout<<"Arguments passed: "<<argv[i]<<endl;
            } else {
                cout<<"Argument passed: "<<argv[i]<<endl;
            }
            
            if (strcmp(argv[i], "-D")==0) {
                debugstatus=1;
                cout<<"Debugging mode active."<<endl;
            } else {
                debugstatus=0;
            }
        }
    }

    Glidenote glidenote;
    //glidenote.show();

    return app.exec();
}

#include "main.moc"


