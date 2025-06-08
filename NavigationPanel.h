// views/NavigationPanel.h
#ifndef NAVIGATIONPANEL_H
#define NAVIGATIONPANEL_H

#include <QWidget>
#include <QTreeWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>

class NavigationPanel : public QWidget
{
    Q_OBJECT
public:
    explicit NavigationPanel(QWidget* parent = nullptr);

signals:
    void menuItemClicked(const QString& id);  // 用于与 MainWindow 通信

private:
    QLabel* avatarLabel;
    QLabel* userNameLabel;
    QLineEdit* searchBox;
    QTreeWidget* menuTree;

    void setupUI();
    void setupMenu();
};

#endif // NAVIGATIONPANEL_H
