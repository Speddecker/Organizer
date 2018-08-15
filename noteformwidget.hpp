#ifndef NOTEFORMWIDGET_HPP
#define NOTEFORMWIDGET_HPP

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

private:
    QLabel* nameLabel = nullptr;
    QLineEdit* nameLineEdit = nullptr;

    QLabel* descriptionLabel = nullptr;
    QTextEdit* descriptionTextEdit = nullptr;

    QPushButton* okPushButton = nullptr;
    QPushButton* editPushButton = nullptr;
    QPushButton* deletePushButton = nullptr;

signals:
    void openMainWindow();

private slots:
    void okPushButtonClicked();
    void editPushButtonClicked();
    void deletePushButtonClicked();
};

#endif // NOTEFORMWIDGET_HPP
