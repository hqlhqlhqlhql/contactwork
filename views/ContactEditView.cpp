#include "ContactEditView.h"
#include <QHBoxLayout>
#include <QIcon>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QApplication>
#include <QClipboard>
#include <QDate>
#include "ContactSignalHub.h"

#include "ElaComboBox.h"
#include "ElaScrollPageArea.h"
#include "ElaText.h"
#include "ElaLineEdit.h"
#include "ElaPushButton.h"
#include "contact.h"
#include "ContactManager.h"
#include "ElaScrollArea.h"
#include "ElaMessageBar.h"

ContactEditView::ContactEditView(ContactManager* magisk,const QModelIndex & index, QWidget* parent)
    : m(magisk),ElaWidget(parent), _index(index)
{
    // connect(ContactSignalHub::instance(), &ContactSignalHub::contactListChanged, this, [=]() {
    //     qDebug() << "EditView 检测到数据更新，自动关闭";
    //     this->close(); // 避免访问已失效数据
    // });

    auto var = index.data(Qt::DisplayRole);
    auto contactItem = var.value<std::shared_ptr<Contact>>();
    QString contactName = contactItem->getName();
    QString contactPhone = contactItem->getPhone();
    QString contactDescription = contactItem->getDescription();
    QString contactJob = contactItem->getType();
    QString contactQQnumber = contactItem->getQQnumber();
    QString contactemail = contactItem->getEmail();
    bool f = contactItem->getFavorite();
    QDate birthday = contactItem->getbirthday();

    setWindowModality(Qt::ApplicationModal);    //模态性
    setFixedSize(450, 800);
    QWidget* centralWidget = new QWidget(this);
    setWindowTitle("修改联系人");

    ElaLineEdit* nameedit = new ElaLineEdit(this);
    nameedit->setReadOnly(true);
    ElaScrollPageArea* nameArea = new ElaScrollPageArea(this);
    QHBoxLayout* nameLayout = new QHBoxLayout(nameArea);
    ElaText* nametext = new ElaText("姓名");
    nameedit->setFixedSize(200,40);
    nameedit->setText(contactName);
    nametext->setTextPixelSize(15);
    nameLayout->addWidget(nametext);
    nameLayout->addSpacing(100);
    nameLayout->addWidget(nameedit);

    ElaLineEdit* qqnumberedit = new ElaLineEdit(this);
    ElaScrollPageArea* qqnumberArea = new ElaScrollPageArea(this);
    QHBoxLayout* qqnumberLayout = new QHBoxLayout(qqnumberArea);
    ElaText* qqnumbertext = new ElaText("QQ");
    qqnumberedit->setFixedSize(200,40);
    qqnumberedit->setText(contactQQnumber);
    qqnumbertext->setTextPixelSize(15);
    qqnumberLayout->addWidget(qqnumbertext);
    qqnumberLayout->addSpacing(100);
    qqnumberLayout->addWidget(qqnumberedit);

    ElaLineEdit* jobedit = new ElaLineEdit(this);
    ElaScrollPageArea* jobArea = new ElaScrollPageArea(this);
    QHBoxLayout* jobLayout = new QHBoxLayout(jobArea);
    ElaText* jobtext = new ElaText("职业");
    jobedit->setFixedSize(200,40);
    jobedit->setText(contactJob);
    jobtext->setTextPixelSize(15);
    jobLayout->addWidget(jobtext);
    jobLayout->addSpacing(100);
    jobLayout->addWidget(jobedit);

    ElaLineEdit* phoneedit = new ElaLineEdit(this);
    ElaScrollPageArea* phoneArea = new ElaScrollPageArea(this);
    QHBoxLayout* phoneLayout = new QHBoxLayout(phoneArea);
    ElaText* phonetext = new ElaText("电话");
    phoneedit->setFixedSize(200,40);
    phoneedit->setText(contactPhone);
    phonetext->setTextPixelSize(15);
    phoneLayout->addWidget(phonetext);
    phoneLayout->addSpacing(100);
    phoneLayout->addWidget(phoneedit);

    _relation = new ElaComboBox(this);
    QStringList comboList{
        "家人","同事","学生","教师","普通"
    };
    _relation->addItems(comboList);
    _relation->setStyleSheet("QComboBox { color: black; }");
    ElaScrollPageArea* comboBoxArea = new ElaScrollPageArea(this);
    QHBoxLayout* comboBoxLayout = new QHBoxLayout(comboBoxArea);
    ElaText* comboxtext = new ElaText("关系");
    _relation->setCurrentText(contactJob);
    _relation->setEnabled(false);
    comboxtext->setTextPixelSize(15);
    comboBoxLayout->addWidget(comboxtext);
    comboBoxLayout->addSpacing(100);
    comboBoxLayout->addWidget(_relation);

    ElaLineEdit* emailedit = new ElaLineEdit(this);
    ElaScrollPageArea* emailArea = new ElaScrollPageArea(this);
    QHBoxLayout* emailLayout = new QHBoxLayout(emailArea);
    ElaText* emailtext = new ElaText("邮箱");
    emailedit->setFixedSize(200,40);
    emailedit->setText(contactemail);
    emailtext->setTextPixelSize(15);
    emailLayout->addWidget(emailtext);
    emailLayout->addSpacing(100);
    emailLayout->addWidget(emailedit);

    _birthday = new ElaCalendarPicker(this);
    ElaScrollPageArea* birthdayArea = new ElaScrollPageArea(this);
    QHBoxLayout* birthdayLayout = new QHBoxLayout(birthdayArea);
    ElaText* birthdaytext = new ElaText("生日");
    _birthday->setSelectedDate(birthday);
    birthdaytext->setTextPixelSize(15);
    birthdayLayout->addWidget(birthdaytext);
    birthdayLayout->addSpacing(100);
    birthdayLayout->addWidget(_birthday);

    ElaLineEdit* name2edit = new ElaLineEdit(this);
    ElaScrollPageArea* name2Area = new ElaScrollPageArea(this);
    QHBoxLayout* name2Layout = new QHBoxLayout(name2Area);
    ElaText* name2text = new ElaText("备注");
    name2edit->setFixedSize(200,40);
    name2edit->setText(contactDescription);
    name2text->setTextPixelSize(15);
    name2Layout->addWidget(name2text);
    name2Layout->addSpacing(100);
    name2Layout->addWidget(name2edit);

    favo = new ElaComboBox(this);
    QStringList favolist{
        "待选择","否","是"
    };
    favo->addItems(favolist);
    favo->setStyleSheet("QComboBox { color: black; }");
    ElaScrollPageArea* favoArea = new ElaScrollPageArea(this);
    QHBoxLayout* favoLayout = new QHBoxLayout(favoArea);
    ElaText* favotext = new ElaText("收藏");
    if(f)favo->setCurrentText("是");
    else favo->setCurrentText("否");
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

    ElaScrollArea* centerArea = new ElaScrollArea(this);
    centerArea->setWidgetResizable(true);
    centerArea->setWidget(centralWidget);
    centerArea->setStyleSheet("background-color: white;");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(centerArea);
    //centralWidget->setLayout(mainLayout);

    QString selectedRelation = contactJob;

    if (selectedRelation == "家人") {
        auto stu = std::dynamic_pointer_cast<family_contact>(contactItem);
        ElaLineEdit* relationedit = new ElaLineEdit(this);
        ElaScrollPageArea* relationArea = new ElaScrollPageArea(this);
        QHBoxLayout* relationLayout = new QHBoxLayout(relationArea);
        ElaText* relationtext = new ElaText("具体关系");
        relationedit->setFixedSize(200,40);
        relationedit->setText(stu->getRelation());
        relationtext->setTextPixelSize(15);
        relationLayout->addWidget(relationtext);
        relationLayout->addSpacing(100);
        relationLayout->addWidget(relationedit);

        ElaPushButton* sure = new ElaPushButton("修改", this);
        ElaPushButton* desure = new ElaPushButton("取消", this);
        ElaPushButton* de = new ElaPushButton("删除", this);
        ElaScrollPageArea* buArea = new ElaScrollPageArea(this);
        QHBoxLayout* buLayout = new QHBoxLayout(buArea);
        buLayout->addWidget(sure);
        buLayout->addSpacing(20);
        buLayout->addWidget(de);
        buLayout->addSpacing(20);
        buLayout->addWidget(desure);
        connect(desure,&ElaPushButton::clicked, this, [=]() {
            close();
        });
        connect(de,&ElaPushButton::clicked, this, [=]() {
            m->removeContact(stu);
            if (m->saveToFile("contacts.json")) {
                emit ContactSignalHub::instance()->contactListChanged();
                //emit contactModified();
                qDebug() << "删除成功";
            }
            close();
        });
        connect(sure,&ElaPushButton::clicked, this, [=]() {
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
            //magisk.modifyContact(stu);
            if (m->saveToFile("contacts.json")) {
                emit ContactSignalHub::instance()->contactListChanged();
                //emit contactModified();
                qDebug() << "修改成功";
            }
            close();
        });
        centerLayout->addWidget(relationArea);
        centerLayout->addWidget(buArea);
        ElaPushButton* copyButton = new ElaPushButton("复制", this);  // 创建复制按钮
        ElaScrollPageArea* copyButtonArea = new ElaScrollPageArea(this);  // 创建按钮区域
        QHBoxLayout* copyButtonLayout = new QHBoxLayout(copyButtonArea);  // 创建布局
        copyButtonLayout->addWidget(copyButton);  // 将按钮添加到布局中
        centerLayout->addWidget(copyButtonArea);
        connect(copyButton, &ElaPushButton::clicked, this, [=]() {
            QString contactInfo;  // 用来存储联系人信息
            contactInfo.append("姓名: " + nameedit->text() + "\n");
            contactInfo.append("QQ: " + qqnumberedit->text() + "\n");
            contactInfo.append("职业: " + jobedit->text() + "\n");
            contactInfo.append("电话: " + phoneedit->text() + "\n");
            contactInfo.append("邮箱: " + emailedit->text() + "\n");
            contactInfo.append("生日: " + _birthday->getSelectedDate().toString("yyyy-MM-dd") + "\n");
            contactInfo.append("备注: " + name2edit->text() + "\n");
            contactInfo.append("关系: " + _relation->currentText() + "\n");
            contactInfo.append("具体关系: " + relationedit->text() + "\n");
            contactInfo.append("收藏: " + favo->currentText() + "\n");
            QClipboard *clipboard = QApplication::clipboard();
            clipboard->setText(contactInfo);

            // 可选：显示一条信息提示用户已复制
            qDebug() << "联系人信息已复制到剪贴板！";
        });
        connect(copyButton, &ElaPushButton::clicked, this, [=]() {
            ElaMessageBar::success(ElaMessageBarType::Top, "复制完成", "已被复制到剪贴板", 1000, this);
        });
    } else if (selectedRelation == "同事") {
        auto stu = std::dynamic_pointer_cast<colleague_contact>(contactItem);
        ElaLineEdit* companyedit = new ElaLineEdit(this);
        ElaScrollPageArea* companyArea = new ElaScrollPageArea(this);
        QHBoxLayout* companyLayout = new QHBoxLayout(companyArea);
        ElaText* companytext = new ElaText("公司");
        companyedit->setFixedSize(200,40);
        companyedit->setText(stu->getcompany());
        companytext->setTextPixelSize(15);
        companyLayout->addWidget(companytext);
        companyLayout->addSpacing(100);
        companyLayout->addWidget(companyedit);

        ElaPushButton* sure = new ElaPushButton("修改", this);
        ElaPushButton* desure = new ElaPushButton("取消", this);
        ElaPushButton* de = new ElaPushButton("删除", this);
        ElaScrollPageArea* buArea = new ElaScrollPageArea(this);
        QHBoxLayout* buLayout = new QHBoxLayout(buArea);
        buLayout->addWidget(sure);
        buLayout->addSpacing(20);
        buLayout->addWidget(de);
        buLayout->addSpacing(20);
        buLayout->addWidget(desure);
        connect(desure,&ElaPushButton::clicked, this, [=]() {
            close();
        });
        connect(de,&ElaPushButton::clicked, this, [=]() {
            m->removeContact(stu);
            if (m->saveToFile("contacts.json")) {
                emit ContactSignalHub::instance()->contactListChanged();
                //emit contactModified();
                qDebug() << "删除成功";
            }
            close();
        });
        connect(sure,&ElaPushButton::clicked, this, [=]() {
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
            //magisk.modifyContact(stu);
            if (m->saveToFile("contacts.json")) {
                emit ContactSignalHub::instance()->contactListChanged();
                //emit contactModified();
                qDebug() << "修改成功";
            }
            close();
        });

        centerLayout->addWidget(companyArea);
        centerLayout->addWidget(buArea);
        ElaPushButton* copyButton = new ElaPushButton("复制", this);  // 创建复制按钮
        ElaScrollPageArea* copyButtonArea = new ElaScrollPageArea(this);  // 创建按钮区域
        QHBoxLayout* copyButtonLayout = new QHBoxLayout(copyButtonArea);  // 创建布局
        copyButtonLayout->addWidget(copyButton);  // 将按钮添加到布局中
        centerLayout->addWidget(copyButtonArea);
        connect(copyButton, &ElaPushButton::clicked, this, [=]() {
            QString contactInfo;  // 用来存储联系人信息
            contactInfo.append("姓名: " + nameedit->text() + "\n");
            contactInfo.append("QQ: " + qqnumberedit->text() + "\n");
            contactInfo.append("职业: " + jobedit->text() + "\n");
            contactInfo.append("电话: " + phoneedit->text() + "\n");
            contactInfo.append("邮箱: " + emailedit->text() + "\n");
            contactInfo.append("生日: " + _birthday->getSelectedDate().toString("yyyy-MM-dd") + "\n");
            contactInfo.append("备注: " + name2edit->text() + "\n");
            contactInfo.append("关系: " + _relation->currentText() + "\n");
            contactInfo.append("公司: " + companyedit->text() + "\n");
            contactInfo.append("收藏: " + favo->currentText() + "\n");
            QClipboard *clipboard = QApplication::clipboard();
            clipboard->setText(contactInfo);

            // 可选：显示一条信息提示用户已复制
            qDebug() << "联系人信息已复制到剪贴板！";
        });
        connect(copyButton, &ElaPushButton::clicked, this, [=]() {
            ElaMessageBar::success(ElaMessageBarType::Top, "复制完成", "已被复制到剪贴板", 1000, this);
        });
    } else if (selectedRelation == "学生") {
        auto stu = std::dynamic_pointer_cast<student_contact>(contactItem);
        ElaLineEdit* classedit = new ElaLineEdit(this);
        ElaScrollPageArea* classArea = new ElaScrollPageArea(this);
        QHBoxLayout* classLayout = new QHBoxLayout(classArea);
        ElaText* classtext = new ElaText("班级");
        classedit->setFixedSize(200,40);
        classedit->setText(stu->getclassName());
        classtext->setTextPixelSize(15);
        classLayout->addWidget(classtext);
        classLayout->addSpacing(100);
        classLayout->addWidget(classedit);
        ElaLineEdit* idedit = new ElaLineEdit(this);
        ElaScrollPageArea* idArea = new ElaScrollPageArea(this);
        QHBoxLayout* idLayout = new QHBoxLayout(idArea);
        ElaText* idtext = new ElaText("学号");
        idedit->setFixedSize(200,40);
        idedit->setText(stu->getstudentId());
        idtext->setTextPixelSize(15);
        idLayout->addWidget(idtext);
        idLayout->addSpacing(100);
        idLayout->addWidget(idedit);

        ElaPushButton* sure = new ElaPushButton("修改", this);
        ElaPushButton* desure = new ElaPushButton("取消", this);
        ElaPushButton* de = new ElaPushButton("删除", this);
        ElaScrollPageArea* buArea = new ElaScrollPageArea(this);
        QHBoxLayout* buLayout = new QHBoxLayout(buArea);
        buLayout->addWidget(sure);
        buLayout->addSpacing(20);
        buLayout->addWidget(de);
        buLayout->addSpacing(20);
        buLayout->addWidget(desure);
        connect(desure,&ElaPushButton::clicked, this, [=]() {
            close();
        });
        connect(de,&ElaPushButton::clicked, this, [=]() {
            m->removeContact(stu);
            if (m->saveToFile("contacts.json")) {
                emit ContactSignalHub::instance()->contactListChanged();
                //emit contactModified();
                qDebug() << "删除成功";
            }
            close();
        });
        connect(sure,&ElaPushButton::clicked, this, [=]() {
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
            //magisk.modifyContact(stu);
            if (m->saveToFile("contacts.json")) {
                emit ContactSignalHub::instance()->contactListChanged();
                //emit contactModified();
                qDebug() << "修改成功";
            }
            close();
        });
        centerLayout->addWidget(classArea);
        centerLayout->addWidget(idArea);
        centerLayout->addWidget(buArea);
        ElaPushButton* copyButton = new ElaPushButton("复制", this);  // 创建复制按钮
        ElaScrollPageArea* copyButtonArea = new ElaScrollPageArea(this);  // 创建按钮区域
        QHBoxLayout* copyButtonLayout = new QHBoxLayout(copyButtonArea);  // 创建布局
        copyButtonLayout->addWidget(copyButton);  // 将按钮添加到布局中
        centerLayout->addWidget(copyButtonArea);
        connect(copyButton, &ElaPushButton::clicked, this, [=]() {
            QString contactInfo;  // 用来存储联系人信息
            contactInfo.append("姓名: " + nameedit->text() + "\n");
            contactInfo.append("QQ: " + qqnumberedit->text() + "\n");
            contactInfo.append("职业: " + jobedit->text() + "\n");
            contactInfo.append("电话: " + phoneedit->text() + "\n");
            contactInfo.append("邮箱: " + emailedit->text() + "\n");
            contactInfo.append("生日: " + _birthday->getSelectedDate().toString("yyyy-MM-dd") + "\n");
            contactInfo.append("备注: " + name2edit->text() + "\n");
            contactInfo.append("关系: " + _relation->currentText() + "\n");
            contactInfo.append("班级: " + classedit->text() + "\n");
            contactInfo.append("学号: " + idedit->text() + "\n");
            contactInfo.append("收藏: " + favo->currentText() + "\n");
            QClipboard *clipboard = QApplication::clipboard();
            clipboard->setText(contactInfo);

            // 可选：显示一条信息提示用户已复制
            qDebug() << "联系人信息已复制到剪贴板！";
        });
        connect(copyButton, &ElaPushButton::clicked, this, [=]() {
            ElaMessageBar::success(ElaMessageBarType::Top, "复制完成", "已被复制到剪贴板", 1000, this);
        });
    } else if(selectedRelation == "教师") {
        auto stu = std::dynamic_pointer_cast<teacher_contact>(contactItem);
        ElaLineEdit* crouseedit = new ElaLineEdit(this);
        ElaScrollPageArea* crouseArea = new ElaScrollPageArea(this);
        QHBoxLayout* crouseLayout = new QHBoxLayout(crouseArea);
        ElaText* crousetext = new ElaText("课程");
        crouseedit->setFixedSize(200,40);
        crouseedit->setText(stu->getCourse());
        crousetext->setTextPixelSize(15);
        crouseLayout->addWidget(crousetext);
        crouseLayout->addSpacing(100);
        crouseLayout->addWidget(crouseedit);

        ElaPushButton* sure = new ElaPushButton("修改", this);
        ElaPushButton* desure = new ElaPushButton("取消", this);
        ElaPushButton* de = new ElaPushButton("删除", this);
        ElaScrollPageArea* buArea = new ElaScrollPageArea(this);
        QHBoxLayout* buLayout = new QHBoxLayout(buArea);
        buLayout->addWidget(sure);
        buLayout->addSpacing(20);
        buLayout->addWidget(de);
        buLayout->addSpacing(20);
        buLayout->addWidget(desure);
        connect(desure,&ElaPushButton::clicked, this, [=]() {
            close();
        });
        connect(de,&ElaPushButton::clicked, this, [=]() {
            m->removeContact(stu);
            if (m->saveToFile("contacts.json")) {
                emit ContactSignalHub::instance()->contactListChanged();
                //emit contactModified();
                qDebug() << "删除成功";
            }
            close();
        });
        connect(sure,&ElaPushButton::clicked, this, [=]() {
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
            //magisk.modifyContact(stu);
            if (m->saveToFile("contacts.json")) {
                emit ContactSignalHub::instance()->contactListChanged();
                //emit contactModified();
                qDebug() << "修改成功";
            }
            close();
        });
        centerLayout->addWidget(crouseArea);
        centerLayout->addWidget(buArea);
        ElaPushButton* copyButton = new ElaPushButton("复制", this);  // 创建复制按钮
        ElaScrollPageArea* copyButtonArea = new ElaScrollPageArea(this);  // 创建按钮区域
        QHBoxLayout* copyButtonLayout = new QHBoxLayout(copyButtonArea);  // 创建布局
        copyButtonLayout->addWidget(copyButton);  // 将按钮添加到布局中
        centerLayout->addWidget(copyButtonArea);
        connect(copyButton, &ElaPushButton::clicked, this, [=]() {
            QString contactInfo;  // 用来存储联系人信息
            contactInfo.append("姓名: " + nameedit->text() + "\n");
            contactInfo.append("QQ: " + qqnumberedit->text() + "\n");
            contactInfo.append("职业: " + jobedit->text() + "\n");
            contactInfo.append("电话: " + phoneedit->text() + "\n");
            contactInfo.append("邮箱: " + emailedit->text() + "\n");
            contactInfo.append("生日: " + _birthday->getSelectedDate().toString("yyyy-MM-dd") + "\n");
            contactInfo.append("备注: " + name2edit->text() + "\n");
            contactInfo.append("关系: " + _relation->currentText() + "\n");
            contactInfo.append("课程: " + crouseedit->text() + "\n");
            contactInfo.append("收藏: " + favo->currentText() + "\n");
            QClipboard *clipboard = QApplication::clipboard();
            clipboard->setText(contactInfo);

            // 可选：显示一条信息提示用户已复制
            qDebug() << "联系人信息已复制到剪贴板！";
        });
        connect(copyButton, &ElaPushButton::clicked, this, [=]() {
            ElaMessageBar::success(ElaMessageBarType::Top, "复制完成", "已被复制到剪贴板", 1000, this);
        });
    } else if(selectedRelation == "普通"){
        auto stu = std::dynamic_pointer_cast<normal_contact>(contactItem);
        ElaPushButton* sure = new ElaPushButton("修改", this);
        ElaPushButton* desure = new ElaPushButton("取消", this);
        ElaPushButton* de = new ElaPushButton("删除", this);
        ElaScrollPageArea* buArea = new ElaScrollPageArea(this);
        QHBoxLayout* buLayout = new QHBoxLayout(buArea);
        buLayout->addWidget(sure);
        buLayout->addSpacing(20);
        buLayout->addWidget(de);
        buLayout->addSpacing(20);
        buLayout->addWidget(desure);
        connect(desure,&ElaPushButton::clicked, this, [=]() {
            close();
        });
        connect(de,&ElaPushButton::clicked, this, [=]() {
            m->removeContact(stu);
            if (m->saveToFile("contacts.json")) {
                emit ContactSignalHub::instance()->contactListChanged();
                //emit contactModified();
                qDebug() << "删除成功";
            }
            close();
        });
        connect(sure,&ElaPushButton::clicked, this, [=]() {
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
            //magisk.modifyContact(stu);
            if (m->saveToFile("contacts.json")) {
                emit ContactSignalHub::instance()->contactListChanged();
                //emit contactModified();
                qDebug() << "修改成功";
            }
            close();
        });

        centerLayout->addWidget(buArea);
        ElaPushButton* copyButton = new ElaPushButton("复制", this);  // 创建复制按钮
        ElaScrollPageArea* copyButtonArea = new ElaScrollPageArea(this);  // 创建按钮区域
        QHBoxLayout* copyButtonLayout = new QHBoxLayout(copyButtonArea);  // 创建布局
        copyButtonLayout->addWidget(copyButton);  // 将按钮添加到布局中
        centerLayout->addWidget(copyButtonArea);
        connect(copyButton, &ElaPushButton::clicked, this, [=]() {
            QString contactInfo;  // 用来存储联系人信息
            contactInfo.append("姓名: " + nameedit->text() + "\n");
            contactInfo.append("QQ: " + qqnumberedit->text() + "\n");
            contactInfo.append("职业: " + jobedit->text() + "\n");
            contactInfo.append("电话: " + phoneedit->text() + "\n");
            contactInfo.append("邮箱: " + emailedit->text() + "\n");
            contactInfo.append("生日: " + _birthday->getSelectedDate().toString("yyyy-MM-dd") + "\n");
            contactInfo.append("备注: " + name2edit->text() + "\n");
            contactInfo.append("关系: " + _relation->currentText() + "\n");
            contactInfo.append("收藏: " + favo->currentText() + "\n");
            QClipboard *clipboard = QApplication::clipboard();
            clipboard->setText(contactInfo);
            qDebug() << "联系人信息已复制到剪贴板！";
        });
        connect(copyButton, &ElaPushButton::clicked, this, [=]() {
            ElaMessageBar::success(ElaMessageBarType::Top, "复制完成", "已被复制到剪贴板", 1000, this);
        });
    }
}
