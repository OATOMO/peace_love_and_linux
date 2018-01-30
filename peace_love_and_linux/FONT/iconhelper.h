/*			DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
                    Version 2, December 2004

 Copyright (C) 2017 Romain Lespinasse <443437061@qq.com.com>

 Everyone is permitted to copy and distribute verbatim or modified
 copies of this license document, and changing it is allowed as long
 as the name is changed.

            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

  0. You just DO WHAT THE FUCK YOU WANT TO.
*/

#ifndef ICONHELPER_H
#define ICONHELPER_H

#include <QObject>
#include <QFont>
#include <QFontDatabase>
#include <QMutex>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QTreeWidgetItem>

class IconHelper : public QObject
{
private:
    explicit IconHelper(QObject *parent = 0);
    QFont iconFont;
    static IconHelper* _instance;

public:
    static IconHelper* Instance()
    {
        static QMutex mutex;
        if(!_instance)
        {
            QMutexLocker locker(&mutex);
            if(!_instance)
            {
                _instance = new IconHelper;
            }
        }
        return _instance;
    }

    void SetIcon(QLabel* lab, QChar c, int size = 10,QString color = "color: rgb(0,0,0)");
    void SetIcon(QPushButton* btn, QChar c, int size = 10,QString color = "color: rgb(0,0,0)");

};

#endif // ICONHELPER_H</pre>
