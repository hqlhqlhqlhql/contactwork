#include "SettingsPage.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "ElaApplication.h"
#include "ElaComboBox.h"
#include "ElaPushButton.h"
#include "ElaLog.h"
#include "ElaRadioButton.h"
#include "ElaScrollPageArea.h"
#include "ElaText.h"
#include "ElaTheme.h"
#include "ElaToggleSwitch.h"
#include "ElaWindow.h"

SettingsPage::SettingsPage(QWidget* parent)
    : BaseView(parent)
{
    // 预览窗口标题
    ElaWindow* window = dynamic_cast<ElaWindow*>(parent);
    setWindowTitle("Setting");
    // ElaText* themeText = new ElaText("信息展示设置", this);
    // themeText->setWordWrap(false);
    // themeText->setTextPixelSize(18);

    // _pixButton = new ElaPushButton(this);
    // ElaScrollPageArea* pixArea = new ElaScrollPageArea(this);
    // QHBoxLayout* pixLayout = new QHBoxLayout(pixArea);
    // ElaText* pixText = new ElaText("更改头像", this);
    // pixText->setWordWrap(false);
    // pixText->setTextPixelSize(15);
    // pixLayout->addWidget(pixText);
    // pixLayout->addStretch();
    // pixLayout->addWidget(_pixButton);


    ElaText* helperText = new ElaText("应用程序设置", this);
    helperText->setWordWrap(false);
    helperText->setTextPixelSize(18);

    _themeComboBox = new ElaComboBox(this);
    _themeComboBox->addItem("日间模式");
    _themeComboBox->addItem("夜间模式");
    ElaScrollPageArea* themeSwitchArea = new ElaScrollPageArea(this);
    QHBoxLayout* themeSwitchLayout = new QHBoxLayout(themeSwitchArea);
    ElaText* themeSwitchText = new ElaText("主题切换", this);
    themeSwitchText->setWordWrap(false);
    themeSwitchText->setTextPixelSize(15);
    themeSwitchLayout->addWidget(themeSwitchText);
    themeSwitchLayout->addStretch();
    themeSwitchLayout->addWidget(_themeComboBox);
    connect(_themeComboBox, QOverload<int>::of(&ElaComboBox::currentIndexChanged), this, [=](int index) {
        if (index == 0)
        {
            eTheme->setThemeMode(ElaThemeType::Light);
        }
        else
        {
            eTheme->setThemeMode(ElaThemeType::Dark);
        }
    });
    connect(eTheme, &ElaTheme::themeModeChanged, this, [=](ElaThemeType::ThemeMode themeMode) {
        _themeComboBox->blockSignals(true);
        if (themeMode == ElaThemeType::Light)
        {
            _themeComboBox->setCurrentIndex(0);
        }
        else
        {
            _themeComboBox->setCurrentIndex(1);
        }
        _themeComboBox->blockSignals(false);
    });

    _micaSwitchButton = new ElaToggleSwitch(this);
    ElaScrollPageArea* micaSwitchArea = new ElaScrollPageArea(this);
    QHBoxLayout* micaSwitchLayout = new QHBoxLayout(micaSwitchArea);
    ElaText* micaSwitchText = new ElaText("启用云母效果(跨平台,会增大内存开销)", this);
    micaSwitchText->setWordWrap(false);
    micaSwitchText->setTextPixelSize(15);
    micaSwitchLayout->addWidget(micaSwitchText);
    micaSwitchLayout->addStretch();
    micaSwitchLayout->addWidget(_micaSwitchButton);
    connect(_micaSwitchButton, &ElaToggleSwitch::toggled, this, [=](bool checked) {
        eApp->setIsEnableMica(checked);
    });



    _minimumButton = new ElaRadioButton("最小", this);
    _compactButton = new ElaRadioButton("紧凑", this);
    _maximumButton = new ElaRadioButton("最大", this);
    _autoButton = new ElaRadioButton("自动调节", this);
    _autoButton->setChecked(true);
    ElaScrollPageArea* displayModeArea = new ElaScrollPageArea(this);
    QHBoxLayout* displayModeLayout = new QHBoxLayout(displayModeArea);
    ElaText* displayModeText = new ElaText("导航栏模式选择", this);
    displayModeText->setWordWrap(false);
    displayModeText->setTextPixelSize(15);
    displayModeLayout->addWidget(displayModeText);
    displayModeLayout->addStretch();
    displayModeLayout->addWidget(_minimumButton);
    displayModeLayout->addWidget(_compactButton);
    displayModeLayout->addWidget(_maximumButton);
    displayModeLayout->addWidget(_autoButton);
    connect(_minimumButton, &ElaRadioButton::toggled, this, [=](bool checked) {
        if (checked)
        {
            window->setNavigationBarDisplayMode(ElaNavigationType::Minimal);
        }
    });
    connect(_compactButton, &ElaRadioButton::toggled, this, [=](bool checked) {
        if (checked)
        {
            window->setNavigationBarDisplayMode(ElaNavigationType::Compact);
        }
    });
    connect(_maximumButton, &ElaRadioButton::toggled, this, [=](bool checked) {
        if (checked)
        {
            window->setNavigationBarDisplayMode(ElaNavigationType::Maximal);
        }
    });
    connect(_autoButton, &ElaRadioButton::toggled, this, [=](bool checked) {
        if (checked)
        {
            window->setNavigationBarDisplayMode(ElaNavigationType::Auto);
        }
    });

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("Setting");
    QVBoxLayout* centerLayout = new QVBoxLayout(centralWidget);
    centerLayout->addSpacing(30);
    // centerLayout->addWidget(themeText);
    // centerLayout->addSpacing(10);

    centerLayout->addSpacing(15);
    centerLayout->addWidget(helperText);
    centerLayout->addSpacing(10);
    centerLayout->addWidget(themeSwitchArea);
    centerLayout->addWidget(micaSwitchArea);
    centerLayout->addWidget(displayModeArea);
    centerLayout->addStretch();
    centerLayout->setContentsMargins(0, 0, 0, 0);
    addCentralWidget(centralWidget, true, true, 0);
}
