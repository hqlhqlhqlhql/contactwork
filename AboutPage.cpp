#include "AboutPage.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QVBoxLayout>

#include "ElaImageCard.h"
#include "ElaText.h"

AboutPage::AboutPage(QWidget* parent)
    : ElaWidget(parent)
{
    setWindowTitle("关于");
    setWindowIcon(QIcon(":/include/Image/user.png"));
    this->setIsFixedSize(true);
    setWindowModality(Qt::ApplicationModal);
    setWindowButtonFlags(ElaAppBarType::CloseButtonHint);

    ElaText* versionText = new ElaText("Contact by No Inspiration-v0.0.1", this);
    QFont versionTextFont = versionText->font();
    versionTextFont.setWeight(QFont::Bold);
    versionText->setFont(versionTextFont);
    versionText->setWordWrap(false);
    versionText->setTextPixelSize(18);

    ElaText* licenseText = new ElaText("GPL授权协议", this);
    licenseText->setWordWrap(false);
    licenseText->setTextPixelSize(14);
    ElaText* supportText = new ElaText("基于Qt 6.8和ElaWidgetTools-LK-2024（MIT授权协议）开发", this);
    supportText->setWordWrap(false);
    supportText->setTextPixelSize(14);
    ElaText* contactText = new ElaText("作者: No Inspiration", this);
    contactText->setWordWrap(false);
    contactText->setTextInteractionFlags(Qt::TextSelectableByMouse);
    contactText->setTextPixelSize(14);
    // ElaText* helperText = new ElaText("用户手册及API文档付费提供\n提供额外的专业技术支持", this);
    // helperText->setWordWrap(false);
    // helperText->setTextPixelSize(14);
    // ElaText* copyrightText = new ElaText("版权所有 © 2024 Liniyous", this);
    // copyrightText->setWordWrap(false);
    // copyrightText->setTextPixelSize(14);

    QVBoxLayout* textLayout = new QVBoxLayout();
    textLayout->setSpacing(15);
    textLayout->addWidget(versionText);
    textLayout->addWidget(licenseText);
    textLayout->addWidget(supportText);
    textLayout->addWidget(contactText);
    // textLayout->addWidget(helperText);
    // textLayout->addWidget(copyrightText);
    textLayout->addStretch();

    QHBoxLayout* contentLayout = new QHBoxLayout();
    contentLayout->addSpacing(70);
    contentLayout->addLayout(textLayout);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 25, 0, 0);
    mainLayout->addLayout(contentLayout);
}

AboutPage::~AboutPage()
{

}
