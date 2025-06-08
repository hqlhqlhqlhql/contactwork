#ifndef GROUPEDCONTACTLISTVIEW_H
#define GROUPEDCONTACTLISTVIEW_H

#include<BaseView.h>

#include <QWidget>

class ElaLineEdit;  //前向声明。别处定义
class ElaListView;
class GroupedContactListModel;
class GroupedContactItemDelegate;
class FavoriteItemDelegate;

class GroupedContactListView : public BaseView
{
    Q_OBJECT
public:
    explicit GroupedContactListView(const QString& type, QWidget* parent = nullptr);
    Q_SLOT void onSearchEditTextEdit(const QString& searchText);
    void updateList();
private:
    ElaLineEdit* searchBar{nullptr};
    ElaListView* contactList{nullptr};
    GroupedContactListModel* contactListModel;
    GroupedContactItemDelegate* contactItemDelegate;
    FavoriteItemDelegate* favoriteItemDelegate;
    QString _type;
};

#endif // GROUPEDCONTACTLISTVIEW_H
