#include "Well.hpp"

namespace Geo
{
namespace Domain
{
//

Well::
Well() {}

Well::
~Well() {}

// here we create several mock logs

Well::
Well(QString const& name)
  : _name(name)
{
  // for (int i = 0; i < 5; ++i) {
  // QString name = "Log_" + QString::number(qrand() % 100 + 100);
  // QString unit = "Unit_" + QString::number(qrand() % 100 + 100);
  // QString tool = "Tool_" + QString::number(qrand() % 100 + 100);

  // std::shared_ptr<Log> l(new Log(name, unit, tool));

  // _logs.append(l);
  // }
}


void
Well::
addLog(std::shared_ptr<Log> log)
{
  _logs.push_back(log);
}


std::vector<std::shared_ptr<Log> > &
Well::
getLogsListIterator()
{
  return _logs;
}
}
}
