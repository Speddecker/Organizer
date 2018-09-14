#include "widget.hpp"
#include "noteform.hpp"

#include <QSqlQuery>

#include <QDialog>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QHeaderView>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("Organizer");
    this->setMinimumSize(QSize(700, 350));

    db.setDatabaseName("/home/stanislav/Desktop/Organizer.db");

    //Конфигурация элементов, работающих с заметками
    notesLabel  = new QLabel("Notes");

    notesListView = new QListView(this);
    notesListModel = new QStandardItemModel();
    notesListView->setModel(notesListModel);
    notesListView->setSelectionMode(QAbstractItemView::SingleSelection);
    notesListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    notesListView->setFixedWidth(this->width()/3);

    createNotePushButton = new QPushButton("Create note", this);

    connect(notesListView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(noteInfo()));
    connect(createNotePushButton, SIGNAL(clicked(bool)), this, SLOT(createNote()));

    notesLayout = new QVBoxLayout();
    notesLayout->addWidget(notesLabel);
    notesLayout->addWidget(notesListView);
    notesLayout->addWidget(createNotePushButton);

    //Конфигурация элементов, работающих с событиями
    eventsLabel  = new QLabel("Events");

    eventsTableView = new QTableView(this);
    eventsModel = new QStandardItemModel();
    QStringList eventsTableHeaders;
    eventsTableHeaders.append("Date");
    eventsTableHeaders.append("Time");
    eventsTableHeaders.append("Place");
    eventsTableHeaders.append("Name");
    eventsModel->setHorizontalHeaderLabels(eventsTableHeaders);
    eventsTableView->setModel(eventsModel);
    eventsTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    eventsTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    eventsTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    eventsTableView->horizontalHeader()->setStretchLastSection(true);

    createEventPushButton = new QPushButton("Create event", this);
    deleteEventPushButton = new QPushButton("Delete event", this);
    editEventPushButton   = new QPushButton("Edit event", this);

    deleteEventPushButton->setDisabled(true);
    editEventPushButton->setDisabled(true);

    connect(eventsTableView, SIGNAL(pressed(QModelIndex)), this, SLOT(eventTableItemClicked()));
    connect(eventsTableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(eventInfo()));
    connect(createEventPushButton, SIGNAL(clicked(bool)), this, SLOT(createEvent()));
    connect(deleteEventPushButton, SIGNAL(clicked(bool)), this, SLOT(deleteEvent()));
    connect(editEventPushButton, SIGNAL(clicked(bool)), this, SLOT(editEvent()));

    eventsLayout = new QVBoxLayout();
    eventsLayout->addWidget(eventsLabel);
    eventsLayout->addWidget(eventsTableView);
    eventsLayout->addWidget(createEventPushButton);
    eventsLayout->addWidget(deleteEventPushButton);
    eventsLayout->addWidget(editEventPushButton);

    //Layout, который собирает все основные компоненты
    mainLayout = new QHBoxLayout();
    mainLayout->addLayout(notesLayout);
    mainLayout->addLayout(eventsLayout);

    this->setLayout(mainLayout);

    getData();
}

Widget::~Widget()
{
    db.close();
}

void Widget::eventTableItemClicked()
{
    deleteEventPushButton->setEnabled(true);
    editEventPushButton->setEnabled(true);
}

void Widget::createNote()
{
    QDialog* dlg = new NoteForm(this);
    dlg->exec();
    this->close();
}

void Widget::noteInfo()
{
}

void Widget::createEvent()
{
    QDialog dlg(this);
    dlg.setWindowTitle(tr("Create event"));

    QLabel *nameLabel = new QLabel("Input event's name: ", &dlg);
    QLineEdit *name = new QLineEdit(&dlg);

    QLabel *dateLabel = new QLabel("Input event's date: ", &dlg);
    QLineEdit *date = new QLineEdit(&dlg);

    QLabel *timeLabel = new QLabel("Input event's time: ", &dlg);
    QLineEdit *time = new QLineEdit(&dlg);

    QLabel *placeLabel = new QLabel("Input event's place: ", &dlg);
    QLineEdit *place = new QLineEdit(&dlg);

    QLabel *textLabel = new QLabel("Input event's description: ", &dlg);
    QTextEdit *text = new QTextEdit(&dlg);

    QDialogButtonBox *btn_box = new QDialogButtonBox(&dlg);
    btn_box->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(btn_box, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
    connect(btn_box, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);

    QGridLayout *datetime = new QGridLayout();
    datetime->addWidget(dateLabel, 0, 0);
    datetime->addWidget(timeLabel, 0, 1);
    datetime->addWidget(date, 1, 0);
    datetime->addWidget(time, 1, 1);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(nameLabel);
    layout->addWidget(name);
    layout->addLayout(datetime);
    layout->addWidget(placeLabel);
    layout->addWidget(place);
    layout->addWidget(textLabel);
    layout->addWidget(text);
    layout->addWidget(btn_box);

    dlg.setLayout(layout);

    // В случае, если пользователь нажал "Ok".
    if(dlg.exec() == QDialog::Accepted)
    {
        if (db.open())
        {
            QSqlQuery query;
            query.prepare("INSERT INTO events(name, date, time, text, place) VALUES(?, ?, ?, ?, ?);");
            query.bindValue(0, name->text());
            query.bindValue(1, date->text());
            query.bindValue(2, time->text());
            query.bindValue(3, text->toPlainText());
            query.bindValue(4, place->text());
            query.exec();

            eventsList.clear();
        }
        getData();
    }
}

void Widget::deleteEvent()
{
    QDialog dlg(this);
    dlg.setWindowTitle(tr("Delete event"));

    int pos = eventsTableView->selectionModel()->selectedRows().at(0).row();

    QLabel *label = new QLabel("Do you really want to delete this event?", &dlg);

    QDialogButtonBox *btn_box = new QDialogButtonBox(&dlg);
    btn_box->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(btn_box, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
    connect(btn_box, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(label);
    layout->addWidget(btn_box);

    dlg.setLayout(layout);

    // В случае, если пользователь нажал "Ok".
    if(dlg.exec() == QDialog::Accepted)
    {
        if (db.open())
        {
            QSqlQuery query;
            query.prepare("DELETE FROM events WHERE id=?");
            query.bindValue(0, eventsList.at(pos)->getId());
            query.exec();

            eventsList.clear();
        }

        getData();
    }
}

void Widget::editEvent()
{
    QDialog dlg(this);
    dlg.setWindowTitle(tr("Create event"));

    int pos = eventsTableView->selectionModel()->selectedRows().at(0).row();
    Event* event = eventsList.at(pos);

    QLabel *nameLabel = new QLabel("Input event's name: ", &dlg);
    QLineEdit *name = new QLineEdit(event->getName(), &dlg);

    QLabel *dateLabel = new QLabel("Input event's date: ", &dlg);
    QLineEdit *date = new QLineEdit(event->getDate(), &dlg);

    QLabel *timeLabel = new QLabel("Input event's time: ", &dlg);
    QLineEdit *time = new QLineEdit(event->getTime(), &dlg);

    QLabel *placeLabel = new QLabel("Input event's place: ", &dlg);
    QLineEdit *place = new QLineEdit(event->getPlace(), &dlg);

    QLabel *textLabel = new QLabel("Input event's description: ", &dlg);
    QTextEdit *text = new QTextEdit(event->getText(), &dlg);

    QDialogButtonBox *btn_box = new QDialogButtonBox(&dlg);
    btn_box->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(btn_box, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
    connect(btn_box, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);

    QGridLayout *datetime = new QGridLayout();
    datetime->addWidget(dateLabel, 0, 0);
    datetime->addWidget(timeLabel, 0, 1);
    datetime->addWidget(date, 1, 0);
    datetime->addWidget(time, 1, 1);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(nameLabel);
    layout->addWidget(name);
    layout->addLayout(datetime);
    layout->addWidget(placeLabel);
    layout->addWidget(place);
    layout->addWidget(textLabel);
    layout->addWidget(text);
    layout->addWidget(btn_box);

    dlg.setLayout(layout);

    // В случае, если пользователь нажал "Ok".
    if(dlg.exec() == QDialog::Accepted)
    {
        if (db.open())
        {
            QSqlQuery query;
            query.prepare("UPDATE events SET name=?, date=?, time=?, text=?, place=? WHERE id=?");
            query.bindValue(0, name->text());
            query.bindValue(1, date->text());
            query.bindValue(2, time->text());
            query.bindValue(3, text->toPlainText());
            query.bindValue(4, place->text());
            query.bindValue(5, eventsList.at(pos)->getId());
            query.exec();

            eventsList.clear();
        }
        getData();
    }
}

void Widget::eventInfo()
{
    QDialog dlg(this);
    dlg.setWindowTitle(tr("Event info"));

    int pos = eventsTableView->selectionModel()->selectedRows().at(0).row();

    QLabel *nameLabel = new QLabel("Event's name: ", &dlg);
    QLineEdit *name = new QLineEdit(eventsList.at(pos)->getName(), &dlg);
    name->setReadOnly(true);

    QLabel *dateLabel = new QLabel("Event's date: ", &dlg);
    QLineEdit *date = new QLineEdit(eventsList.at(pos)->getDate(), &dlg);
    date->setReadOnly(true);

    QLabel *timeLabel = new QLabel("Event's time: ", &dlg);
    QLineEdit *time = new QLineEdit(eventsList.at(pos)->getTime(), &dlg);
    time->setReadOnly(true);

    QLabel *placeLabel = new QLabel("Event's place: ", &dlg);
    QLineEdit *place = new QLineEdit(eventsList.at(pos)->getPlace(), &dlg);
    place->setReadOnly(true);

    QLabel *textLabel = new QLabel("Event's description: ", &dlg);
    QTextEdit *text = new QTextEdit(eventsList.at(pos)->getText(), &dlg);
    text->setReadOnly(true);

    QDialogButtonBox *btn_box = new QDialogButtonBox(&dlg);
    btn_box->setStandardButtons(QDialogButtonBox::Ok);

    connect(btn_box, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
    connect(btn_box, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);
    QGridLayout *datetime = new QGridLayout();
    datetime->addWidget(dateLabel, 0, 0);
    datetime->addWidget(timeLabel, 0, 1);
    datetime->addWidget(date, 1, 0);
    datetime->addWidget(time, 1, 1);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(nameLabel);
    layout->addWidget(name);
    layout->addLayout(datetime);
    layout->addWidget(placeLabel);
    layout->addWidget(place);
    layout->addWidget(textLabel);
    layout->addWidget(text);
    layout->addWidget(btn_box);

    dlg.setLayout(layout);

    // В случае, если пользователь нажал "Ok".
    if(dlg.exec() == QDialog::Accepted) {

    }
}

void Widget::getData()
{
    notesListModel->removeRows(0, notesListModel->rowCount()); //Очистка списка заметок от старых данных

    if (db.open())
    {
        //Заполнение данных о заметках
        QSqlQuery notesQuery("SELECT * FROM notes;"); //Запрос выполняется автоматически, при создании объекта

        int i = 0;
        while(notesQuery.next())
        {
            notesList.append(new Note(notesQuery.value("id").toInt(),
                                      notesQuery.value("name").toString(),
                                      notesQuery.value("text").toString()));

            notesListModel->setItem(i, 0, new QStandardItem(notesList.at(i)->getName()));
            i++;
        }

        eventsModel->removeRows(0, eventsModel->rowCount()); //Очистка таблицы событий от старых данных

        //Заполнение данных о событиях
        QSqlQuery eventsQuery("SELECT * FROM events;"); //Запрос выполняется автоматически, при создании объекта

        i = 0;
        while(eventsQuery.next())
        {
            eventsList.append(new Event(eventsQuery.value("id").toInt(),
                                        eventsQuery.value("name").toString(),
                                        eventsQuery.value("date").toString(),
                                        eventsQuery.value("time").toString(),
                                        eventsQuery.value("text").toString(),
                                        eventsQuery.value("place").toString()));

            eventsModel->setItem(i, 0, new QStandardItem(eventsList.at(i)->getDate()));
            eventsModel->setItem(i, 1, new QStandardItem(eventsList.at(i)->getTime()));
            eventsModel->setItem(i, 2, new QStandardItem(eventsList.at(i)->getPlace()));
            eventsModel->setItem(i, 3, new QStandardItem(eventsList.at(i)->getName()));
            i++;
        }
    }
}

void Widget::resizeEvent(QResizeEvent *)
{
    notesListView->setFixedWidth(this->width()/3);
    eventsTableView->resizeRowsToContents();
}
