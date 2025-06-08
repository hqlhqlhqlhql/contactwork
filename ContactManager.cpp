#include "ContactManager.h"
#include <QDebug>
#include <QModelIndex>

bool ContactManager::loadFromFile(const QString& path, bool reserve) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "无法打开文件:" << path;
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) {
        qWarning() << "JSON格式错误";
        return false;
    }

    QJsonArray array = doc.array();
    if(!reserve) contacts.clear();
    // contacts.clear();

    for (const auto& val : array) {
        if (!val.isObject()) continue;
        QJsonObject obj = val.toObject();
        QString type = obj.value("type").toString();
        std::shared_ptr<Contact> c;

        if (type == "学生") c = std::make_shared<student_contact>();
        else if (type == "教师") c = std::make_shared<teacher_contact>();
        else if (type == "同事") c = std::make_shared<colleague_contact>();
        else if (type == "家人") c = std::make_shared<family_contact>();
        else c = std::make_shared<normal_contact>();

        c->fromJson(obj);
        // contacts.push_back(c);
        this->addContact(c);
    }

    return true;
}

bool ContactManager::saveToFile(const QString& path) {
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "无法写入文件:" << path;
        return false;
    }

    QJsonArray array;
    for (const auto& c : contacts) {
        QJsonObject obj = c->toJson();
        obj["type"] = c->getType();
        array.append(obj);
    }

    QJsonDocument doc(array);
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
    return true;
}

void ContactManager::modifyContact(std::shared_ptr<Contact> c){    //注意这里没有写入文件，要手动改
    for (auto & existing : contacts) {
        if (existing->getName() == c->getName()){
            existing = c;
        }
    }
}

void ContactManager::addContact(std::shared_ptr<Contact> c) {
    for (auto existing : contacts) {
        if (existing->getName() == c->getName()) return;  // 防止重复添加
    }
    contacts.push_back(c);
}

void ContactManager::removeContact(std::shared_ptr<Contact> c) { //注意这里没有写入文件，要手动改
    // if (!index.isValid()) {
    //     qWarning() << "无效的索引";
    //     return;
    // }
    // int row = index.row();
    // if (row >= 0 && row < contacts.size()) {
    //     contacts.erase(contacts.begin() + row);

    //     qDebug() << "行删除成功!";
    // } else {
    //     qWarning() << "无法删除，索引超出范围!";
    // }
    for (int i = 0; i < contacts.size(); i++ ) {
        if (contacts.at(i)->getName() == c->getName()){
            contacts.erase(contacts.begin() + i);
        }
    }
}

QStringList ContactManager::HandleBirthday(){
    QDate currentDate = QDate::currentDate();
    QStringList list;
    for (auto existing : contacts) {
        QDate toCompare = existing->getbirthday();
        if (toCompare.day() == currentDate.day() &&
            toCompare.month() == currentDate.month()){
            list.append(existing->getName());
        }
    }
    return list;
}

void ContactManager::clear() {
    contacts.clear();
}

std::vector<std::shared_ptr<Contact>> ContactManager::getAll() const {
    return contacts;
}

std::vector<std::shared_ptr<Contact>> ContactManager::search(const QString& keyword, const QString& type) const {
    if(type == ""){     //这里不用写默认参数，否则报错
        std::vector<std::shared_ptr<Contact>> result;
        for (const auto& c : contacts) {
            if (c->getName().contains(keyword, Qt::CaseInsensitive) ||
                c->getPhone().contains(keyword) ||
                c->getEmail().contains(keyword)) {
                result.push_back(c);
            }
        }
        return result;
    }
    if(type == "收藏"){
        std::vector<std::shared_ptr<Contact>> result;
        for (const auto& c : contacts) {
            if (c->getFavorite() && (c->getName().contains(keyword, Qt::CaseInsensitive) ||
                c->getPhone().contains(keyword) ||
                c->getEmail().contains(keyword))) {
                result.push_back(c);
            }
        }
        return result;
    }
    std::vector<std::shared_ptr<Contact>> result;
    for (const auto& c : contacts) {
        if (c->getType() == type && (c->getName().contains(keyword, Qt::CaseInsensitive) ||
            c->getPhone().contains(keyword) ||
            c->getEmail().contains(keyword))) {
            result.push_back(c);
        }
    }
    return result;
}

std::vector<std::shared_ptr<Contact>> ContactManager::getGroup(const QString& type) const {
    if(type == "收藏"){
        std::vector<std::shared_ptr<Contact>> result;
        for (const auto& c : contacts) {
            if (c->getFavorite()) {
                result.push_back(c);
            }
        }
        return result;
    }
    std::vector<std::shared_ptr<Contact>> result;
    for (const auto& c : contacts) {
        if (c->getType() == type) {
            result.push_back(c);
        }
    }
    return result;
}
