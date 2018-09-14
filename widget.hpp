#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "note.hpp"
#include "event.hpp"
#include "noteform.hpp"

#include <QList>
#include <QLabel>
#include <QWidget>
#include <QListView>
#include <QBoxLayout>
#include <QTableView>
#include <QPushButton>
#include <QSqlDatabase>
#include <QStandardItemModel>
#include <QResizeEvent>


class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget* parent = nullptr);
    ~Widget();

private:
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    QList<Note*> notesList;
    QList<Event*> eventsList;

    QHBoxLayout *mainLayout             = nullptr;

    //Note's related elements
    QLabel* notesLabel                  = nullptr;
    QPushButton* createNotePushButton   = nullptr;
    QListView* notesListView            = nullptr;
    QStandardItemModel* notesListModel  = nullptr;
    NoteForm* noteForm                  = nullptr;
    QVBoxLayout *notesLayout            = nullptr;

    //Event's related elements
    QLabel* eventsLabel                 = nullptr;
    QPushButton* createEventPushButton  = nullptr;
    QPushButton* deleteEventPushButton  = nullptr;
    QPushButton* editEventPushButton    = nullptr;
    QTableView* eventsTableView         = nullptr;
    QStandardItemModel* eventsModel     = nullptr;
    QVBoxLayout *eventsLayout           = nullptr;

    void getData(); //Geting data from database and filling the models

private slots:
    virtual void resizeEvent(QResizeEvent*);

    void eventTableItemClicked();

    void createNote();
    void noteInfo();

    void createEvent();
    void deleteEvent();
    void editEvent();
    void eventInfo();
};

#endif // WIDGET_HPP
