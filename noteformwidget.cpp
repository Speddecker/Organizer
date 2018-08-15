#include "noteformwidget.hpp"

#include <QBoxLayout>

NoteFormWidget::NoteFormWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("Note info");

    nameLabel = new QLabel("Note's name");
    nameLineEdit = new QLineEdit();

    descriptionLabel = new QLabel("Note's description");
    descriptionTextEdit = new QTextEdit();

    okPushButton = new QPushButton("Ok");
    editPushButton = new QPushButton("Edit");
    deletePushButton = new QPushButton("Delete");

    editPushButton->hide();
    deletePushButton->hide();

    connect(okPushButton, SIGNAL(clicked(bool)), this, SLOT(okPushButtonClicked()));
    connect(editPushButton, SIGNAL(clicked(bool)), this, SLOT(editPushButtonClicked()));
    connect(deletePushButton, SIGNAL(clicked(bool)), this, SLOT(deletePushButtonClicked()));

    QHBoxLayout* buttonBox = new QHBoxLayout();
    buttonBox->addWidget(deletePushButton);
    buttonBox->addWidget(editPushButton);
    buttonBox->addWidget(okPushButton);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(nameLabel);
    mainLayout->addWidget(nameLineEdit);
    mainLayout->addWidget(descriptionLabel);
    mainLayout->addWidget(descriptionTextEdit);
    mainLayout->addLayout(buttonBox);

    this->setLayout(mainLayout);
}

void NoteFormWidget::okPushButtonClicked()
{
    this->hide();
    emit openMainWindow();
}

void NoteFormWidget::editPushButtonClicked()
{
    this->hide();
    emit openMainWindow();
}

void NoteFormWidget::deletePushButtonClicked()
{
    this->hide();
    emit openMainWindow();
}
