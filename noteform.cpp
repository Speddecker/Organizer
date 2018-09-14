#include "noteform.hpp"

NoteForm::NoteForm(QWidget* parent)
    : QDialog(parent)
{
    this->setWindowTitle("Note info");
    this->setGeometry(parentWidget()->geometry());

    nameLabel = new QLabel("Note's name:");
    nameLineEdit = new QLineEdit();
    descriptionLabel = new QLabel("Note's description:");
    descriptionTextEdit = new QTextEdit();
    okButton = new QPushButton("Ok");
    editButton = new QPushButton("Edit");
    deleteButton = new QPushButton("Delete");
    buttonLayout = new QHBoxLayout();
    mainLayout = new QVBoxLayout();

    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(okButton);

    mainLayout->addWidget(nameLabel);
    mainLayout->addWidget(nameLineEdit);
    mainLayout->addWidget(descriptionLabel);
    mainLayout->addWidget(descriptionTextEdit);
    mainLayout->addLayout(buttonLayout);

    this->setLayout(mainLayout);

    connect(okButton, SIGNAL(pressed()), this, SLOT(okButtonPressed()));
    connect(editButton, SIGNAL(pressed()), this, SLOT(editButtonPressed()));
    connect(deleteButton, SIGNAL(pressed()), this, SLOT(deleteButtonPressed()));
}

void NoteForm::okButtonPressed()
{

}

void NoteForm::editButtonPressed()
{

}

void NoteForm::deleteButtonPressed()
{

}
