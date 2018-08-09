#include "event.hpp"

Event::Event(int id, QString name, QString date, QString time, QString text, QString place)
{
    this->id = id;
    this->name = name;
    this->date = date;
    this->time = time;
    this->text = text;
    this->place = place;
}

void Event::setId(int id)
{
    this->id = id;
}

void Event::setName(QString name)
{
    this->name = name;
}

void Event::setDate(QString date)
{
    this->date = date;
}

void Event::setTime(QString time)
{
    this->time = time;
}

void Event::setText(QString text)
{
    this->text = text;
}

void Event::setPlace(QString place)
{
    this->place = place;
}

int Event::getId()
{
    return this->id;
}

QString Event::getName()
{
    return this->name;
}

QString Event::getDate()
{
    return this->date;
}

QString Event::getTime()
{
    return this->time;
}

QString Event::getText()
{
    return this->text;
}

QString Event::getPlace()
{
    return this->place;
}
