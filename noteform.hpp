#ifndef NOTEFORM_HPP
#define NOTEFORM_HPP

#include "note.hpp"

#include <QDialog>

#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QBoxLayout>

class NoteForm : public QDialog
{
    Q_OBJECT
public:
    explicit NoteForm(QWidget* parent = nullptr);
    explicit NoteForm(Note* note, QWidget* parent = nullptr);

private:
    QLabel* nameLabel              = nullptr;
    QLineEdit* nameLineEdit        = nullptr;
    QLabel* descriptionLabel       = nullptr;
    QTextEdit* descriptionTextEdit = nullptr;
    QPushButton* okButton          = nullptr;
    QPushButton* editButton        = nullptr;
    QPushButton* deleteButton      = nullptr;
    QHBoxLayout* buttonLayout      = nullptr;
    QVBoxLayout* mainLayout        = nullptr;

private slots:
    void okButtonPressed();
    void editButtonPressed();
    void deleteButtonPressed();
};

#endif // NOTEFORM_HPP
