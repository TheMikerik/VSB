#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QRegularExpression> // Include QRegularExpression for splitting the expression
#include <QMessageBox> // Include QMessageBox for error handling

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT
    QLineEdit *display;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleButtonClick(const QString &text); // Slot for handling button clicks
    void calculateResult(); // Function to calculate the result

private:
    Ui::MainWindow *ui;

    double evalExpression(const QString &expression); // Function to evaluate the expression
};

#endif // MAINWINDOW_H
