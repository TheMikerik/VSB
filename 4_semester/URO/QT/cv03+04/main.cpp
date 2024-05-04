#include <QApplication>
#include <QMainWindow>
#include <QDialog>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableView>
#include <QPushButton>
#include <QStandardItemModel>
#include <QLabel>
#include <QMessageBox>


class FlashcardEditorDialog : public QDialog {
    Q_OBJECT
public:
    explicit FlashcardEditorDialog(QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle("Edit Flashcard");

        tagEdit = new QLineEdit(this);
        frontsideEdit = new QLineEdit(this);
        backsideEdit = new QLineEdit(this);
        statusEdit = new QLineEdit("Not studied", this);

        QFormLayout *formLayout = new QFormLayout;
        formLayout->addRow("Tag:", tagEdit);
        formLayout->addRow("Frontside:", frontsideEdit);
        formLayout->addRow("Backside:", backsideEdit);
        formLayout->addRow("Status:", statusEdit);

        saveButton = new QPushButton("Save", this);
        connect(saveButton, &QPushButton::clicked, this, &FlashcardEditorDialog::saveClicked);

        QVBoxLayout *layout = new QVBoxLayout;
        layout->addLayout(formLayout);
        layout->addWidget(saveButton);

        setLayout(layout);
    }

signals:
    void flashcardSaved(const QString &tag, const QString &frontside, const QString &backside, const QString &status);

private slots:
    void saveClicked() {
        QString tag = tagEdit->text();
        QString frontside = frontsideEdit->text();
        QString backside = backsideEdit->text();
        QString status = statusEdit->text();

        emit flashcardSaved(tag, frontside, backside, status);
        close();
    }

private:

    QLineEdit *tagEdit;
    QLineEdit *frontsideEdit;
    QLineEdit *backsideEdit;
    QLineEdit *statusEdit;

    QPushButton *saveButton;
};

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("Flashcard Manager");


        model = new QStandardItemModel(0, 4, this);
        model->setHorizontalHeaderLabels({"Tag", "Frontside", "Backside", "Status"});


        tableView = new QTableView(this);
        tableView->setModel(model);

        tableView->setColumnWidth(1, 275);
        tableView->setColumnWidth(2, 125);


        flashcardTagEdit = new QLineEdit(this);
        flashcardFrontsideEdit = new QLineEdit(this);
        flashcardBacksideEdit = new QLineEdit(this);
        flashcardStatusEdit = new QLineEdit(this);


        flashcardFormLayout = new QFormLayout;
        flashcardFormLayout->addRow("Tag:", flashcardTagEdit);
        flashcardFormLayout->addRow("Frontside:", flashcardFrontsideEdit);
        flashcardFormLayout->addRow("Backside:", flashcardBacksideEdit);
        flashcardFormLayout->addRow("Status:", flashcardStatusEdit);

        flashcardTagEdit->setMinimumSize(400, 30);
        flashcardFrontsideEdit->setMinimumSize(400, 30);
        flashcardBacksideEdit->setMinimumSize(400, 30);
        flashcardStatusEdit->setMinimumSize(400, 30);

        addButton = new QPushButton("Add Flashcard", this);
        connect(addButton, &QPushButton::clicked, this, &MainWindow::addFlashcard);

        deleteButton = new QPushButton("Delete Flashcard", this);
        connect(deleteButton, &QPushButton::clicked, this, &MainWindow::deleteFlashcard);

        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(tableView);
        layout->addLayout(flashcardFormLayout);
        layout->addWidget(addButton);
        layout->addWidget(deleteButton);

        QWidget *centralWidget = new QWidget(this);
        centralWidget->setLayout(layout);
        setCentralWidget(centralWidget);

        resize(650, 600);

        connect(tableView->selectionModel(), &QItemSelectionModel::currentRowChanged, this, &MainWindow::displayFlashcardDetails);
    }

    void insertFlashcard(const QString &tag, const QString &frontside, const QString &backside, const QString &status) {
        QList<QStandardItem*> newRow;
        newRow << new QStandardItem(tag)
               << new QStandardItem(frontside)
               << new QStandardItem(backside)
               << new QStandardItem(status);
        model->appendRow(newRow);
    }

private slots:
    void addFlashcard() {
        FlashcardEditorDialog dialog(this);
        connect(&dialog, &FlashcardEditorDialog::flashcardSaved, this, &MainWindow::insertFlashcard);
        dialog.exec();
    }

    void deleteFlashcard() {
        if (tableView->selectionModel()->selectedRows().isEmpty()) {
            QMessageBox::information(this, "Information", "No flashcard selected for deletion.");
            return;
        }

        QMessageBox::StandardButton ret_button = QMessageBox::question(this, "Delete?", "Are you sure you want to delete the selected flashcard?");
        if (ret_button == QMessageBox::StandardButton::Yes) {
            foreach (const QModelIndex &index, tableView->selectionModel()->selectedRows()) {
                model->removeRow(index.row());
            }
        } else {
            qInfo("Deletion canceled.");
        }
    }


    void displayFlashcardDetails(const QModelIndex &index) {
        if (index.isValid()) {
            QString tag = model->item(index.row(), 0)->text();
            QString frontside = model->item(index.row(), 1)->text();
            QString backside = model->item(index.row(), 2)->text();
            QString status = model->item(index.row(), 3)->text();

            flashcardTagEdit->setText(tag);
            flashcardFrontsideEdit->setText(frontside);
            flashcardBacksideEdit->setText(backside);
            flashcardStatusEdit->setText(status);
        }
    }

private:
    QStandardItemModel *model; // Model for the table
    QTableView *tableView; // Table view to display flashcards
    QLineEdit *flashcardTagEdit; // QLineEdit for flashcard tag
    QLineEdit *flashcardFrontsideEdit; // QLineEdit for flashcard frontside
    QLineEdit *flashcardBacksideEdit; // QLineEdit for flashcard backside
    QLineEdit *flashcardStatusEdit; // QLineEdit for flashcard status
    QFormLayout *flashcardFormLayout; // Layout for flashcard details
    QPushButton *addButton; // Button to add a new flashcard
    QPushButton *deleteButton; // Button to delete a flashcard
};


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    window.insertFlashcard("Math", "What is 2 + 2?", "4", "Studied");
    window.insertFlashcard("Science", "What is the chemical symbol for water?", "H2O", "Not studied");
    window.insertFlashcard("History", "When did World War II end?", "1945", "Studied");
    window.insertFlashcard("Geography", "What is the capital of France?", "Paris", "Not studied");
    window.insertFlashcard("Literature", "Who wrote Romeo and Juliet?", "William Shakespeare", "Studied");
    window.insertFlashcard("Art", "Who painted the Mona Lisa?", "Leonardo da Vinci", "Not studied");
    window.insertFlashcard("Biology", "What is the powerhouse of the cell?", "Mitochondria", "Studied");
    window.insertFlashcard("Physics", "What is Newton's first law of motion?", "An object in motion stays in motion unless acted upon by an external force.", "Not studied");
    window.insertFlashcard("Chemistry", "What is the pH scale used to measure?", "Acidity or alkalinity", "Studied");
    window.insertFlashcard("Language", "What is the most spoken language in the world?", "Mandarin Chinese", "Not studied");

    return app.exec();
}

#include "main.moc"
