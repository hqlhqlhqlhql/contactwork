#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include "BaseView.h"
class ElaLineEdit;
class ElaPushButton;
class ElaRadioButton;
class ElaToggleSwitch;
class ElaComboBox;

class SettingsPage : public BaseView
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit SettingsPage(QWidget* parent = nullptr);
private:
    ElaPushButton* _pixButton{nullptr};
    ElaPushButton* _nameButton{nullptr};
    ElaPushButton* _infoButton{nullptr};
    ElaLineEdit* _nameEdit{nullptr};
    ElaLineEdit* _infoEdit{nullptr};
    ElaComboBox* _themeComboBox{nullptr};
    ElaToggleSwitch* _micaSwitchButton{nullptr};
    ElaRadioButton* _minimumButton{nullptr};
    ElaRadioButton* _compactButton{nullptr};
    ElaRadioButton* _maximumButton{nullptr};
    ElaRadioButton* _autoButton{nullptr};
};

#endif // SETTINGSPAGE_H
