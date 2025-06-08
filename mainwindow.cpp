#include "MainWindow.h"
#include "NavigationPanel.h"
#include "views/HomePageView.h"
#include "views/ContactListView.h"
#include "views/GroupedContactListView.h"
#include "views/ContactDetailView.h"
#include "views/ContactEditView.h"
#include "views/ContactAddView.h"
#include "views/FavoritePageView.h"  //别忘了加头文件
#include "SettingsPage.h"
#include <QFileDialog>
#include "ContactManager.h"
#include "ElaMessageBar.h"
#include "AboutPage.h"


#include <QSplitter>
#include <QVBoxLayout>
#include <QDebug>




MainWindow::MainWindow(QWidget* parent)
    : ElaWindow(parent)
{

    initContent();
    setupPages();
    moveToCenter();

}

void MainWindow::initContent() {
    setUserInfoCardPixmap(QPixmap(":/include/Image/user.png"));
    setUserInfoCardTitle("No Inspiration");
    setUserInfoCardSubTitle("123456@gmail.com");
    setWindowTitle("Contact");
    setWindowIcon(QIcon(":/include/Image/user.png"));

    //创建每一页
    //_baseComponentsPage = new T_BaseComponents(this);
    homePage = new HomePageView(this);
    // favoritePage = new FavoritePageView(this);
    contactListPage = new ContactListView(this);
    QStringList name = {"家人","同事","教师","学生", "收藏"};
    familyListPage = new GroupedContactListView(name.at(0), this);
    businessListPage = new GroupedContactListView(name.at(1), this);
    teacherListPage = new GroupedContactListView(name.at(2), this);
    studentListPage = new GroupedContactListView(name.at(3), this);
    favoriteListPage = new GroupedContactListView(name.at(4),this);
    settingsPage = new SettingsPage(this);

    addPageNode("主页",homePage,homePage->getBirthdayCount(),ElaIconType::House);
    addPageNode("收藏",favoriteListPage,ElaIconType::Heart);
    //联系人子菜单
    addExpanderNode("联系人",_viewKey,ElaIconType::CabinetFiling);
    addPageNode("所有联系人",contactListPage,_viewKey,ElaIconType::PeopleLine);
    addPageNode("家人",familyListPage,_viewKey,ElaIconType::PeopleLine);
    addPageNode("老师",teacherListPage,_viewKey,ElaIconType::PeopleLine);
    addPageNode("学生",studentListPage,_viewKey,ElaIconType::PeopleLine);
    addPageNode("同事",businessListPage,_viewKey,ElaIconType::PeopleLine);

    expandNavigationNode(_viewKey);

    addPageNode("设置",settingsPage,ElaIconType::Gear);

    addFooterNode("导入", nullptr, _importKey, 0, ElaIconType::FileImport);
    connect(this, &ElaWindow::navigationNodeClicked, this, [=](ElaNavigationType::NavigationNodeType nodeType, QString nodeKey) {
        if (_importKey == nodeKey){
            handleImportContacts();
        }
    });
    addFooterNode("导出", nullptr, _exportKey, 0, ElaIconType::FileExport);
    // addPageNode("ElaBaseComponents", _baseComponentsPage, ElaIconType::CabinetFiling);
    connect(this, &ElaWindow::navigationNodeClicked, this, [=](ElaNavigationType::NavigationNodeType nodeType, QString nodeKey) {
        if(_exportKey == nodeKey){
            handleExportContacts();
        }
    });
    addFooterNode("关于", nullptr, _aboutKey, 0, ElaIconType::CircleInfo);
    AboutPage* aboutPage = new AboutPage;
    connect(this, &ElaWindow::navigationNodeClicked, this, [=](ElaNavigationType::NavigationNodeType nodeType, QString nodeKey) {
        if(_aboutKey == nodeKey){
            aboutPage->show();
        }
    });
    // connect(this, &ElaWindow::navigationNodeClicked, this, [=](ElaNavigationType::NavigationNodeType nodeType, QString nodeKey) {
    //     if (_aboutKey == nodeKey)
    //     {
    //         _aboutPage->setFixedSize(400, 400);
    //         _aboutPage->moveToCenter();
    //         _aboutPage->show();
    //     }
    // });
    // 中间区域（页面切换）
   // mainStack = new QStackedWidget(this);

    // 使用 QSplitter 左右分栏
    //QSplitter* splitter = new QSplitter(Qt::Horizontal, this);
    // splitter->addWidget(navigationPanel);
    // splitter->addWidget(mainStack);
    // splitter->setStretchFactor(1, 1); // 右边可拉伸

    // QWidget* central = new QWidget(this);
    // QVBoxLayout* layout = new QVBoxLayout(central);
    // layout->setContentsMargins(0, 0, 0, 0);
    // layout->addWidget(splitter);

    //setCentralWidget(central);
}

void MainWindow::setupPages() {


    // 加入堆栈
    // mainStack->addWidget(homePage);         // index 0
    // mainStack->addWidget(addPage);
    // mainStack->addWidget(contactListPage);  // index 1
    // mainStack->addWidget(detailPage);       // index 2
    // mainStack->addWidget(editPage);         // index 3

    // 默认显示首页
    // mainStack->setCurrentWidget(homePage);
}

void MainWindow::handleMenuClick(const QString& text) {

}

void MainWindow::handleImportContacts() {
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "选择要导入的联系人文件",
        "",
        "JSON 文件 (*.json);;所有文件 (*.*)"
        );

    if (!filePath.isEmpty()) {
        qDebug() << "选中的文件路径:" << filePath;

        ContactManager* manager = new ContactManager;
        bool loadtest = manager->loadFromFile("contacts.json", true);
        int countBefore = manager->getAll().size();
        if(loadtest) qDebug() << "载入成功";
        bool success = manager->loadFromFile(filePath, true);
        int countAfter = manager->getAll().size();
        if (success) {
            qDebug() << "导入成功";
            ElaMessageBar::success(ElaMessageBarType::Top,
            "导入成功", "成功导入" + QString::number(countAfter - countBefore) + "个联系人", 1000, this);

        } else {
            qDebug() << "导入失败";
            ElaMessageBar::warning(ElaMessageBarType::Top, "导入失败", "请检查文件格式是否正确", 1000, this);
        }

        success = manager->saveToFile("contacts.json");
        if (success) {
            qDebug() << "保存成功";
            contactListPage->updateList();
        } else {
            qDebug() << "保存失败";
            // TODO: 弹出错误提示框
        }
    }
}

void MainWindow::handleExportContacts() {
    QString defaultPath = QDir::homePath() + "/contact_export.json";

    QString savePath = QFileDialog::getSaveFileName(
        this,
        tr("导出联系人"),
        defaultPath,
        tr("JSON 文件 (*.json)")
        );

    if (savePath.isEmpty())
        return;

    QString sourcePath = "contacts.json";

    if (!QFile::copy(sourcePath, savePath)) {
        qDebug() << "导出失败";
        ElaMessageBar::warning(ElaMessageBarType::Top, "导出失败", "可能是成功的，检查目录是否有同名文件", 1000, this);
    } else {
        qDebug() << "导出成功";
        ElaMessageBar::success(ElaMessageBarType::Top, "导出成功", "JSON文件已复制到目标路径", 1000, this);
    }
}
