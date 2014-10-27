#include "Well.hpp"

namespace Geo {
namespace Domain {
Well::
Well() {}

Well::
~Well() {}

// here we create several mock logs

Well::
Well(QString const& name,
     float const&   depth,
     float const&   absDepth,
     float const&   altitude):
  _name(name),
  _depth(depth),
  _absDepth(absDepth),
  _altitude(altitude)
{
  // for (int i = 0; i < 5; ++i) {
  // QString name = "Log_" + QString::number(qrand() % 100 + 100);
  // QString unit = "Unit_" + QString::number(qrand() % 100 + 100);
  // QString tool = "Tool_" + QString::number(qrand() % 100 + 100);

  // QSharedPointer<Log> l(new Log(name, unit, tool));

  // _logs.append(l);
  // }
}


void
Well::
addLog(QSharedPointer<Log> log)
{
  _logs.append(log);
}


QVectorIterator<QSharedPointer<Log> >
Well::
getLogsListIterator()
{
  return QVectorIterator<QSharedPointer<Log> >(_logs);
}
}
}
