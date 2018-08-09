#include "note.hpp"

Note::Note(int id, QString name, QString text)
{
    this->id = id;
    this->name = name;
    this->text = text;
}

void Note::setId(int id)
{
    this->id = id;
}

void Note::setName(QString name)
{
    this->name = name;
}

void Note::setText(QString text)
{
    this->text = text;
}

int Note::getId()
{
    return id;
}

QString Note::getName()
{
    return this->name;
}

QString Note::getText()
{
    return this->text;
}
