#ifndef HOMEPAGEVIEW_H
#define HOMEPAGEVIEW_H

#include <QWidget>
#include <BaseView.h>

class ElaLCDNumber;
class ElaPromotionCard;
class ElaPromotionView;
class HomePageView : public BaseView
{
    Q_OBJECT
public:
    explicit HomePageView(QWidget* parent = nullptr);
    int getBirthdayCount();
    ElaLCDNumber* _lcdNumber{nullptr};
    ElaPromotionCard* _promotionCard{nullptr};
    ElaPromotionView* _promotionView{nullptr};
private:
    int _birthdayCount;
};

#endif // HOMEPAGEVIEW_H
