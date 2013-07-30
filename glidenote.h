#ifndef GLIDENOTE_H
#define GLIDENOTE_H

#include <QtGui>
#include <QWidget>
#include <QxtGlobalShortcut>
#include <QStringList>

class Glidenote : public QMainWindow
{
    Q_OBJECT

public:
    Glidenote();


private slots:
    void open();
    void save();
    void anim();
    void about();
    void scale();

private:
    QWidget   *mainWidget;
    QTextEdit *textEdit;
    QLineEdit *searchEdit;
    QPushButton *addButton;
    QGridLayout *mainLayout;
    QPropertyAnimation *animation;

    QAction *openAction;
    QAction *saveAction;
    QAction *animAction;
    QAction *exitAction;
    QAction *aboutAction;

    QMenu *fileMenu;

    QxtGlobalShortcut *shortcut; 
    bool winstatus;
    int screenheight;
    int screenwidth;
    float heightratio;
    int appheight;
    int appwidth;
    int appvpos;
    int apphpos;
    int animdur;
    QStringList *arguments;
};
#endif // GLIDENOTE_H
