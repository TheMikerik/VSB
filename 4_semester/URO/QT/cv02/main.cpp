#include <QApplication>
#include <QMainWindow>
#include <QDialog>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableView>
#include <QPushButton>
#include <QStandardItemModel>

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

        // Button to add a new flashcard
        addButton = new QPushButton("Add Flashcard", this);
        connect(addButton, &QPushButton::clicked, this, &MainWindow::addFlashcard);

        // Main layout
        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(tableView);
        layout->addWidget(addButton);

        // Set the central widget of the window
        QWidget *centralWidget = new QWidget(this);
        centralWidget->setLayout(layout);
        setCentralWidget(centralWidget);

        resize(440, 600); // Set window size
    }

private slots:
    void addFlashcard() {
        // Open dialog to add a new flashcard
        FlashcardEditorDialog dialog(this);
        connect(&dialog, &FlashcardEditorDialog::flashcardSaved, this, &MainWindow::insertFlashcard);
        dialog.exec();
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

private:
    QStandardItemModel *model; // Model for the table
    QTableView *tableView; // Table view to display flashcards
    QPushButton *addButton; // Button to add a new flashcard
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}

#include "main.moc"
