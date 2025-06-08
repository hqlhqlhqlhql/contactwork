#include "ContactListView.h"
#include "ContactEditView.h"
#include <QLabel>
#include <ElaText.h>
#include "ContactManager.h"
#include "ElaLineEdit.h"
#include "ElaPushButton.h"
#include "ElaListView.h"
#include "ContactListModel.h"
#include "ContactItemDelegate.h"
#include "ContactAddView.h"
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "contact.h"
#include "ContactSignalHub.h"

ContactListView::ContactListView(QWidget* parent)
    : BaseView(parent)
{
    setWindowTitle("联系人列表");
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("所有联系人");
    QVBoxLayout* centerLayout = new QVBoxLayout(centralWidget);
    QHBoxLayout* topLayout = new QHBoxLayout();

    //搜索栏
    searchBar = new ElaLineEdit(this);
    searchBar->setPlaceholderText("搜索联系人");
    searchBar->setFixedSize(300,35);
    connect(searchBar, &ElaLineEdit::textEdited, this, &ContactListView::onSearchEditTextEdit);
    connect(searchBar, &ElaLineEdit::focusIn, this, &ContactListView::onSearchEditTextEdit);

    //添加按钮
    ElaPushButton* addButton = new ElaPushButton(this);
    addButton->setText("添加联系人");
    addButton->setFixedSize(100,40);
    // connect(addButton,&ElaPushButton::clicked,this,[=]() {
    //     ContactAddView* p = new ContactAddView();
    //     p->show();
    // });

    connect(ContactSignalHub::instance(), &ContactSignalHub::contactListChanged, this, [=]() {
        contactListModel->updateView();  // 重新给模型填充联系人
    });

    connect(addButton,&ElaPushButton::clicked,this,[=]() {
        ContactAddView* p = new ContactAddView();
        p->setAttribute(Qt::WA_DeleteOnClose);  //关闭时自动 delete，注意，直接delete会crash。
        p->show();
        // connect(p, &ContactAddView::contactAdded, this, [=]() {
        //     contactListModel->updateView();  // 重新给模型填充联系人
        // });
        // connect(ContactSignalHub::instance(), &ContactSignalHub::contactListChanged,
        //         this, &GroupedContactView::updateView);
    });

    //delete p;

    //加入到上部分布局
    topLayout->addWidget(searchBar);
    topLayout->addSpacing(10);
    topLayout->addWidget(addButton);

    //联系人列表
    contactList = new ElaListView(this);
    contactList->setIsTransparent(true);
    //contactList->setFlow(QListView::LeftToRight);   //MVC 模式（Model-View-Delegate）
    contactList->setViewMode(QListView::ListMode);
    contactList->setResizeMode(QListView::Adjust);
    contactListModel = new ContactListModel(this);
    contactItemDelegate = new ContactItemDelegate(this);
    ContactManager* manager = new ContactManager;
    contactListModel->setManager(manager);
    // contactListModel->setIsSearchMode(false);
    contactList->setModel(contactListModel);
    contactList->setItemDelegate(contactItemDelegate);
    contactList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    centerLayout->addLayout(topLayout);
    centerLayout->addWidget(contactList);
    //只要确保 centralWidget 的 parent 是 ContactListView 或其某个 child，Qt 会自动释放
    addCentralWidget(centralWidget, true, true, 0);
    // layout->addWidget(new QLabel("这是联系人列表页"));

    connect(contactList,&ElaListView::clicked, this, [=](const QModelIndex& index) {    //响应点击编辑
        QPoint globalPos = QCursor::pos();  // 获取全局鼠标位置
        QPoint viewPos = contactList->viewport()->mapFromGlobal(globalPos);  // 转为 view 内部坐标
        QRect rect = contactList->visualRect(index);
        QRect favoriteRect = QRect(rect.right() - 45, rect.top() + 20, 20, 20);
        if(favoriteRect.contains(viewPos)) {
            auto var = index.data(Qt::DisplayRole);
            auto contactItem = var.value<std::shared_ptr<Contact>>();
            // ContactManager* manager = contactListModel->getManager();
            // auto contact = manager->getAll().at(index.row());
            //contact->setFavorite(!contact->getFavorite());
            contactItem->setFavorite(!contactItem->getFavorite());
            manager->saveToFile("contacts.json");
            emit ContactSignalHub::instance()->contactListChanged();
            return;
        }
        contactList->clearSelection();
        ContactEditView* p = new ContactEditView(manager,index);
        p->setAttribute(Qt::WA_DeleteOnClose);  //关闭时自动 delete，注意，直接delete会crash。
        p->show();
        // connect(p, &ContactEditView::contactModified, this, [=]() {
        //     qDebug() << "修改已更新";
        //     contactListModel->updateView();  // 重新给模型填充联系人
        // });
    });

    // connect(contactItemDelegate, &ContactItemDelegate::favoriteToggled, this, [=](const QModelIndex& index) {   //响应点击收藏
    //     // 获取联系人对象
    //     // auto contact = index.data(Qt::DisplayRole).value<std::shared_ptr<Contact>>();
    //     // if (contact) {
    //     //     contact->setFavorite(!contact->getFavorite()); // 切换收藏状态
    //     //     emit contactListModel->dataChanged(index, index); // 通知视图更新
    //     // }
    //     auto var = index.data(Qt::DisplayRole);
    //     auto contactItem = var.value<std::shared_ptr<Contact>>();
    //     // ContactManager* manager = contactListModel->getManager();
    //     // auto contact = manager->getAll().at(index.row());
    //     //contact->setFavorite(!contact->getFavorite());
    //     contactItem->setFavorite(!contactItem->getFavorite());
    //     manager->saveToFile("contacts.json");
    //     //emit contactListModel->dataChanged(index, index); // 通知视图更新
    //     // connect(ContactSignalHub::instance(), &ContactSignalHub::contactListChanged, this, [=]() {
    //     //     contactListModel->updateView();  // 重新给模型填充联系人
    //     // });
    //     //emit ContactSignalHub::instance()->contactListChanged();
    // });

}

void ContactListView::onSearchEditTextEdit(const QString& searchText)
{
    if (searchText.isEmpty())
    {
        contactListModel->setIsSearchMode(false);
        contactListModel->setSearchKeyList(std::vector<std::shared_ptr<Contact>>());
        contactList->clearSelection();
        contactList->viewport()->update();
        return;
    }
    // std::vector<std::shared_ptr<Contact>> searchContacts;
    // ContactManager* manager = new ContactManager;
    // manager->loadFromFile("contacts.json");
    auto manager = contactListModel->getManager();  //防止内存泄漏
    contactListModel->setIsSearchMode(true);
    contactListModel->setSearchKeyList(manager->search(searchText));
    contactList->clearSelection();
    contactList->scrollTo(contactListModel->index(0));

}

void ContactListView::updateList()
{
    contactListModel->updateView();
}
