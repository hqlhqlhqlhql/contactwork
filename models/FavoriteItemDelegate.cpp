#include "FavoriteItemDelegate.h"
#include "contact.h"
#include <QPainter>
#include <QEvent>
#include <QMouseEvent>

#include "ElaTheme.h"

FavoriteItemDelegate::FavoriteItemDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
    _themeMode = eTheme->getThemeMode();
    connect(eTheme, &ElaTheme::themeModeChanged, this, [=](ElaThemeType::ThemeMode themeMode) {
        _themeMode = themeMode;
    });
}

QColor FavoriteItemDelegate::typeToColor(QString& type) const
{
    if(type == "家人") return QColor("#27AE60");
    if(type == "同事") return QColor("#8E44AD");
    if(type == "教师") return QColor("#FF8C00");
    if(type == "学生") return QColor("#2D9CDB");
    return QColor("#0078D4");
}

void FavoriteItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option,
                                const QModelIndex& index) const {
    painter->save();
    // 先让基类绘制（包含背景和选中悬停等效果）
    QStyledItemDelegate::paint(painter, option, index);

    auto contactItem = index.data(Qt::DisplayRole).value<std::shared_ptr<Contact>>();
    QString contactName = contactItem->getName();
    QString contactJob = contactItem->getType();
    bool isFavorite = contactItem->getFavorite();

    QRect rect = option.rect;

    // 开启抗锯齿
    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    // 绘制头像（圆形背景 + 首字母）
    int avatarSize = 50;
    QRect avatarRect(rect.x() + (rect.width() - avatarSize) / 2, rect.y() + 10, avatarSize, avatarSize);
    painter->setBrush(typeToColor(contactJob));
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(avatarRect);

    painter->setPen(Qt::white);
    QFont avatarFont = painter->font();
    avatarFont.setPointSize(20);
    avatarFont.setBold(true);
    painter->setFont(avatarFont);
    painter->drawText(avatarRect, Qt::AlignCenter, contactName.left(1));

    // 绘制姓名
    QFont nameFont = painter->font();
    nameFont.setPointSize(10);
    nameFont.setBold(false);
    painter->setFont(nameFont);
    painter->setPen(ElaThemeColor(_themeMode, BasicText));

    QRect textRect(rect.x() + 5, avatarRect.bottom() + 5, rect.width() - 10, 20);
    painter->drawText(textRect, Qt::AlignHCenter | Qt::AlignTop, painter->fontMetrics().elidedText(contactName, Qt::ElideRight, textRect.width()));

    // // 绘制收藏图标（可选）
    // if (isFavorite) {
    //     QPixmap icon(":/icon/icons/heart_red_filled.png");
    //     QRect iconRect(rect.right() - 22, rect.top() + 5, 16, 16);
    //     painter->drawPixmap(iconRect, icon.scaled(iconRect.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    // }

    painter->restore();
}

QSize FavoriteItemDelegate::sizeHint(const QStyleOptionViewItem&,
                                    const QModelIndex&) const {
    return QSize(100, 120);  // 每个条目宽度和高度
}

// bool FavoriteItemDelegate::editorEvent(QEvent* event, QAbstractItemModel* model,
//     const QStyleOptionViewItem& option, const QModelIndex& index) {
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
