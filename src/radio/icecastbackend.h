/* This file is part of Clementine.
   Copyright 2010, David Sansome <me@davidsansome.com>

   Clementine is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Clementine is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Clementine.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ICECASTBACKEND_H
#define ICECASTBACKEND_H

#include <QObject>
#include <QUrl>

#include <boost/shared_ptr.hpp>

class Database;

class IcecastBackend : public QObject {
  Q_OBJECT

public:
  IcecastBackend(QObject* parent = 0);
  void Init(boost::shared_ptr<Database> db);

  static const char* kTableName;

  struct Station {
    Station()
      : bitrate(0),
        channels(0),
        samplerate(0) {
    }

    QString name;
    QUrl url;
    QString mime_type;
    int bitrate;
    int channels;
    int samplerate;
    QString genre;
  };
  typedef QList<Station> StationList;

  QStringList GetGenresAlphabetical();
  QStringList GetGenresByPopularity();
  StationList GetStations(const QString& genre = QString());

  void ClearAndAddStations(const StationList& stations);

  bool IsEmpty();

signals:
  void DatabaseReset();

private:
  boost::shared_ptr<Database> db_;

};

#endif // ICECASTBACKEND_H
