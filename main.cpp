#include <QtGui>
#include <iostream>
#include <QxtGlobalShortcut>
#include "glidenote.h"
#include <QStringList>
#include <ctime>
#include <QSplashScreen>
using namespace std;

bool debugstatus;
bool linewrap;
int windir=0;
bool openfile;
QString openthis;


//Allows for timestamping debug output
char* timestamp(){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [256];
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime (buffer,256,"%b %d %Y %T",timeinfo);
    return buffer;
}

//Allows for pausing code, so animations are given time to complete
void delay(int timedur){
    QTime dieTime= QTime::currentTime().addMSecs(timedur);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);    
}

Glidenote::Glidenote() : QMainWindow(NULL, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint){
    // Declarations    
    openAction = new QAction(tr("&Load"), this);
    saveAction = new QAction(tr("&Save"), this);
    animAction = new QAction(tr("&Animate"), this);
    exitAction = new QAction(tr("E&xit"), this);
    aboutAction = new QAction(tr("A&bout"), this);
    // -Slots
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
    connect(animAction, SIGNAL(triggered()), this, SLOT(anim()));
    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    // -File menu
    fileMenu = menuBar()->addMenu(tr("&File"));                       //File menu
    fileMenu->addAction(openAction);                                  //Open item
    fileMenu->addAction(saveAction);                                  //Save item
    fileMenu->addSeparator();
    fileMenu->addAction(animAction);                                  //Toggle window state
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
    fileMenu = menuBar()->addMenu(tr("&Help"));                       //Help menu
    fileMenu->addAction(aboutAction);                                 //About item

    // -Widgets and Layout
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
    mainWidget->setLayout(mainLayout);
    addButton->setText(QApplication::translate("Widget", "+", 0, QApplication::UnicodeUTF8));

    // -Animation and hotkey
    animation = new QPropertyAnimation(this, "geometry");
    shortcut = new QxtGlobalShortcut;
    connect(shortcut, SIGNAL(activated()), this, SLOT(anim()));
    shortcut->setShortcut(QKeySequence("Shift+F12"));

    // Variable settings
    setWindowTitle(tr("Glidenote"));
    
    animdur=250;                                                      //Time in ms
    winstatus=0;                                                      //Closed
    if(windir==0){
        windir=4;                                                     //Spectacles, testacles, wallet, watch
    }

    scale();

    //Output to console info about the sizing
    //For debugging purposes
    if(debugstatus==1){
        cout<<"Desktop: "<<screenwidth<<"x"<<screenheight<<endl;
        cout<<"App Height:"<<appheight<<"@"<<appvpos<<" per "<<heightratio<<endl;
        cout<<"App Width: "<<appwidth<<"@"<<apphpos<<endl;
    }
    
    if(linewrap==1){
        textEdit->setLineWrapMode(QTextEdit::NoWrap);
    }

    //this->setGeometry(QRect(apphpos,appvpos,appwidth,appheight));     //Set the start position and size
    if(openfile==1){                                                  //Opens file if passed in argument
        //cout<<openthis.toStdString()<<endl;
        open(openthis);
        openfile=0;
    }
}

void Glidenote::scale(){
    // Generate information on sizing based on the desktop size.
    heightratio=0.70;
    QDesktopWidget* desktop = QApplication::desktop();
    screenwidth=desktop->frameGeometry().width();
    screenheight=desktop->frameGeometry().height();
    //apphpos=-400;                                                     //Offscreen
}

//Opening of files
void Glidenote::open(){
    if(debugstatus==1){cout<<"Open"<<endl;}                            //Debug output
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
        tr("Text Files (*.txt);;C++ Files (*.cpp *.h);;Shell Scripts (*.sh *.bat *.com);;Web Files (*.html *.htm *.css *.php *.asp *.js);;All Files (*.*)"));

    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        QTextStream in(&file);
        textEdit->setText(in.readAll());
        searchEdit->setText(fileName);
        file.close();
    }
}
void Glidenote::open(QString fileName){                               //Open File if from CLI argument
    if(debugstatus==1){cout<<"Open "<<fileName.toStdString()<<endl;}  //Debug output
    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        QTextStream in(&file);
        textEdit->setText(in.readAll());
        searchEdit->setText(fileName);
        file.close();
    }
}

//Saving files
void Glidenote::save(){												   //Save As
    if(debugstatus==1){cout<<"Save"<<endl;}                            //Debug output
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "",
        tr("Text Files (*.txt);;C++ Files (*.cpp *.h);;Shell Scripts (*.sh *.bat *.com);;Web Files (*.html *.htm *.css *.php *.asp *.js);;All Files (*.*)"));

    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            // error message
        } else {
			if(debugstatus==1){                                       //Additional debug output
				cout<<"Saved as "<<fileName.toStdString()<<endl;
			}
            QTextStream stream(&file);
            stream << textEdit->toPlainText();
            stream.flush();
            file.close();
        }
    }
}
void Glidenote::save(QString fileName){                               //Save File using specified name
    if(debugstatus==1){cout<<"Save "<<fileName.toStdString()<<endl;}  //Debug output
    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        QTextStream stream(&file);
        stream << textEdit->toPlainText();
        //searchEdit->setText(fileName);
        stream.flush();
        file.close();
    }
}

//Animation for opening and closing
void Glidenote::anim(){
    scale();
    if(winstatus==1){                                                 //Hide
        if(windir==1){                                                //Top
            appwidth=screenwidth*heightratio;
            appheight=400;
            starthpos=(screenwidth-appwidth)/2;
            endhpos=starthpos;
            startvpos=0;
            endvpos=0-appheight;
        } else if(windir==2){                                         //Bottom
            appwidth=screenwidth*heightratio;
            appheight=400;
            starthpos=(screenwidth-appwidth)/2;
            endhpos=starthpos;
            startvpos=screenheight-appheight;
            endvpos=screenheight+appheight;
        } else if(windir==3){                                         //Left
            appheight=screenheight*(heightratio);
            appvpos=(screenheight*(1-heightratio))/2;
            appwidth=400;
            startvpos=appvpos;
            endvpos=appvpos;
            starthpos=0;
            endhpos=0-appwidth;
        } else if(windir==4){                                         //Right
            appheight=screenheight*(heightratio);
            appvpos=(screenheight*(1-heightratio))/2;
            appwidth=400;
            startvpos=appvpos;
            endvpos=appvpos;
            starthpos=screenwidth-appwidth;
            endhpos=screenwidth+appwidth;
        }
        animation->setDuration(animdur);
        animation->setStartValue(QRect(starthpos,startvpos,appwidth,appheight));
        animation->setEndValue(QRect(endhpos,endvpos,appwidth,appheight));
        animation->start();                                           //Begin animation
        winstatus=0;                                                  //Toggle status for next check
        if(debugstatus==1){                                           //Debug output
            cout<<timestamp()<<" - Closed window."<<endl;
        }
        delay(animdur);
        this->hide();                                                 //Hide the Window
    }else if(winstatus==0){                                           //Show
        if(windir==1){                                                //Top
            appwidth=screenwidth*heightratio;
            appheight=400;
            starthpos=(screenwidth-appwidth)/2;
            endhpos=starthpos;
            startvpos=0-appheight;
            endvpos=0;
        } else if(windir==2){                                         //Bottom
            appwidth=screenwidth*heightratio;
            appheight=400;
            starthpos=(screenwidth-appwidth)/2;
            endhpos=starthpos;
            startvpos=screenheight+appheight;
            endvpos=screenheight-appheight;
        } else if(windir==3){                                         //Left
            appheight=screenheight*(heightratio);
            appvpos=(screenheight*(1-heightratio))/2;
            appwidth=400;
            startvpos=appvpos;
            endvpos=appvpos;
            starthpos=0-appwidth;
            endhpos=0;
        } else if(windir==4){                                         //Right
            appheight=screenheight*(heightratio);
            appvpos=(screenheight*(1-heightratio))/2;
            appwidth=400;
            startvpos=appvpos;
            endvpos=appvpos;
            starthpos=screenwidth+appwidth;
            endhpos=screenwidth-appwidth;
        }
        this->setGeometry(QRect(starthpos,endvpos,appwidth,appheight));
        this->show();                                                 //Make the window appear
        animation->setDuration(animdur);
        animation->setStartValue(QRect(starthpos,endvpos,appwidth,appheight));
        animation->setEndValue(QRect(endhpos,endvpos,appwidth,appheight));
        animation->start();                                           //Begin animation
        winstatus=1;
        if(debugstatus==1){                                           //Debugging
            cout<<timestamp()<<" - Opened window."<<endl;
        }
    }
}

//Code for showing an about screen
void Glidenote::about(){
    //Code to be added
}

int main(int argc, char **argv){
    QApplication app(argc, argv);

    // Check arguments
    if (argc!=1){
        if(argc>2){                                                   //Plural or singular check
            cout<<"Arguments passed: ";
        } else if(argc==2) {
            cout<<"Argument passed: ";
        }
        for (int x = 1; x < argc;x++){                                //Output the arguments
            cout<<argv[x]<<" ";
        }
        cout<<endl;
    }

    for (int i = 1; i < argc; i++){                                   //Loop through number of arguments
            if (strcmp(argv[i], "-D")==0) {                           //Check for the debug flag
                debugstatus=1;                                        //Set debugging on
                cout<<"Debugging mode active."<<endl;                 //report to console
            } else if (strcmp(argv[i], "-w")==0) {                    //No Linewrap
                linewrap=1;
            } else if (strcmp(argv[i], "-t")==0){                     //Top
                windir=1;
            } else if (strcmp(argv[i], "-b")==0){                     //Bottom
                windir=2;
            } else if (strcmp(argv[i], "-l")==0){                     //Left
                windir=3;
            } else if (strcmp(argv[i], "-r")==0){                     //Right
                windir=4;
            } else if (strcmp(argv[i], "-h")==0 || strcmp(argv[i], "--help")==0){
                cout<<"Glidenote by Keith \"Hellmark\" Brown"<<endl<<endl;
                cout<<"-f <file>    Opens the given file."<<endl;
                cout<<"-D           Debug"<<endl;
                cout<<"-w           Disable Linewrap"<<endl;
                cout<<"-t           Located at top of screen"<<endl;
                cout<<"-b           Located at bottom of screen"<<endl;
                cout<<"-l           Located on left side of screen"<<endl;
                cout<<"-r           Located on right side of screen"<<endl<<endl;
                exit(0);
            } else if (strcmp(argv[i], "-f")==0){                     //File open
                openthis=argv[i+1];
                openfile=1;
            } else if (strcmp(argv[i], "-D")==1){
                debugstatus=0;                                        //If no debug flag, disable
            }
    }
    if(debugstatus==1){
        cout<<"Location: ";
        if(windir==1){cout<<"top"<<endl;}
        if(windir==2){cout<<"bottom"<<endl;}
        if(windir==3){cout<<"left"<<endl;}
        if(windir==4){cout<<"right"<<endl;}
    }
    Glidenote glidenote;                                              //Declaration for using all the goodies
    //glidenote.show();                                               //Only used here if you want the window
                                                                      //to be shown at start
    return app.exec();                                                //Return status
}

#include "main.moc"
