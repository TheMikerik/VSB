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

class FlashcardEditorDialog : public QDialog {
    Q_OBJECT
public:
    explicit FlashcardEditorDialog(QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle("Edit Flashcard");

        // Create input fields
        tagEdit = new QLineEdit(this);
        frontsideEdit = new QLineEdit(this);
        backsideEdit = new QLineEdit(this);
        statusEdit = new QLineEdit("Not studied", this); // Default status

        // Layout for the input fields
        QFormLayout *formLayout = new QFormLayout;
        formLayout->addRow("Tag:", tagEdit);
        formLayout->addRow("Frontside:", frontsideEdit);
        formLayout->addRow("Backside:", backsideEdit);
        formLayout->addRow("Status:", statusEdit);

        // Button to save changes
        saveButton = new QPushButton("Save", this);
        connect(saveButton, &QPushButton::clicked, this, &FlashcardEditorDialog::saveClicked);

        // Main layout
        QVBoxLayout *layout = new QVBoxLayout;
        layout->addLayout(formLayout);
        layout->addWidget(saveButton);

        setLayout(layout);
    }

signals:
    // Signal emitted when a flashcard is saved
    void flashcardSaved(const QString &tag, const QString &frontside, const QString &backside, const QString &status);

private slots:
    void saveClicked() {
        // Retrieve input values
        QString tag = tagEdit->text();
        QString frontside = frontsideEdit->text();
        QString backside = backsideEdit->text();
        QString status = statusEdit->text();

        // Emit signal with input values
        emit flashcardSaved(tag, frontside, backside, status);
        close(); // Close the dialog
    }

private:
    // Input fields
    QLineEdit *tagEdit;
    QLineEdit *frontsideEdit;
    QLineEdit *backsideEdit;
    QLineEdit *statusEdit;

    QPushButton *saveButton; // Button to save changes
};

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("Flashcard Manager");

        // Create a table model with four columns
        model = new QStandardItemModel(0, 4, this);
        model->setHorizontalHeaderLabels({"Tag", "Frontside", "Backside", "Status"});

        // Table view to display flashcards
        tableView = new QTableView(this);
        tableView->setModel(model);

        tableView->setColumnWidth(1, 275);
        tableView->setColumnWidth(2, 125);

        // Form to display flashcard details
        flashcardTagEdit = new QLineEdit(this);
        flashcardFrontsideEdit = new QLineEdit(this);
        flashcardBacksideEdit = new QLineEdit(this);
        flashcardStatusEdit = new QLineEdit(this);

        // Layout for the flashcard details
        flashcardFormLayout = new QFormLayout;
        flashcardFormLayout->addRow("Tag:", flashcardTagEdit);
        flashcardFormLayout->addRow("Frontside:", flashcardFrontsideEdit);
        flashcardFormLayout->addRow("Backside:", flashcardBacksideEdit);
        flashcardFormLayout->addRow("Status:", flashcardStatusEdit);

        flashcardTagEdit->setMinimumSize(400, 30); // Adjust the size as needed
        flashcardFrontsideEdit->setMinimumSize(400, 30); // Adjust the size as needed
        flashcardBacksideEdit->setMinimumSize(400, 30); // Adjust the size as needed
        flashcardStatusEdit->setMinimumSize(400, 30);

        // Add flashcard button
        addButton = new QPushButton("Add Flashcard", this);
        connect(addButton, &QPushButton::clicked, this, &MainWindow::addFlashcard);

        // Main layout
        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(tableView);
        layout->addLayout(flashcardFormLayout);
        layout->addWidget(addButton);

        // Set the central widget of the window
        QWidget *centralWidget = new QWidget(this);
        centralWidget->setLayout(layout);
        setCentralWidget(centralWidget);

        resize(650, 600); // Set window size

        // Connect table view selection change to slot
        connect(tableView->selectionModel(), &QItemSelectionModel::currentRowChanged, this, &MainWindow::displayFlashcardDetails);
    }

    void insertFlashcard(const QString &tag, const QString &frontside, const QString &backside, const QString &status) {
        // Insert a new row with flashcard details
        QList<QStandardItem*> newRow;
        newRow << new QStandardItem(tag)
               << new QStandardItem(frontside)
               << new QStandardItem(backside)
               << new QStandardItem(status);
        model->appendRow(newRow);
    }

private slots:
    void addFlashcard() {
        // Open dialog to add a new flashcard
        FlashcardEditorDialog dialog(this);
        connect(&dialog, &FlashcardEditorDialog::flashcardSaved, this, &MainWindow::insertFlashcard);
        dialog.exec();
    }

    void displayFlashcardDetails(const QModelIndex &index) {
        if (index.isValid()) {
            QString tag = model->item(index.row(), 0)->text();
            QString frontside = model->item(index.row(), 1)->text();
            QString backside = model->item(index.row(), 2)->text();
            QString status = model->item(index.row(), 3)->text();

            // Update flashcard details
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
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    // Inserting 10 initial flashcards
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
