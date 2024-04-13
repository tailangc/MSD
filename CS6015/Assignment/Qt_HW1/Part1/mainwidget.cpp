#include "mainwidget.h"

mainWidget::mainWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Create and set vertical layout
    setVerticalLayout();

    // Create and set grid layout
    // setGridLayout();

    // Add both layouts to the main layout
    mainLayout->addLayout(verticalLayout1);
    mainLayout->addLayout(verticalLayout2);
    mainLayout->addLayout(verticalLayout3);
    mainLayout->addLayout(gridLayout);

    // Connect Refresh button signal to slot function
    connect(refreshButton, &QPushButton::clicked, this, &mainWidget::clearData);
    connect(finishButton, &QPushButton::clicked, this, &mainWidget::fillSummary);
}

void mainWidget::setVerticalLayout()
{

    // Create vertical layout
    verticalLayout1 = new QGridLayout;
    verticalLayout2 = new QVBoxLayout;
    verticalLayout3 = new QVBoxLayout;


    // Create labels, line edits, spin box, radio buttons, and buttons
    firstNameLabel = new QLabel("First Name:");
    firstNameLineEdit = new QLineEdit;
    lastNameLabel = new QLabel("Last Name:");
    lastNameLineEdit = new QLineEdit;
    ageLabel = new QLabel("Age:");
    ageSpinBox = new QSpinBox;
    // genderGroupBox = new QGroupBox("Gender");
    genderLable = new QLabel("Gender");
    genderLayout = new QVBoxLayout;
    maleRadioButton = new QRadioButton("Male");
    femaleRadioButton = new QRadioButton("Female");
    refreshButton = new QPushButton("Refresh");
    summaryTextEdit = new QTextEdit;
    finishButton = new QPushButton("Finish");

    // // Add radio buttons to the gender group box layout
    genderLayout->addWidget(maleRadioButton);
    genderLayout->addWidget(femaleRadioButton);
    // genderGroupBox->setLayout(genderLayout);

    // Add widgets to the vertical layout
    verticalLayout1->addWidget(firstNameLabel,0,0);
    verticalLayout1->addWidget(firstNameLineEdit,0,1);
    verticalLayout1->addWidget(lastNameLabel,1,0);
    verticalLayout1->addWidget(lastNameLineEdit,1,1);
    verticalLayout1->addWidget(ageLabel,0,2);
    verticalLayout1->addWidget(ageSpinBox,0,3);
    verticalLayout1->addWidget(genderLable,2,0);
    verticalLayout1->addLayout(genderLayout,2,1);
    // verticalLayout1->addWidget(femaleRadioButton,2,1);
    verticalLayout1->addWidget(refreshButton,3,0);
    verticalLayout2->addWidget(summaryTextEdit);
    verticalLayout3->addWidget(finishButton);

}

// void mainWidget::setGridLayout()
// {
//     // Create grid layout
//     gridLayout = new QGridLayout;

//     // Add vertical spacer item
//     gridLayout->addItem(new QSpacerItem(50, 10), 0, 2, 1, 1);

//     // Add widgets to the grid layout
//     // (Assuming some labels and widgets were already added in setVerticalLayout())
//     gridLayout->addWidget(firstNameLabel, 0, 0);
//     gridLayout->addWidget(lastNameLabel, 1, 0);
//     gridLayout->addWidget(ageLabel, 2, 0);
//     gridLayout->addWidget(genderGroupBox, 3, 0);
// }

void mainWidget::fillSummary()
{
    // Retrieve data from widgets and construct summary text
    QString summaryText = "First Name: " + firstNameLineEdit->text() + "\n";
    summaryText += "Last Name: " + lastNameLineEdit->text() + "\n";
    summaryText += "Age: " + QString::number(ageSpinBox->value()) + "\n";
    summaryText += "Gender: ";
    summaryText += maleRadioButton->isChecked() ? "Male" : "Female";

    // Set summary text to QTextEdit
    summaryTextEdit->setText(summaryText);
}

void mainWidget::clearData()
{
    // Clear all data in widgets
    firstNameLineEdit->clear();
    lastNameLineEdit->clear();
    ageSpinBox->clear();
    maleRadioButton->setChecked(false);
    femaleRadioButton->setChecked(false);
    summaryTextEdit->clear();
}


mainWidget::~mainWidget()
{
    // Delete dynamically allocated objects to avoid memory leaks
    delete verticalLayout1;
    delete verticalLayout2;
    delete verticalLayout3;
    delete gridLayout;
    delete firstNameLabel;
    delete firstNameLineEdit;
    delete lastNameLabel;
    delete lastNameLineEdit;
    delete ageLabel;
    delete ageSpinBox;
    // delete genderGroupBox;
    delete genderLayout;
    delete maleRadioButton;
    delete femaleRadioButton;
    delete refreshButton;
    delete summaryTextEdit;
}
