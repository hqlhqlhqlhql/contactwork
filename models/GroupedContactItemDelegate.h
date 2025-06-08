#ifndef GROUPEDCONTACTITEMDELEGATE_H
#define GROUPEDCONTACTITEMDELEGATE_H

#include <QStyledItemDelegate>

#include "Def.h"
class GroupedContactItemDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit GroupedContactItemDelegate(QObject* parent = nullptr);
    QColor typeToColor(QString& type) const;
    void paint(QPainter* painter, const QStyleOptionViewItem& option,
               const QModelIndex& index) const override;
    QSize sizeHint(const QStyleOptionViewItem& option,
                   const QModelIndex& index) const override;
    // bool editorEvent(QEvent *event,QAbstractItemModel *model,const QStyleOptionViewItem &option,
    //                  const QModelIndex &index);

private:
    ElaThemeType::ThemeMode _themeMode;

// signals:
//     void favoriteToggled(const QModelIndex& index);
};

#endif // GROUPEDCONTACTITEMDELEGATE_H
