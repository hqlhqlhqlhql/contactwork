#ifndef ABOUTPAGE_H
#define ABOUTPAGE_H

#include <ElaWidget.h>

class AboutPage : public ElaWidget
{
    Q_OBJECT
public:
    explicit AboutPage(QWidget* parent = nullptr);
    ~AboutPage();
};

#endif // ABOUTPAGE_H
