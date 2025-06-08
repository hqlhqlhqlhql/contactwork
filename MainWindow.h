#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
// #include <QSplitter>
#include <QStackedWidget>
#include "ElaWindow.h"

class NavigationPanel;
class ContactListView;
class GroupedContactListView;
class ContactDetailView;
class ContactEditView;
class ContactAddView;
class HomePageView;
class FavoritePageView;
class SettingsPage;


class MainWindow : public ElaWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);

private slots:
    void handleMenuClick(const QString& text); // 处理左侧菜单点击
    void handleImportContacts();
    void handleExportContacts();

private:
    //T_BaseComponents* _baseComponentsPage{nullptr}; //使用了统一初始化语法C++11，默认是空指针（安全）
    NavigationPanel* navigationPanel{nullptr};
    QStackedWidget* mainStack;

    // // 中间各视图
    HomePageView* homePage{nullptr};
    // FavoritePageView* favoritePage{nullptr};
    GroupedContactListView* favoriteListPage{nullptr};
    ContactListView* contactListPage{nullptr};
    GroupedContactListView* familyListPage{nullptr};
    GroupedContactListView* businessListPage{nullptr};
    GroupedContactListView* teacherListPage{nullptr};
    GroupedContactListView* studentListPage{nullptr};
    ContactDetailView* detailPage{nullptr};
    ContactEditView* editPage{nullptr};
    ContactAddView* addPage{nullptr};
    SettingsPage* settingsPage{nullptr};
    QString _viewKey{""};   //注意后面这些键是要被赋值的，是在ElaNavigationNode。
    QString _importKey{""};
    QString _exportKey{""};
    QString _aboutKey{""};

    void initContent();
    void setupPages();

signals:
    void contactUpdated();
};

#endif // MAINWINDOW_H
