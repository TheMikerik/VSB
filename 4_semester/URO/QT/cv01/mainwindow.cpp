#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox> // Include QMessageBox for error handling

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    display = new QLineEdit("0");

    QGridLayout *layout = new QGridLayout;
    layout->setHorizontalSpacing(2);
    layout->setVerticalSpacing(14);

    QStringList buttonLabels = {
        "AC", "/", "-", "%",
        "7", "8", "9", "x",
        "4", "5", "6", "-",
        "1", "2", "3", "+",
        "0", ".", "="
    };

    QPushButton *buttons[19];

    int index = 0;
    for(int row = 1; row < 6; ++row){
        for(int col = 0; col < 4; ++col){
            if(row == 5 && col == 0){
                buttons[index] = new QPushButton(buttonLabels[index]);
                layout->addWidget(buttons[index], row, col, 1, 2);
                index++;
                col++;
            }
            else {
                buttons[index] = new QPushButton(buttonLabels[index]);
                layout->addWidget(buttons[index], row, col);
                index++;
            }
        }
    }

    QString buttonStyle = "QPushButton {"
                          "font-size: 20px;"
                          "min-width: 60px;"
                          "min-height: 60px;"
        ;

    for (int i = 0; i < 19; ++i) {
        if( i < 3 ){
            QString additionStyle = "background-color: gray;"
                                    "}";
            buttons[i]->setStyleSheet(buttonStyle + additionStyle);
        } else {
            if( i % 4 == 3 ){
                QString additionStyle = "background-color: orange;"
                                        "}";
                buttons[i]->setStyleSheet(buttonStyle + additionStyle);
            } else {
                QString additionStyle = "background-color: darkgray;"
                                        "}";
                buttons[i]->setStyleSheet(buttonStyle + additionStyle);
            }
        }
    }

    layout->addWidget(display, 0, 0, 1, 4);

    setLayout(layout);

    // Connect buttons to slots
    for (int i = 0; i < 19; ++i) {
        connect(buttons[i], &QPushButton::clicked, this, [=]() {
            handleButtonClick(buttons[i]->text());
        });
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButtonClick(const QString &text)
{
    if (text == "AC") {
        display->setText("0");
    } else if (text == "=") {
        calculateResult();
    } else {
        QString currentText = display->text();
        if (currentText == "0") {
            display->setText(text);
        } else {
            display->setText(currentText + text);
        }
    }
}

void MainWindow::calculateResult()
{
    QString expression = display->text();

    try {
        double result = evalExpression(expression);
        display->setText(QString::number(result));
    } catch (std::exception &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

double MainWindow::evalExpression(const QString &expression)
{
    QStringList operatorList;
    QString currentOperator;
    for (const QChar &ch : expression) {
        if (ch.isDigit() || ch == '.') {
            currentOperator += ch;
        } else if (ch == '+' || ch == '-' || ch == 'x' || ch == '/') {
            if (!currentOperator.isEmpty()) {
                operatorList << currentOperator;
                currentOperator.clear();
            }
            operatorList << ch;
        }
    }
    if (!currentOperator.isEmpty()) {
        operatorList << currentOperator;
    }

    qDebug() << "Expression operatorList:";
    for (const QString &singleOperator : operatorList) {
        qDebug() << singleOperator;
    }

    if (operatorList.size() % 2 == 0) {
        throw std::runtime_error("Invalid expression");
    }

    double result = operatorList[0].toDouble();
    for (int i = 1; i < operatorList.size(); i += 2) {
        QString op = operatorList[i];
        double operand = operatorList[i + 1].toDouble();
        if (op == "+") {
            result += operand;
        } else if (op == "-") {
            result -= operand;
        } else if (op == "x") {
            result *= operand;
        } else if (op == "/") {
            if (operand == 0) {
                throw std::runtime_error("Division by zero");
            }
            result /= operand;
        } else {
            throw std::runtime_error("Invalid operator");
        }
    }

    return result;
}



