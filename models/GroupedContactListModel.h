#ifndef GROUPEDCONTACTLISTMODEL_H
#define GROUPEDCONTACTLISTMODEL_H

#include "ContactListModel.h"
#include <QString>

class GroupedContactListModel : public ContactListModel {
    Q_OBJECT
    Q_PROPERTY_CREATE(bool, IsSearchMode)
public:
    explicit GroupedContactListModel(const QString& type, QObject* parent = nullptr);
    void setManager(ContactManager* manager);
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    //搜索有关功能
    void setSearchKeyList(std::vector<std::shared_ptr<Contact>> list);
    std::vector<std::shared_ptr<Contact>> getSearchKeyList();
    void updateView();

private:
    std::vector<std::shared_ptr<Contact>> groupedList;
    QString _type;
};

#endif // GROUPEDCONTACTLISTMODEL_H
