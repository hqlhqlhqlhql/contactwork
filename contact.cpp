#include "Contact.h"

// --- Contact 基类 Getter / Setter 实现 ---
void Contact::setName(const QString& n) { name = n; }
void Contact::setPhone(const QString& p) { phone = p; }
void Contact::setEmail(const QString& e) { email = e; }
void Contact::setJob(const QString& a) { job = a; }
void Contact::setQQnumber(const QString& q) { qqnumber = q; }
void Contact::setDescription(const QString& d) { second_name = d; }
void Contact::setbirthday(const QDate& d) { birthday = d; }
void Contact::setFavorite(bool f) { isFavorite = f; }

QString Contact::getName() const { return name; }
QString Contact::getPhone() const { return phone; }
QString Contact::getEmail() const { return email; }
QString Contact::getJob() const { return job; }
QString Contact::getQQnumber() const { return qqnumber; }
QString Contact::getDescription() const { return second_name; }
QDate Contact::getbirthday() const {return birthday;}
bool Contact::getFavorite() const { return isFavorite; }

// --- normal_contact ---
QString normal_contact::getType() const { return "普通"; }

QJsonObject normal_contact::toJson() const {
    QJsonObject obj;
    obj["name"] = name;
    obj["phone"] = phone;
    obj["email"] = email;
    obj["job"] = job;
    obj["QQnumber"] = qqnumber;
    obj["description"] = second_name;
    obj["isFavorite"] = isFavorite;
    obj["birthday"] = birthday.toString("yyyy-MM-dd");
    return obj;
}

void normal_contact::fromJson(const QJsonObject& obj) {
    name = obj["name"].toString();
    phone = obj["phone"].toString();
    email = obj["email"].toString();
    job = obj["job"].toString();
    qqnumber = obj["QQnumber"].toString();
    second_name = obj["description"].toString();
    isFavorite = obj["isFavorite"].toBool();
    birthday = QDate::fromString(obj["birthday"].toString(), "yyyy-MM-dd");
}

// --- teacher_contact ---
void teacher_contact::setCourse(const QString& c) { course = c; }
QString teacher_contact::getCourse() const { return course; }
QString teacher_contact::getType() const { return "教师"; }

QJsonObject teacher_contact::toJson() const {
    QJsonObject obj;
    obj["name"] = name;
    obj["phone"] = phone;
    obj["email"] = email;
    obj["job"] = job;
    obj["QQnumber"] = qqnumber;
    obj["description"] = second_name;
    obj["isFavorite"] = isFavorite;
    obj["birthday"] = birthday.toString("yyyy-MM-dd");
    obj["course"] = course;
    return obj;
}

void teacher_contact::fromJson(const QJsonObject& obj) {
    name = obj["name"].toString();
    phone = obj["phone"].toString();
    email = obj["email"].toString();
    job = obj["job"].toString();
    qqnumber = obj["QQnumber"].toString();
    second_name = obj["description"].toString();
    isFavorite = obj["isFavorite"].toBool();
    birthday = QDate::fromString(obj["birthday"].toString(), "yyyy-MM-dd");
    course = obj["course"].toString();
}

// --- colleague_contact ---
void colleague_contact::setCompany(const QString& c) { company = c; }
QString colleague_contact::getcompany() const { return company; }
QString colleague_contact::getType() const { return "同事"; }

QJsonObject colleague_contact::toJson() const {
    QJsonObject obj;
    obj["name"] = name;
    obj["phone"] = phone;
    obj["email"] = email;
    obj["job"] = job;
    obj["QQnumber"] = qqnumber;
    obj["description"] = second_name;
    obj["isFavorite"] = isFavorite;
    obj["birthday"] = birthday.toString("yyyy-MM-dd");
    obj["company"] = company;
    return obj;
}

void colleague_contact::fromJson(const QJsonObject& obj) {
    name = obj["name"].toString();
    phone = obj["phone"].toString();
    email = obj["email"].toString();
    job = obj["job"].toString();
    qqnumber = obj["QQnumber"].toString();
    second_name = obj["description"].toString();
    isFavorite = obj["isFavorite"].toBool();
    birthday = QDate::fromString(obj["birthday"].toString(), "yyyy-MM-dd");
    company = obj["company"].toString();
}

// --- student_contact ---
void student_contact::setClassName(const QString& c) { student_class = c; }
void student_contact::setStudentID(const QString& s) { studentID = s; }
QString student_contact::getstudentId() const { return studentID; }
QString student_contact::getclassName() const { return student_class; }
QString student_contact::getType() const { return "学生"; }

QJsonObject student_contact::toJson() const {
    QJsonObject obj;
    obj["name"] = name;
    obj["phone"] = phone;
    obj["email"] = email;
    obj["job"] = job;
    obj["QQnumber"] = qqnumber;
    obj["description"] = second_name;
    obj["isFavorite"] = isFavorite;
    obj["birthday"] = birthday.toString("yyyy-MM-dd");
    obj["className"] = student_class;
    obj["studentID"] = studentID;
    return obj;
}

void student_contact::fromJson(const QJsonObject& obj) {
    name = obj["name"].toString();
    phone = obj["phone"].toString();
    email = obj["email"].toString();
    job = obj["job"].toString();
    qqnumber = obj["QQnumber"].toString();
    second_name = obj["description"].toString();
    isFavorite = obj["isFavorite"].toBool();
    birthday = QDate::fromString(obj["birthday"].toString(), "yyyy-MM-dd");
    studentID = obj["studentID"].toString();
    student_class = obj["className"].toString();
}

// --- family_contact ---
void family_contact::setRelation(const QString& r) { relation = r; }
QString family_contact::getRelation() const { return relation; }
QString family_contact::getType() const { return "家人"; }

QJsonObject family_contact::toJson() const {
    QJsonObject obj;
    obj["name"] = name;
    obj["phone"] = phone;
    obj["email"] = email;
    obj["job"] = job;
    obj["QQnumber"] = qqnumber;
    obj["description"] = second_name;
    obj["isFavorite"] = isFavorite;
    obj["birthday"] = birthday.toString("yyyy-MM-dd");
    obj["relation"] = relation;
    return obj;
}

void family_contact::fromJson(const QJsonObject& obj) {
    name = obj["name"].toString();
    phone = obj["phone"].toString();
    email = obj["email"].toString();
    job = obj["job"].toString();
    qqnumber = obj["QQnumber"].toString();
    second_name = obj["description"].toString();
    isFavorite = obj["isFavorite"].toBool();
    birthday = QDate::fromString(obj["birthday"].toString(), "yyyy-MM-dd");
    relation = obj["relation"].toString();
}
