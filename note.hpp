#ifndef NOTE_HPP
#define NOTE_HPP

#include <QString>

class Note
{
public:
    Note(int id, QString name, QString text);

    void setId(int id);
    void setName(QString name);
    void setText(QString text);

    int getId();
    QString getName();
    QString getText();

private:
    int id;
    QString name;
    QString text;
};

#endif // NOTE_HPP
