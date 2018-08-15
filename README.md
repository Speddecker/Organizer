# organizer
Simple and light-weight organizer for notes and events

#Database scheme (SQLite3) - local storage for notes and events
CREATE TABLE notes (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  name TEXT NOT NULL,
  text TEXT
);

CREATE TABLE events (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  name TEXT NOT NULL,
  date TEXT NOT NULL,
  time TEXT,
  text TEXT,
  place TEXT
);
