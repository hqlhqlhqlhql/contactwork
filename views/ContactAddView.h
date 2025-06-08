#ifndef CONTACTADDVIEW_H
#define CONTACTADDVIEW_H

#include <QWidget>
#include "ElaWidget.h"
class ElaComboBox;
class ElaCalendarPicker;

class ContactAddView : public ElaWidget
{
    Q_OBJECT
public:
    explicit ContactAddView(QWidget* parent = nullptr);
private:
    ElaComboBox* _relation{nullptr};
    ElaComboBox* favo{nullptr};
    ElaCalendarPicker* _birthday{nullptr};

signals:
    void contactAdded();
};

#endif // CONTACTADDVIEW_H
// #ifndef CONTACTEDITVIEW_H
// #define CONTACTEDITVIEW_H

// #include <QWidget>

// class ContactEditView : public QWidget
// {
//     Q_OBJECT
// public:
//     explicit ContactEditView(QWidget* parent = nullptr);
// };

// #endif // CONTACTEDITVIEW_H
