#ifndef MAINWIDGET_H
#define MAINWIDGET_H


#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QTextEdit>
#include <QGroupBox>
#include <QRadioButton>
#include <QPushButton>
#include <QFileDialog>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include "parse.h"
#include "Env.h"
#include "Val.h"
#include "Expr.h"

class mainWidget : public QWidget
{
    Q_OBJECT
    QGridLayout* mainLayout;

    QLabel* expressionLabel;
    QTextEdit* expressionEdit;
    QGroupBox* modeGroup;
    QVBoxLayout* modeLayout;
    QPushButton* fileB;
    QRadioButton* interpB;
    QRadioButton* prettyPrintB;
    QPushButton* submitB;

    QLabel* resultLabel;
    QTextEdit* resultEdit;
    QPushButton* resetB;

public:
    explicit mainWidget(QWidget *parent = nullptr);
    void parse();
    void reset();
    void loadFile();
signals:

};


#endif // MAINWIDGET_H
