#include "GroupedContactListModel.h"

GroupedContactListModel::GroupedContactListModel(const QString& type, QObject* parent)
    :ContactListModel(parent) {_type = type;}

void GroupedContactListModel::setManager(ContactManager* manager) {
    m_manager = manager;
    m_manager->loadFromFile("contacts.json");
    qDebug() << "type selected" << _type;
    qDebug() << "setManager " + _type << manager->getGroup(_type).size();
    _rowCount = manager->getGroup(_type).size();
    _pIsSearchMode = false;
    beginResetModel();
    endResetModel();
}

QVariant GroupedContactListModel::data(const QModelIndex& index, int role) const {

    //const auto& contact = m_manager->getAll()[index.row()-1];

    if (role == Qt::DisplayRole) {  //要处理好不同role
        //qDebug() << "role?" << index.row();

        if(!_pIsSearchMode)
        {
            if (!m_manager || !index.isValid()) return QVariant();
            if (index.row() < 0 || index.row() >= rowCount()) return QVariant();
            auto contactData = m_manager->getGroup(_type)[index.row()];
            //return contactItemList;
            return QVariant::fromValue(contactData);
        }
        else
        {
            if (!m_manager || !index.isValid()) return QVariant();
            if (index.row() < 0 || index.row() >= _searchKeyList.size()) return QVariant();
            auto contactData = this->_searchKeyList[index.row()];
            return QVariant::fromValue(contactData);
        }
    }
    return QVariant();  //返回空值
}

void GroupedContactListModel::setSearchKeyList(std::vector<std::shared_ptr<Contact>> list)
{
    beginResetModel();
    this->_searchKeyList = list;
    if (_pIsSearchMode)
    {
        _rowCount = this->getSearchKeyList().size();
    }
    else
    {
        _rowCount = m_manager->getGroup(_type).size();
    }
    endResetModel();
}

std::vector<std::shared_ptr<Contact>> GroupedContactListModel::getSearchKeyList()
{
    return this->_searchKeyList;
}

void GroupedContactListModel::updateView(){
    m_manager->loadFromFile("contacts.json");
    //_rowCount = m_manager->getAll().size();
    _rowCount = _pIsSearchMode ? _searchKeyList.size() : m_manager->getGroup(_type).size();    //记得更新rowcount，因为它被独立存储，需要手动更新
    beginResetModel();
    endResetModel();
}
