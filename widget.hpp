#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "note.hpp"
#include "event.hpp"
#include "noteformwidget.hpp"

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
    Widget(QWidget* parent = nullptr);
    ~Widget();

private:
    QSqlDatabase db;

    QList<Note*> notesList;
    QList<Event*> eventsList;


    //Note's related elements
    QLabel* notesLabel                  = nullptr;

    QPushButton* createNotePushButton   = nullptr;

    QListView* notesListView            = nullptr;
    QStandardItemModel* notesListModel  = nullptr;

    NoteFormWidget* noteForm            = nullptr;


    //Event's related elements
    QLabel* eventsLabel                 = nullptr;

    QPushButton* createEventPushButton  = nullptr;
    QPushButton* deleteEventPushButton  = nullptr;
    QPushButton* editEventPushButton    = nullptr;

    QTableView* eventsTableView         = nullptr;
    QStandardItemModel* eventsModel     = nullptr;

    void init(); // Configuring database connection
    void getData(); //Geting data from database and filling the models

private slots:
    void eventTableItemClicked();

    void createNote();
    void noteInfo();

    void createEvent();
    void deleteEvent();
    void editEvent();
    void eventInfo();
};

#endif // WIDGET_HPP
