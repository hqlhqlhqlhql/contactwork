#include "GroupedContactItemDelegate.h"

#include "contact.h"
#include <QPainter>
#include <QEvent>
#include <QMouseEvent>

#include "ElaTheme.h"

GroupedContactItemDelegate::GroupedContactItemDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
    _themeMode = eTheme->getThemeMode();
    connect(eTheme, &ElaTheme::themeModeChanged, this, [=](ElaThemeType::ThemeMode themeMode) {
        _themeMode = themeMode;
    });
}

QColor GroupedContactItemDelegate::typeToColor(QString& type) const
{
    if(type == "家人") return QColor("#27AE60");
    if(type == "同事") return QColor("#8E44AD");
    if(type == "教师") return QColor("#FF8C00");
    if(type == "学生") return QColor("#2D9CDB");
    return QColor("#0078D4");
}

void GroupedContactItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option,
                                const QModelIndex& index) const {
    //painter->save();

    // 先让基类绘制（包含背景和选中悬停等效果）
    QStyledItemDelegate::paint(painter, option, index);

    //QRect rect = option.rect;
    // QStringList contactItemList = index.data(Qt::DisplayRole).toStringList();
    auto var = index.data(Qt::DisplayRole);
    auto contactItem = var.value<std::shared_ptr<Contact>>();
    // auto contactItem = index.data(Qt::DisplayRole).value(std::shared_ptr<Contact>>)();

    // QString contactName = contactItemList.at(0);
    // QString contactPhone = contactItemList.at(1);
    // QString contactDescription = contactItemList.at(2);
    // QString contactJob = contactItemList.at(3);
    // QString contactQQnumber = contactItemList.at(4);
    // QString contactFavorite = contactItemList.at(5);

    QString contactName = contactItem->getName();
    QString contactPhone = contactItem->getPhone();
    QString contactDescription = contactItem->getDescription();
    QString contactJob = contactItem->getType();
    QString contactQQnumber = contactItem->getQQnumber();
    bool contactFavorite = contactItem->getFavorite();
    painter->save();

    // 卡片背景
    QRect rect = option.rect.adjusted(4, 4, -4, -4);    //x,y,w,h
    painter->setRenderHint(QPainter::Antialiasing);    //反走样（图形学概念），去锯齿
    painter->setBrush(ElaThemeColor(_themeMode,BasicBaseAlpha));
    painter->setPen(ElaThemeColor(_themeMode, BasicBorder));
    painter->drawRoundedRect(rect, 7, 7);

    // // ==== 头像区域 ====
    // int avatarSize = 43;
    // QRect avatarRect(rect.left() + 12, rect.top() + (rect.height() - avatarSize) / 2, avatarSize, avatarSize);
    // QPixmap avatar(":/include/Image/user.png");
    // //QPixmap scaledAvatar = avatar.scaled(avatarRect.size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    // painter->drawPixmap(avatarRect, avatar);

    //新头像区域
    // 绘制头像圆形背景
    QString firstChar = contactName.left(1);
    int avatarSize = 43;
    QRect avatarRect(rect.left() + 12, rect.top() + (rect.height() - avatarSize) / 2, avatarSize, avatarSize);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(typeToColor(contactJob)); // 注意const成员函数不能调用非const函数
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(avatarRect);

    // 绘制头像首字母文字
    painter->setPen(Qt::white);
    QFont font = painter->font();
    font.setPointSize(16);
    font.setBold(true);
    painter->setFont(font);
    painter->drawText(avatarRect, Qt::AlignCenter, firstChar);

    // 姓名（加粗）
    //QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(12);
    painter->setFont(font);
    painter->setPen(ElaThemeColor(_themeMode, BasicText));
    painter->drawText(rect.adjusted(76, 12, -16, -12), contactName);
    painter->setFont(painter->font());


    // 电话（普通字体）
    font.setPointSize(10);
    font.setBold(false);
    painter->setFont(font);

    QRect subRect = rect.adjusted(76, 32, -16, -12);
    painter->drawText(subRect, contactPhone);
    painter->drawText(subRect.adjusted(90, 0, 0, 0), contactJob); //在subRect基础上右移，(疑惑translated是什么？)

    //收藏状态爱心图标

    QPixmap icon = contactFavorite ? QPixmap(":/icon/icons/heart_red_filled.png") : QPixmap(":/icon/icons/heart_red_regular.png");  //注意qrc文件要以:/开头
    QRect iconRect = QRect(rect.right() - 45, rect.top() + 20, 20, 20);
    QPixmap scaledIcon = icon.scaled(iconRect.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);   //据说可以按比例裁剪，更加平滑
    //painter->drawPixmap(iconRect.topLeft(), icon);
    painter->drawPixmap(iconRect, icon);

    //painter->restore();
    //painter->drawText(option.rect.x() + option.rect.width() / 2 - 11, option.rect.y() + option.rect.height() / 2 - 11, contactName);
    // //QString name = index.data(Qt::DisplayRole).toString().at(0);

    // painter->setRenderHint(QPainter::Antialiasing);
    // painter->drawText(rect.adjusted(10, 5, -10, -5), name);

    painter->restore();
}

QSize GroupedContactItemDelegate::sizeHint(const QStyleOptionViewItem&,
                                    const QModelIndex&) const {
    return QSize(200, 70);  // 每个条目宽度和高度
}

// bool GroupedContactItemDelegate::editorEvent(QEvent* event, QAbstractItemModel* model,
//                                       const QStyleOptionViewItem& option, const QModelIndex& index) {
//     if(event->type() == QEvent::MouseButtonRelease) {
//         auto* mouseEvent = dynamic_cast<QMouseEvent*>(event);
//         if (!mouseEvent)
//             return false;

//         // 计算图标所在的矩形（要和 paint 中一致）
//         QRect rect = option.rect.adjusted(4, 4, -4, -4);
//         QRect iconRect = QRect(rect.right() - 45, rect.top() + 20, 20, 20);

//         if (iconRect.contains(mouseEvent->pos())) {
//             emit favoriteToggled(index);  // 发出信号
//             return true;  // 表示事件已处理
//         }
//     }
//     return false;
// }
