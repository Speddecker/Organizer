#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "note.hpp"
#include "event.hpp"

#include <QList>

#include <QListView>
#include <QTableView>
#include <QStandardItemModel>

#include <QSqlDatabase>

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
private:
    QSqlDatabase db;

    QList<Note*> notesList;
    QList<Event*> eventsList;


    //Элементы, относящиеся к работе с заметками
    QLabel *notesLabel                  = nullptr;

    QPushButton *createNoteButton       = nullptr;
    QPushButton *deleteNoteButton       = nullptr;
    QPushButton *editNoteButton         = nullptr;

    QListView *notesListView            = nullptr;
    QStandardItemModel *notesListModel  = nullptr;


    //Элементы, относящиеся к работе с событиями
    QLabel *eventsLabel                 = nullptr;

    QPushButton *createEventButton      = nullptr;
    QPushButton *deleteEventButton      = nullptr;
    QPushButton *editEventButton        = nullptr;

    QTableView *eventsTableView         = nullptr;
    QStandardItemModel *eventsModel     = nullptr;

public slots:
    void init(); // Configuring DB connection

    void noteListItemClicked();
    void eventTableItemClicked();

    void createNote();
    void deleteNote();
    void editNote();
    void noteInfo();

    void createEvent();
    void deleteEvent();
    void editEvent();
    void eventInfo();

    void getData();
};

#endif // WIDGET_HPP
