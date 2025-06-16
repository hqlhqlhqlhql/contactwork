#ifndef CONTACT_H
#define CONTACT_H

#include <QString>
#include <QDate>
#include <QJsonObject>

class Contact {
protected:
    QString name;
    QString phone;
    QString email;
    QString address;
    QString QQnumber;
    QString description;
    bool isFavorite;

public:
    virtual ~Contact() {}

    // 抽象函数：每个子类都有自己的类型名
    virtual QString getType() const = 0;

    // 抽象函数：子类必须实现 JSON 转换
    virtual QJsonObject toJson() const = 0;
    virtual void fromJson(const QJsonObject& obj) = 0;

    // 公共访问器（可省略 set/get 用属性操作）
    QString getName() const { return name; }
    QString getPhone() const { return phone; }
    QString getEmail() const { return email; }
    QString getAddress() const { return address; }
    QString getQQnumber() const { return QQnumber; }
    QString getDescription() const { return description; }
    bool getFavorite() const { return isFavorite; }

    void setName(const QString& n) { name = n; }
    void setPhone(const QString& p) { phone = p; }
    void setEmail(const QString& e) { email = e; }
    void setAddress(const QString& a) { address = a; }
    void setQQnumber(const QString& q) { QQnumber = q; }
    void setDescription(const QString& d) { description = d; }
    void setFavorite(bool f) { isFavorite = f; }
};

// class NormalContact : public Contact {
// public:
//     QString getType() const override { return "普通联系人"; }

//     QJsonObject toJson() const override;
//     void fromJson(const QJsonObject& obj) override;
// };

// class TeacherContact : public Contact {
// private:
//     QString course;

// public:
//     QString getCourse() const { return course; }
//     void setCourse(const QString& c) { course = c; }

//     QString getType() const override { return "教师"; }

//     QJsonObject toJson() const override;
//     void fromJson(const QJsonObject& obj) override;
// };

class StudentContact : public Contact {
private:
    QString className;
    QString studentID;

public:
    QString getType() const override { return "学生"; }

    QJsonObject toJson() const override {
        QJsonObject obj;
        obj["name"] = name;
        obj["phone"] = phone;
        obj["email"] = email;
        obj["address"] = address;
        obj["QQnumber"] = QQnumber;
        obj["description"] = description;
        obj["isFavorite"] = isFavorite;
        obj["className"] = className;
        obj["studentID"] = studentID;
        return obj;
    }

    void fromJson(const QJsonObject& obj) override {
        name = obj["name"].toString();
        phone = obj["phone"].toString();
        email = obj["email"].toString();
        address = obj["address"].toString();
        QQnumber = obj["QQnumber"].toString();
        description = obj["description"].toString();
        isFavorite = obj["isFavorite"].toBool();
        className = obj["className"].toString();
        studentID = obj["studentID"].toString();
    }

    // 可选：用于控制台输出
    void print() const {
        qDebug() << "[学生]" << name << studentID << className;
    }
};

// class BusinessContact : public Contact {
// private:
//     QString company;
//     QString workAddress;

// public:
//     QString getCompany() const { return company; }
//     QString getWorkAddress() const { return workAddress; }

//     void setCompany(const QString& c) { company = c; }
//     void setWorkAddress(const QString& w) { workAddress = w; }

//     QString getType() const override { return "商务"; }

//     QJsonObject toJson() const override;
//     void fromJson(const QJsonObject& obj) override;
// };

// class RelativeContact : public Contact {
// private:
//     QString relation; // 例如“哥哥”、“叔叔”

// public:
//     QString getRelation() const { return relation; }
//     void setRelation(const QString& r) { relation = r; }

//     QString getType() const override { return "亲戚"; }

//     QJsonObject toJson() const override;
//     void fromJson(const QJsonObject& obj) override;
// };

#endif // CONTACT_H
