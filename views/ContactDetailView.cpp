#include "ContactDetailView.h"
#include <QLabel>
#include <QVBoxLayout>

ContactDetailView::ContactDetailView(QWidget* parent)
    : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("这是联系人详情页"));
    setLayout(layout);
}
