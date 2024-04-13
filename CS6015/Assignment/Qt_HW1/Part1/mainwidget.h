#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QRadioButton>
#include <QPushButton>
#include <QGroupBox>
#include <QTextEdit>
#include <QSpacerItem>

class mainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit mainWidget(QWidget *parent = nullptr);
    ~mainWidget();

private:
    QGridLayout *verticalLayout1;
    QVBoxLayout *verticalLayout2;
    QVBoxLayout *verticalLayout3;
    QGridLayout *gridLayout;

    // Widgets for vertical layout
    QLabel *firstNameLabel;
    QLineEdit *firstNameLineEdit;
    QLabel *lastNameLabel;
    QLineEdit *lastNameLineEdit;
    QLabel *ageLabel;
    QSpinBox *ageSpinBox;
    QLabel *genderLable;
    // QGroupBox *genderGroupBox;
    QVBoxLayout *genderLayout;
    QRadioButton *maleRadioButton;
    QRadioButton *femaleRadioButton;
    QPushButton *refreshButton;
    QTextEdit *summaryTextEdit;
    QPushButton *finishButton;

    void setVerticalLayout();
    void setGridLayout();

private slots:
    void fillSummary();
    void clearData();
};

#endif // MAINWIDGET_H
