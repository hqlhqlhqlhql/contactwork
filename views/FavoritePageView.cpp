#include "FavoritePageView.h"
#include <QLabel>
#include <QVBoxLayout>

FavoritePageView::FavoritePageView(QWidget* parent)
    : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("这是收藏页面"));
    setLayout(layout);
}
