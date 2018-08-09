#ifndef EVENT_HPP
#define EVENT_HPP

#include <QString>

class Event
{
public:
    Event(int id, QString name, QString date, QString time, QString text, QString place);

    void setId(int id);
    void setName(QString name);
    void setDate(QString date);
    void setTime(QString time);
    void setText(QString text);
    void setPlace(QString place);

    int getId();
    QString getName();
    QString getDate();
    QString getTime();
    QString getText();
    QString getPlace();

private:
    int id;
    QString name;
    QString date;
    QString time;
    QString text;
    QString place;
};

#endif // EVENT_HPP
