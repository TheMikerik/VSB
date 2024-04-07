#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    display = new QLineEdit(0);

    QGridLayout *layout = new QGridLayout;


    QStringList buttonLabels = {
        "AC", "|", "-", "%",
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


    layout->addWidget(display, 0, 0, 1, 4);

    setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

