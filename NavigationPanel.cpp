// views/NavigationPanel.cpp
#include "NavigationPanel.h"

NavigationPanel::NavigationPanel(QWidget* parent)
    : QWidget(parent)
{
    setupUI();
    setupMenu();
}

void NavigationPanel::setupUI() {
    avatarLabel = new QLabel("头像");
    userNameLabel = new QLabel("用户名");
    searchBox = new QLineEdit();
    searchBox->setPlaceholderText("搜索联系人...");
    menuTree = new QTreeWidget();
    menuTree->setHeaderHidden(true);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(avatarLabel);
    layout->addWidget(userNameLabel);
    layout->addWidget(searchBox);
    layout->addWidget(menuTree);
    layout->addStretch();
    setLayout(layout);
}

void NavigationPanel::setupMenu() {
    QTreeWidgetItem* homeItem = new QTreeWidgetItem(QStringList("主页"));
    QTreeWidgetItem* addItem = new QTreeWidgetItem(QStringList("新建联系人"));
    QTreeWidgetItem* importItem = new QTreeWidgetItem(QStringList("导入联系人"));
    QTreeWidgetItem* exportItem = new QTreeWidgetItem(QStringList("导出联系人"));
    QTreeWidgetItem* favoriteItem = new QTreeWidgetItem(QStringList("收藏"));

    QTreeWidgetItem* contactsRoot = new QTreeWidgetItem(QStringList("联系人"));
    contactsRoot->addChild(new QTreeWidgetItem(QStringList("普通")));
    contactsRoot->addChild(new QTreeWidgetItem(QStringList("老师")));
    contactsRoot->addChild(new QTreeWidgetItem(QStringList("学生")));
    contactsRoot->addChild(new QTreeWidgetItem(QStringList("同事")));
    contactsRoot->addChild(new QTreeWidgetItem(QStringList("家人")));

    menuTree->addTopLevelItem(homeItem);
    menuTree->addTopLevelItem(addItem);
    menuTree->addTopLevelItem(importItem);
    menuTree->addTopLevelItem(exportItem);
    menuTree->addTopLevelItem(favoriteItem);
    menuTree->addTopLevelItem(contactsRoot);

    connect(menuTree, &QTreeWidget::itemClicked, this, [=](QTreeWidgetItem* item, int){
        emit menuItemClicked(item->text(0));
    });
}
