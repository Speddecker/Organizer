#ifndef NOTEFORMWIDGET_HPP
#define NOTEFORMWIDGET_HPP

#include "note.hpp"

#include <QWidget>

#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>

class NoteFormWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NoteFormWidget(QWidget *parent = nullptr);
    explicit NoteFormWidget(Note* note, QWidget* parent = nullptr);

    Note *getNote() const;
    void setNote(Note *value);

private:
    Note* note = nullptr;

    QLabel* nameLabel = nullptr;
    QLineEdit* nameLineEdit = nullptr;

    QLabel* descriptionLabel = nullptr;
    QTextEdit* descriptionTextEdit = nullptr;

    QPushButton* okPushButton = nullptr;
    QPushButton* editPushButton = nullptr;
    QPushButton* deletePushButton = nullptr;

    void initComponents();

signals:
    void openMainWindow();

private slots:
    void okPushButtonClicked();
    void editPushButtonClicked();
    void deletePushButtonClicked();
};

#endif // NOTEFORMWIDGET_HPP
