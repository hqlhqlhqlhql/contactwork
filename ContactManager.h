#ifndef CONTACTMANAGER_H
#define CONTACTMANAGER_H

#include "contact.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <vector>
#include <memory>

class ContactManager {
private:
    std::vector<std::shared_ptr<Contact>> contacts;

public:
    bool loadFromFile(const QString& path, bool reserve = 0);   //后面的参数决定是否保留原始数据
    bool saveToFile(const QString& path);
    void addContact(std::shared_ptr<Contact> c);
    void removeContact(std::shared_ptr<Contact> c);
    void clear();
    void modifyContact(std::shared_ptr<Contact> c);
    QStringList HandleBirthday();

    std::vector<std::shared_ptr<Contact>> getAll() const;
    std::vector<std::shared_ptr<Contact>> search(const QString& keyword, const QString& type = "") const;
    std::vector<std::shared_ptr<Contact>> getGroup(const QString& type) const;
};

#endif // CONTACTMANAGER_H
