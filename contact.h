#ifndef CONTACT_H
#define CONTACT_H

#include <QString>
#include <QJsonObject>
#include <QDate>

class Contact {
protected:
    QString name, second_name;
    QDate birthday;
    QString email;
    QString job;
    bool isFavorite;
    QString phone;
    QString qqnumber;

public:
    virtual ~Contact() {}

    virtual QJsonObject toJson() const = 0;
    virtual void fromJson(const QJsonObject& obj) = 0;
    virtual QString getType() const = 0;

    void setName(const QString& n);
    void setPhone(const QString & p);
    void setEmail(const QString& e);
    void setJob(const QString& a);
    void setQQnumber(const QString& q);
    void setDescription(const QString& d);
    void setbirthday(const QDate& d);
    void setFavorite(bool f);

    QDate getbirthday() const;
    QString getName() const;
    QString getPhone() const;
    QString getEmail() const;
    QString getJob() const;
    QString getQQnumber() const;
    QString getDescription() const;
    bool getFavorite() const;

};

// 以下是五个派生类声明
class normal_contact : public Contact {
public:
    QString getType() const override;
    QJsonObject toJson() const override;
    void fromJson(const QJsonObject& obj) override;
};

class teacher_contact : public Contact {
protected:
    QString course;

public:
    void setCourse(const QString& c);
    QString getCourse() const;
    QString getType() const override;
    QJsonObject toJson() const override;
    void fromJson(const QJsonObject& obj) override;
};

class colleague_contact : public Contact {
protected:
    QString company;

public:
    void setCompany(const QString& c);
    QString getcompany() const;
    QString getType() const override;
    QJsonObject toJson() const override;
    void fromJson(const QJsonObject& obj) override;
};

class student_contact : public Contact {
protected:
    QString studentID;
    QString student_class;

public:
    void setClassName(const QString& c);
    void setStudentID(const QString& s);
    QString getstudentId() const;
    QString getclassName() const;
    QString getType() const override;
    QJsonObject toJson() const override;
    void fromJson(const QJsonObject& obj) override;
};

class family_contact : public Contact {
protected:
    QString relation;

public:
    void setRelation(const QString& r);
    QString getRelation() const;
    QString getType() const override;
    QJsonObject toJson() const override;
    void fromJson(const QJsonObject& obj) override;
};

Q_DECLARE_METATYPE(std::shared_ptr<Contact>)

#endif // CONTACT_H
