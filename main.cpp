#include "MainWindow.h"

#include <QApplication>
#include "ElaApplication.h"
#include <QLocale>
#include <QTranslator>
#include<iostream>
#include "ContactManager.h"

void test()
{
    std::cout<<"testing---"<<std::endl;
    qDebug() << QDate::currentDate();
    QString path="contacts.json";
    ContactManager magisk;
    magisk.loadFromFile(path);
    auto stu = std::make_shared<teacher_contact>();
    auto stu2 = std::make_shared<student_contact>();
    stu->setName("李四");
    stu->setPhone("138767845");
    stu->setEmail("zhangsan@example.com");
    //stu->setAddress("广东广州");
    stu->setQQnumber("12345");
    stu->setDescription("qt大神");
    stu->setFavorite(false);
    // stu2->setName("张三");
    // stu2->setPhone("123456789");
    // stu2->setEmail("zhangsan@example.com");
    // stu2->setAddress("广东广州");
    // stu2->setQQnumber("123456");
    // stu2->setDescription("优秀学生");
    // stu2->setFavorite(true);
     magisk.addContact(stu);
    // magisk.addContact(stu2);
    if (magisk.saveToFile("contacts.json")) {
        qDebug() << "保存成功";
    }

    // 清空再加载
    //manager.clear();
    if (magisk.loadFromFile("contacts.json")) {
        qDebug() << "加载成功";
        for (auto& c : magisk.getAll()) {
            qDebug() << "类型：" << c->getType();
            qDebug() << "姓名：" << c->getName();
            qDebug() <<""<<c->getEmail();
        }
    }
}
int main(int argc, char *argv[])
{
    // 在程序启动时（通常是 main 函数里）注册：
    qRegisterMetaType<std::shared_ptr<Contact>>("std::shared_ptr<Contact>");

    QApplication a(argc, argv);
    eApp->init();   //初始化图标等资源
    //test();
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "contactwork_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    return a.exec();
}
