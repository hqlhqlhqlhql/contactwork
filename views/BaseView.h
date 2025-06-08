#ifndef BASEVIEW_H
#define BASEVIEW_H

#include <ElaScrollPage.h>

class QVBoxLayout;
class BaseView : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit BaseView (QWidget* parent = nullptr);
    ~BaseView();

protected:
    void createCustomWidget(QString desText);
};
#endif // BASEVIEW_H
