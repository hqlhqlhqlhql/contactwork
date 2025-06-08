#ifndef CONTACTLISTVIEW_H
#define CONTACTLISTVIEW_H

#include<BaseView.h>

#include <QWidget>

class ElaLineEdit;  //前向声明。别处定义
class ElaListView;
class ContactListModel;
class ContactItemDelegate;

class ContactListView : public BaseView
{
    Q_OBJECT
public:
    explicit ContactListView(QWidget* parent = nullptr);
    Q_SLOT void onSearchEditTextEdit(const QString& searchText);
    void updateList();

private:
    ElaLineEdit* searchBar{nullptr};
    ElaListView* contactList{nullptr};
    ContactListModel* contactListModel;
    ContactItemDelegate* contactItemDelegate;
};

#endif // CONTACTLISTVIEW_H
