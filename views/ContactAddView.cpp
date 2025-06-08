#include "ContactAddView.h"
#include <QHBoxLayout>
#include <QIcon>
#include <QVBoxLayout>
#include <QScrollArea>
#include "ContactSignalHub.h"
#include "ElaWidget.h"

#include "ElaTheme.h"
#include "ElaCalendarPicker.h"
#include "ElaComboBox.h"
#include "ElaScrollPageArea.h"
#include "ElaText.h"
#include "ElaLineEdit.h"
#include "ElaPushButton.h"
#include "ContactManager.h"
#include "ElaScrollArea.h"
#include "ElaCalendarPicker.h"

ContactAddView::ContactAddView(QWidget* parent)
    : ElaWidget(parent)
{
    connect(eTheme, &ElaTheme::themeModeChanged, this, [=]() {
        if (!parent)
        {
            update();
        }
    });

    setWindowModality(Qt::ApplicationModal);    //设置模态性，防止操作主窗口
    setFixedSize(450, 700);
    QWidget* centralWidget = new QWidget;
    setWindowTitle("添加联系人");

    ElaLineEdit* nameedit = new ElaLineEdit(this);
    ElaScrollPageArea* nameArea = new ElaScrollPageArea(this);
    QHBoxLayout* nameLayout = new QHBoxLayout(nameArea);
    ElaText* nametext = new ElaText("姓名");
    nameedit->setFixedSize(200,40);
    nametext->setTextPixelSize(15);
    nameLayout->addWidget(nametext);
    nameLayout->addSpacing(100);
    nameLayout->addWidget(nameedit);

    ElaLineEdit* qqnumberedit = new ElaLineEdit(this);
    ElaScrollPageArea* qqnumberArea = new ElaScrollPageArea(this);
    QHBoxLayout* qqnumberLayout = new QHBoxLayout(qqnumberArea);
    ElaText* qqnumbertext = new ElaText("QQ");
    qqnumberedit->setFixedSize(200,40);
    qqnumbertext->setTextPixelSize(15);
    qqnumberLayout->addWidget(qqnumbertext);
    qqnumberLayout->addSpacing(100);
    qqnumberLayout->addWidget(qqnumberedit);

    ElaLineEdit* jobedit = new ElaLineEdit(this);
    ElaScrollPageArea* jobArea = new ElaScrollPageArea(this);
    QHBoxLayout* jobLayout = new QHBoxLayout(jobArea);
    ElaText* jobtext = new ElaText("职业");
    jobedit->setFixedSize(200,40);
    jobtext->setTextPixelSize(15);
    jobLayout->addWidget(jobtext);
    jobLayout->addSpacing(100);
    jobLayout->addWidget(jobedit);

    ElaLineEdit* phoneedit = new ElaLineEdit(this);
    ElaScrollPageArea* phoneArea = new ElaScrollPageArea(this);
    QHBoxLayout* phoneLayout = new QHBoxLayout(phoneArea);
    ElaText* phonetext = new ElaText("电话");
    phoneedit->setFixedSize(200,40);
    phonetext->setTextPixelSize(15);
    phoneLayout->addWidget(phonetext);
    phoneLayout->addSpacing(100);
    phoneLayout->addWidget(phoneedit);

    _relation = new ElaComboBox(this);
    QStringList comboList{
        "待选择","普通","家人","同事","学生","教师"
    };
    _relation->addItems(comboList);
    _relation->setStyleSheet("background-color: black;");
    ElaScrollPageArea* comboBoxArea = new ElaScrollPageArea(this);
    QHBoxLayout* comboBoxLayout = new QHBoxLayout(comboBoxArea);
    ElaText* comboxtext = new ElaText("关系");
    comboxtext->setTextPixelSize(15);
    comboBoxLayout->addWidget(comboxtext);
    comboBoxLayout->addSpacing(100);
    comboBoxLayout->addWidget(_relation);

    ElaLineEdit* emailedit = new ElaLineEdit(this);
    ElaScrollPageArea* emailArea = new ElaScrollPageArea(this);
    QHBoxLayout* emailLayout = new QHBoxLayout(emailArea);
    ElaText* emailtext = new ElaText("邮箱");
    emailedit->setFixedSize(200,40);
    emailtext->setTextPixelSize(15);
    emailLayout->addWidget(emailtext);
    emailLayout->addSpacing(100);
    emailLayout->addWidget(emailedit);

    _birthday = new ElaCalendarPicker(this);
    ElaScrollPageArea* birthdayArea = new ElaScrollPageArea(this);
    QHBoxLayout* birthdayLayout = new QHBoxLayout(birthdayArea);
    ElaText* birthdaytext = new ElaText("生日");
    birthdaytext->setTextPixelSize(15);
    birthdayLayout->addWidget(birthdaytext);
    birthdayLayout->addSpacing(100);
    birthdayLayout->addWidget(_birthday);

    ElaLineEdit* name2edit = new ElaLineEdit(this);
    ElaScrollPageArea* name2Area = new ElaScrollPageArea(this);
    QHBoxLayout* name2Layout = new QHBoxLayout(name2Area);
    ElaText* name2text = new ElaText("备注");
    name2edit->setFixedSize(200,40);
    name2text->setTextPixelSize(15);
    name2Layout->addWidget(name2text);
    name2Layout->addSpacing(100);
    name2Layout->addWidget(name2edit);

    favo = new ElaComboBox(this);
    QStringList favolist{
        "待选择","否","是"
    };
    favo->addItems(favolist);
    favo->setStyleSheet("background-color: black;");
    ElaScrollPageArea* favoArea = new ElaScrollPageArea(this);
    QHBoxLayout* favoLayout = new QHBoxLayout(favoArea);
    ElaText* favotext = new ElaText("收藏");
    favotext->setTextPixelSize(15);
    favoLayout->addWidget(favotext);
    favoLayout->addSpacing(100);
    favoLayout->addWidget(favo);

    QVBoxLayout* centerLayout = new QVBoxLayout(centralWidget);
    centerLayout->addWidget(nameArea);
    centerLayout->addWidget(qqnumberArea);
    centerLayout->addWidget(jobArea);
    centerLayout->addWidget(phoneArea);
    centerLayout->addWidget(emailArea);
    centerLayout->addWidget(name2Area);
    centerLayout->addWidget(birthdayArea);
    centerLayout->addWidget(favoArea);
    centerLayout->addWidget(comboBoxArea);

    ElaScrollArea* centerArea = new ElaScrollArea;
    centerArea->setWidgetResizable(true);
    centerArea->setWidget(centralWidget);
    this->setStyleSheet("background-color: white;");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(centerArea);

    connect(_relation, &QComboBox::currentIndexChanged, this,[=](int index){
        for(int i = centerLayout->count()-1;i>=9;--i) {
            QLayoutItem* item = centerLayout->takeAt(i);
            if (item->widget()) {
                item->widget()->deleteLater();
            }
            delete item;
        }
        QString selectedRelation = _relation->itemText(index);
        if (selectedRelation == "家人") {
            ElaLineEdit* relationedit = new ElaLineEdit(this);
            ElaScrollPageArea* relationArea = new ElaScrollPageArea(this);
            QHBoxLayout* relationLayout = new QHBoxLayout(relationArea);
            ElaText* relationtext = new ElaText("具体关系");
            relationedit->setFixedSize(200,40);
            relationtext->setTextPixelSize(15);
            relationLayout->addWidget(relationtext);
            relationLayout->addSpacing(100);
            relationLayout->addWidget(relationedit);

            ElaPushButton* sure = new ElaPushButton("保存", this);
            ElaPushButton* desure = new ElaPushButton("取消", this);
            ElaScrollPageArea* buArea = new ElaScrollPageArea(this);
            QHBoxLayout* buLayout = new QHBoxLayout(buArea);
            buLayout->addWidget(sure);
            buLayout->addSpacing(40);
            buLayout->addWidget(desure);

            connect(desure,&ElaPushButton::clicked, this, [=]() {
                close();
            });
            connect(sure,&ElaPushButton::clicked, this, [=]() {
                QString path="contacts.json";
                ContactManager magisk;  //栈对象会自动释放，应该不会内存泄漏
                magisk.loadFromFile(path);
                auto stu = std::make_shared<family_contact>();
                stu->setName(nameedit->text());
                stu->setPhone(phoneedit->text());
                stu->setEmail(emailedit->text());
                stu->setQQnumber(qqnumberedit->text());
                stu->setDescription(name2edit->text());
                stu->setJob(jobedit->text());
                stu->setbirthday(_birthday->getSelectedDate());

                QString s = favo->currentText();
                if(s=="是"){
                    stu->setFavorite(true);
                }
                else if(s=="否")stu->setFavorite(false);

                stu->setRelation(relationedit->text());
                magisk.addContact(stu);
                if (magisk.saveToFile("contacts.json")) {
                    qDebug() << "保存成功";
                }
                emit ContactSignalHub::instance()->contactListChanged();
                //emit contactAdded();
                close();
            });

            centerLayout->addWidget(relationArea);
            centerLayout->addWidget(buArea);
        } else if (selectedRelation == "同事") {
            ElaLineEdit* companyedit = new ElaLineEdit(this);
            ElaScrollPageArea* companyArea = new ElaScrollPageArea(this);
            QHBoxLayout* companyLayout = new QHBoxLayout(companyArea);
            ElaText* companytext = new ElaText("公司");
            companyedit->setFixedSize(200,40);
            companytext->setTextPixelSize(15);
            companyLayout->addWidget(companytext);
            companyLayout->addSpacing(100);
            companyLayout->addWidget(companyedit);

            ElaPushButton* sure = new ElaPushButton("保存", this);
            ElaPushButton* desure = new ElaPushButton("取消", this);
            ElaScrollPageArea* buArea = new ElaScrollPageArea(this);
            QHBoxLayout* buLayout = new QHBoxLayout(buArea);
            buLayout->addWidget(sure);
            buLayout->addSpacing(40);
            buLayout->addWidget(desure);
            connect(desure,&ElaPushButton::clicked, this, [=]() {
                close();
            });
            connect(sure,&ElaPushButton::clicked, this, [=]() {
                QString path="contacts.json";
                ContactManager magisk;
                magisk.loadFromFile(path);
                auto stu = std::make_shared<colleague_contact>();
                stu->setName(nameedit->text());
                stu->setPhone(phoneedit->text());
                stu->setEmail(emailedit->text());
                stu->setQQnumber(qqnumberedit->text());
                stu->setDescription(name2edit->text());
                stu->setJob(jobedit->text());
                stu->setbirthday(_birthday->getSelectedDate());
                QString s = favo->currentText();
                if(s=="是"){
                    stu->setFavorite(true);
                }
                else if(s=="否")stu->setFavorite(false);
                stu->setCompany(companyedit->text());
                magisk.addContact(stu);
                if (magisk.saveToFile("contacts.json")) {
                    qDebug() << "保存成功";
                }
                emit ContactSignalHub::instance()->contactListChanged();
                //emit contactAdded();
                close();
            });

            centerLayout->addWidget(companyArea);
            centerLayout->addWidget(buArea);
        } else if (selectedRelation == "学生") {
            ElaLineEdit* classedit = new ElaLineEdit(this);
            ElaScrollPageArea* classArea = new ElaScrollPageArea(this);
            QHBoxLayout* classLayout = new QHBoxLayout(classArea);
            ElaText* classtext = new ElaText("班级");
            classedit->setFixedSize(200,40);
            classtext->setTextPixelSize(15);
            classLayout->addWidget(classtext);
            classLayout->addSpacing(100);
            classLayout->addWidget(classedit);
            ElaLineEdit* idedit = new ElaLineEdit(this);
            ElaScrollPageArea* idArea = new ElaScrollPageArea(this);
            QHBoxLayout* idLayout = new QHBoxLayout(idArea);
            ElaText* idtext = new ElaText("学号");
            idedit->setFixedSize(200,40);
            idtext->setTextPixelSize(15);
            idLayout->addWidget(idtext);
            idLayout->addSpacing(100);
            idLayout->addWidget(idedit);

            ElaPushButton* sure = new ElaPushButton("保存", this);
            ElaPushButton* desure = new ElaPushButton("取消", this);
            ElaScrollPageArea* buArea = new ElaScrollPageArea(this);
            QHBoxLayout* buLayout = new QHBoxLayout(buArea);
            buLayout->addWidget(sure);
            buLayout->addSpacing(40);
            buLayout->addWidget(desure);
            connect(desure,&ElaPushButton::clicked, this, [=]() {
                close();
            });
            connect(sure,&ElaPushButton::clicked, this, [=]() {
                QString path="contacts.json";
                ContactManager magisk;
                magisk.loadFromFile(path);
                auto stu = std::make_shared<student_contact>();
                stu->setName(nameedit->text());
                stu->setPhone(phoneedit->text());
                stu->setEmail(emailedit->text());
                stu->setQQnumber(qqnumberedit->text());
                stu->setDescription(name2edit->text());
                stu->setJob(jobedit->text());
                stu->setbirthday(_birthday->getSelectedDate());
                QString s = favo->currentText();
                if(s=="是"){
                    stu->setFavorite(true);
                }
                else if(s=="否")stu->setFavorite(false);
                stu->setClassName(classedit->text());
                stu->setStudentID(idedit->text());
                magisk.addContact(stu);
                if (magisk.saveToFile("contacts.json")) {
                    qDebug() << "保存成功";
                }
                emit ContactSignalHub::instance()->contactListChanged();
                //emit contactAdded();
                close();
            });
            centerLayout->addWidget(classArea);
            centerLayout->addWidget(idArea);
            centerLayout->addWidget(buArea);
        } else if(selectedRelation == "教师") {
            ElaLineEdit* crouseedit = new ElaLineEdit(this);
            ElaScrollPageArea* crouseArea = new ElaScrollPageArea(this);
            QHBoxLayout* crouseLayout = new QHBoxLayout(crouseArea);
            ElaText* crousetext = new ElaText("课程");
            crouseedit->setFixedSize(200,40);
            crousetext->setTextPixelSize(15);
            crouseLayout->addWidget(crousetext);
            crouseLayout->addSpacing(100);
            crouseLayout->addWidget(crouseedit);

            ElaPushButton* sure = new ElaPushButton("保存", this);
            ElaPushButton* desure = new ElaPushButton("取消", this);
            ElaScrollPageArea* buArea = new ElaScrollPageArea(this);
            QHBoxLayout* buLayout = new QHBoxLayout(buArea);
            buLayout->addWidget(sure);
            buLayout->addSpacing(40);
            buLayout->addWidget(desure);
            connect(desure,&ElaPushButton::clicked, this, [=]() {
                close();
            });
            connect(sure,&ElaPushButton::clicked, this, [=]() {
                QString path="contacts.json";
                ContactManager magisk;
                magisk.loadFromFile(path);
                auto stu = std::make_shared<teacher_contact>();
                stu->setName(nameedit->text());
                stu->setPhone(phoneedit->text());
                stu->setEmail(emailedit->text());
                stu->setQQnumber(qqnumberedit->text());
                stu->setDescription(name2edit->text());
                stu->setJob(jobedit->text());
                stu->setbirthday(_birthday->getSelectedDate());
                QString s = favo->currentText();
                if(s=="是"){
                    stu->setFavorite(true);
                }
                else if(s=="否")stu->setFavorite(false);
                stu->setCourse(crouseedit->text());
                magisk.addContact(stu);
                if (magisk.saveToFile("contacts.json")) {
                    qDebug() << "保存成功";
                }
                emit ContactSignalHub::instance()->contactListChanged();
                //emit contactAdded();
                close();
            });
            centerLayout->addWidget(crouseArea);
            centerLayout->addWidget(buArea);
        } else if(selectedRelation == "普通"){
            ElaPushButton* sure = new ElaPushButton("保存", this);
            ElaPushButton* desure = new ElaPushButton("取消", this);
            ElaScrollPageArea* buArea = new ElaScrollPageArea(this);
            QHBoxLayout* buLayout = new QHBoxLayout(buArea);
            buLayout->addWidget(sure);
            buLayout->addSpacing(40);
            buLayout->addWidget(desure);
            connect(desure,&ElaPushButton::clicked, this, [=]() {
                close();
            });
            connect(sure,&ElaPushButton::clicked, this, [=]() {
                QString path="contacts.json";
                ContactManager magisk;
                magisk.loadFromFile(path);
                auto stu = std::make_shared<normal_contact>();
                stu->setName(nameedit->text());
                stu->setPhone(phoneedit->text());
                stu->setEmail(emailedit->text());
                stu->setQQnumber(qqnumberedit->text());
                stu->setDescription(name2edit->text());
                stu->setJob(jobedit->text());
                stu->setbirthday(_birthday->getSelectedDate());
                QString s = favo->currentText();
                if(s=="是"){
                    stu->setFavorite(true);
                }
                else if(s=="否")stu->setFavorite(false);
                magisk.addContact(stu);
                if (magisk.saveToFile("contacts.json")) {
                    qDebug() << "保存成功";
                }
                emit ContactSignalHub::instance()->contactListChanged();
                //emit contactAdded();
                close();
            });

            centerLayout->addWidget(buArea);
        }
    });
}
