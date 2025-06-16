#include "HomePageView.h"
#include "ContactManager.h"
#include "ElaText.h"
#include <QLabel>
#include <QDebug>
#include <QVBoxLayout>

#include "ElaLCDNumber.h"
#include "ElaPromotionCard.h"
#include "ElaPromotionView.h"

HomePageView::HomePageView(QWidget* parent)
    : BaseView(parent)
{
    //顶部
    //setWindowTitle("首页");
    //setContentsMargins(2, 2, 0, 0);  //顺时针左上右下

    QString path="contacts.json";
    ContactManager* manager = new ContactManager;
    manager->loadFromFile(path);
    QStringList birthList = manager->HandleBirthday();
    _birthdayCount = birthList.size();
    QString s;
    for(auto existing : birthList){
        s += existing;
        s += ",";
    }
    s.chop(1);  //删掉最后一个逗号
    qDebug() << "生日列表" << s;

    _promotionCard = new ElaPromotionCard(this);
    _promotionCard->setFixedSize(600, 300);
    _promotionCard->setCardPixmap(QPixmap(":/card/icons/birhdayCard.png"));
    _promotionCard->setCardTitle("生日提醒x" + QString::number(_birthdayCount));
    _promotionCard->setPromotionTitle("Happy birthday~");
    _promotionCard->setTitlePixelSize(15);
    _promotionCard->setTitle("别忘了给他们送上诚挚的祝福");
    _promotionCard->setSubTitlePixelSize(22);
    _promotionCard->setSubTitle("今天是" + s + "的生日哦>_<");

    _promotionView = new ElaPromotionView(this);


    //功能展示
    ElaText* funcText = new ElaText("功能展示", this);

    ElaPromotionCard* exampleCard1 = new ElaPromotionCard(this);
    exampleCard1->setCardPixmap(QPixmap(":/card/icons/showBar.png"));
    // exampleCard1->setCardTitleColor(QColorConstants::Black);
    // exampleCard1->setCardTitle("导航栏");
    // //exampleCard1->setPromotionTitle("SONG~");
    // exampleCard1->setTitleColor(QColorConstants::Black);
    // exampleCard1->setSubTitleColor(QColorConstants::Black);
    // exampleCard1->setTitle("点击分组查看联系人");
    // exampleCard1->setSubTitle("各个联系人页面均可以编辑");

    ElaPromotionCard* exampleCard2 = new ElaPromotionCard(this);
    exampleCard2->setCardPixmap(QPixmap(":/card/icons/showContact.png"));
    // exampleCard2->setTitleColor(QColorConstants::Black);
    // exampleCard2->setSubTitleColor(QColorConstants::Black);
    // exampleCard2->setCardTitleColor(QColorConstants::Black);
    // exampleCard2->setCardTitle("联系人列表");
    // //exampleCard2->setPromotionTitle("SONG~");
    // exampleCard2->setTitle("单击卡片可以编辑对应联系人");
    // exampleCard2->setSubTitle("联系人头像的颜色对应不同群组");

    ElaPromotionCard* exampleCard3 = new ElaPromotionCard(this);
    exampleCard3->setCardPixmap(QPixmap(":/card/icons/showEdit.png"));
    // exampleCard3->setTitleColor(QColorConstants::Black);
    // exampleCard3->setSubTitleColor(QColorConstants::Black);
    // exampleCard3->setCardTitleColor(QColorConstants::Black);
    // exampleCard3->setCardTitle("联系人编辑");
    // //exampleCard3->setPromotionTitle("SONG~");
    // exampleCard3->setTitle("修改对应条目后点击修改保存");
    // exampleCard3->setSubTitle("提示：点击复制可以快捷得到联系人信息");


    _promotionView->appendPromotionCard(exampleCard1);
    _promotionView->appendPromotionCard(exampleCard2);
    _promotionView->appendPromotionCard(exampleCard3);
    _promotionView->setIsAutoScroll(true);


    // QVBoxLayout* center = new QVBoxLayout(this);
    // if(!s.isEmpty()){
    //     ElaText* reminder = new ElaText("今天是"+s+"的生日",this);
    //     reminder->setTextPixelSize(15);
    //     center->addWidget(reminder);
    // }

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("首页");
    QVBoxLayout* centerLayout = new QVBoxLayout(centralWidget);
    centerLayout->setContentsMargins(10, 10, 0, 0);
    if(!s.isEmpty()){
        centerLayout->addWidget(_promotionCard);
        centerLayout->addSpacing(20);
    }
    else _promotionCard->hide();
    centerLayout->addWidget(funcText);
    centerLayout->addWidget(_promotionView);
    centerLayout->addSpacing(10);
    centerLayout->addSpacing(100);
    centerLayout->addStretch();
    addCentralWidget(centralWidget, true, true, 0);
}

int HomePageView::getBirthdayCount()
{
    return _birthdayCount;
}
