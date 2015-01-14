#include <string>
#include <QApplication>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "MainWidget.h"
#include "des.h"

using namespace std;
MainWidget::MainWidget() {
    origin = new QLineEdit("1111222233334444");
    password = new QLineEdit("1111000011110000");
    result = new QLineEdit;
    button = new QPushButton("encrypt");
    decryptButton = new QPushButton("decrypt");
    display = new QLabel;
    display->resize(500, 400);

    QVBoxLayout * inputLayout = new QVBoxLayout;
    inputLayout->addWidget(origin);
    inputLayout->addWidget(password);
    inputLayout->addWidget(result);

    QHBoxLayout * buttonLayout = new QHBoxLayout;
//    buttonLayout->addLayout(inputLayout);
    buttonLayout->addWidget(button);
    buttonLayout->addWidget(decryptButton);

    QHBoxLayout * actionLayout = new QHBoxLayout;
    QVBoxLayout * mainLayout = new QVBoxLayout;
    actionLayout->addLayout(inputLayout);
    actionLayout->addLayout(buttonLayout);
    mainLayout->addLayout(actionLayout);
    mainLayout->addWidget(display);
    setLayout(mainLayout);

	connect(button, SIGNAL(clicked()), this, SLOT(executeEncrypt()));
    connect(decryptButton, SIGNAL(clicked()), this, SLOT(executeDecrypt()));
}

void MainWidget::executeEncrypt() {
    QString src = origin->text();
    QString psd = password->text();
    string s = src.toStdString();
    string p = psd.toStdString();
    unsigned char * ps = new unsigned char[17];
    unsigned char * pp = new unsigned char[17];
    unsigned char * d = new unsigned char[17];
    copy(s.begin(), s.end(), ps);
    copy(p.begin(), p.end(), pp);
    ps[16] = '\0';
    pp[16] = '\0';
    Do_DES((unsigned char *)ps, (unsigned char *)pp, d, 'e', this);
    d[16] = '\0';
    result->setText(QString::fromUtf8((char *)d));
}

void MainWidget::executeDecrypt() {
    QString src = origin->text();
    QString psd = password->text();
    string s = src.toStdString();
    string p = psd.toStdString();
    unsigned char * ps = new unsigned char[17];
    unsigned char * pp = new unsigned char[17];
    unsigned char * d = new unsigned char[17];
    copy(s.begin(), s.end(), ps);
    copy(p.begin(), p.end(), pp);
    ps[16] = '\0';
    pp[16] = '\0';
    d[16] = '\0';
    Do_DES(ps, pp, d, 'd', this);
    result->setText(QString::fromUtf8((char *)d));
}

void MainWidget::recieve(int round, unsigned char *left, unsigned char *right) {
    QString leftString, rightString;
    for (int i = 0; i < 32; i++) {
        leftString = QString("%1%2").arg(leftString, QString::number(left[i]));
        rightString = QString("%1%2").arg(rightString, QString::number(right[i]));
    }
    QString line = QString("f%1 -> L:%2  R:%3").arg(QString::number(round + 1), leftString, rightString);
    display->setText(display->text() + "\n" + line);
}
