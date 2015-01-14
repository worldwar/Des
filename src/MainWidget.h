#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include <QtWidgets/QWidget>
class QLineEdit;
class QPushButton;
class QLabel;

class MainWidget : public QWidget{
    Q_OBJECT
private:
    QLineEdit * origin;
    QLineEdit * password;
    QLineEdit * result;
    QPushButton * button;
    QPushButton * decryptButton;
	QLabel * display;

public:
    MainWidget();

public:
    void close();
	void recieve(int round, unsigned char * left, unsigned char * right);

protected slots:
	void executeEncrypt();
    void executeDecrypt();
};
#endif // MAINWIDGET_H
