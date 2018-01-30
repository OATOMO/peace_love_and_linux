#include "iconhelper.h"

#define TTF_FILE ":/FONT/FONT/fontawesome-webfont.ttf"

IconHelper* IconHelper::_instance = 0;
IconHelper::IconHelper(QObject *) :
    QObject(qApp)
{
    int fontId = QFontDatabase::addApplicationFont(TTF_FILE);
    QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
    iconFont = QFont(fontName);
}

void IconHelper::SetIcon(QLabel *lab, QChar c, int size,QString color)
{
    iconFont.setPointSize(size);
    lab->setFont(iconFont);
    lab->setStyleSheet(color);
    lab->setText(c);
}

//color : "color: rgb(0, 160, 230);"
void IconHelper::SetIcon(QPushButton *btn, QChar c, int size,QString color)
{
    iconFont.setPointSize(size);
    btn->setFont(iconFont);
    btn->setStyleSheet(color);
    btn->setText(c);
}
