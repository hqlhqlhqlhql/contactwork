#include "ContactListModel.h"
#include <QDebug>

ContactListModel::ContactListModel(QObject* parent)
    : QAbstractListModel(parent) {}


void ContactListModel::setManager(ContactManager* manager) {
    m_manager = manager;
    m_manager->loadFromFile("contacts.json");
    qDebug() << "setManager" << manager->getAll().size();
    _rowCount = manager->getAll().size();
    _pIsSearchMode = false;
    beginResetModel();
    endResetModel();
}

ContactManager* ContactListModel::getManager() {
    return m_manager;
}

int ContactListModel::rowCount(const QModelIndex&) const {
    //qDebug() << (m_manager ? (m_manager->getAll().size()) : 0);
    //return m_manager ? (m_manager->getAll().size()) : 0;
    return _rowCount;
}

QVariant ContactListModel::data(const QModelIndex& index, int role) const {

    //const auto& contact = m_manager->getAll()[index.row()-1];

    if (role == Qt::DisplayRole) {  //要处理好不同role
        //qDebug() << "role?" << index.row();

        if(!_pIsSearchMode)
        {
            if (!m_manager || !index.isValid()) return QVariant();
            if (index.row() < 0 || index.row() >= rowCount()) return QVariant();
            auto contactData = m_manager->getAll()[index.row()];
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

Contact* ContactListModel::getContact(int row) const {
    if (!m_manager || row >= int(m_manager->getAll().size())) return nullptr;
    return m_manager->getAll()[row].get();
}

void ContactListModel::setSearchKeyList(std::vector<std::shared_ptr<Contact>> list)
{
    beginResetModel();
    this->_searchKeyList = list;
    if (_pIsSearchMode)
    {
        _rowCount = this->getSearchKeyList().size();
    }
    else
    {
        _rowCount = m_manager->getAll().size();
    }
    endResetModel();
}

std::vector<std::shared_ptr<Contact>> ContactListModel::getSearchKeyList()
{
    return this->_searchKeyList;
}

void ContactListModel::updateView(){
    m_manager->loadFromFile("contacts.json");
    //_rowCount = m_manager->getAll().size();
    _rowCount = _pIsSearchMode ? _searchKeyList.size() : m_manager->getAll().size();    //记得更新rowcount，因为它被独立存储，需要手动更新
    beginResetModel();
    endResetModel();
}
