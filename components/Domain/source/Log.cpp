#include "Log.hpp"

#include <QtCore/QByteArray>
#include <QtCore/QDataStream>

#include <boost/math/constants/constants.hpp>

#include "Well.hpp"

namespace Geo {
namespace Domain {
// Using Declarations {{{
// ----------------------------------------------------------------------------
namespace {
using boost::math::constants::pi;
}
// ----------------------------------------------------------------------------
// }}} Using Declarations

Log::
Log()
{
  generateData();
}


Log::
~Log() {}

void
Log::
generateData()
{
  // _topDepth = 200.0 + qrand() % 20;
  // _step     = 0.50; // half meter

  // const int    numPoints = 1000;
  // const double min       = 20.0;
  // const double max       = 100.0;
  // double       r1        = qrand() / (double)RAND_MAX;

  // for (int i = 0; i < numPoints; ++i) {
  // double depth = _topDepth + i * _step;
  // double value = min +
  // (max -
  // min) / 2.0 *
  // (1 + sin(depth * 2 * pi<double>() / (100.0 + r1 * 200.0)));

  // _values.append(value);
  // }

  // !how to serialize the data array of a curve

  /*
   *  QByteArray byteArray;
   *  QDataStream dataStream(&byteArray);
   *
   *  dataStream << _topDepth;
   *  dataStream << _step;
   *  <
   *  for(int i = 0; i < numPoints; ++i) {
   *    dataStream << _values[i];
   *  }
   *
   *  // finally we can access \0-terminated data as follows:
   *
   *  char *data = byteArray.data();
   *
   */
}
}
}
