#ifndef CONTACTSIGNALHUB_H
#define CONTACTSIGNALHUB_H

#include <QObject>

class ContactSignalHub : public QObject {
    Q_OBJECT
public:
    // 提供一个公用的的静态对象，专业叫法“单例“
    static ContactSignalHub* instance();

signals:
    void contactListChanged(); // 添加或修改联系人后发出的信号
};

#endif // CONTACTSIGNALHUB_H
