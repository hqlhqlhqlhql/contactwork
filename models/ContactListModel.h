#ifndef CONTACTLISTMODEL_H
#define CONTACTLISTMODEL_H

#include <QAbstractListModel>
#include "ContactManager.h"

#include "stdafx.h" //
class ContactListModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY_CREATE(bool, IsSearchMode)   //宏定义，快速生成相关函数
public:
    explicit ContactListModel(QObject* parent = nullptr);

    void setManager(ContactManager* manager);
    ContactManager* getManager();
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    Contact* getContact(int row) const;

    //搜索有关功能
    void setSearchKeyList(std::vector<std::shared_ptr<Contact>> list);
    std::vector<std::shared_ptr<Contact>> getSearchKeyList();

    void updateView();

protected:
    ContactManager* m_manager = nullptr;
    std::vector<std::shared_ptr<Contact>> _searchKeyList;   //搜索列表
    int _rowCount;    //小心重名
};

#endif // CONTACTLISTMODEL_H
