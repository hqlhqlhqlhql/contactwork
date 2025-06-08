#ifndef CONTACTEDITVIEW_H
#define CONTACTEDITVIEW_H

#include "ElaWidget.h"
#include "ElaComboBox.h"
#include "ElaCalendarPicker.h"
#include "ContactManager.h"

class ContactEditView : public ElaWidget
{
    Q_OBJECT
public:
    explicit ContactEditView(ContactManager* magisk,const QModelIndex & index,QWidget* parent = nullptr);
private:
    ElaCalendarPicker* _birthday{nullptr};
    ElaComboBox* _relation{nullptr};
    QModelIndex _index;
    ElaComboBox* favo{nullptr};
    ContactManager* m;
signals:
    void contactModified();
};

#endif // CONTACTEDITVIEW_H
