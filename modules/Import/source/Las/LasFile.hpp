#pragma once

#include <QtCore/QDateTime>
#include <QtCore/QMap>
#include <QtCore/QPair>
#include <QtCore/QString>
#include <QtCore/QObject>

#include <vector>
#include <memory>

namespace Geo
{
namespace Import
{

/**
 * Class contains all the information from a Las file split into special
 * structures
 */
class LasFile : public QObject
{
  Q_OBJECT

public:

  LasFile() = default;
  LasFile(LasFile const& lasFile) = default;

  struct WellInformationEntry
  {
    QString units;
    QString value;
    QString description;
  };

  struct LasRequired
  {
    QString wellName;
    QString company;
    QString serviceCompany;
    QString field;
    QString location;
    QString date;
    QString country;
    QString state;
    QString county;
    QString province;
    QString api;
    QString uwi;
  };

  struct LogMetrics
  {
    double start;
    double stop;
    double step;
    double nullValue;
    QString units;
  };

  struct LogInformationEntry
  {
    QString units;
    QString code;
    QString description;
  };

  struct ParameterInformationEntry
  {
    QString name;
    QString units;
    QString value;
    QString description;
  };

public:

  QString fileName;

  LasRequired lasRequired;
  LogMetrics logMetrics;
  QMap<QString, WellInformationEntry> wellInformation;
  QMap<QString, ParameterInformationEntry> parameterInformation;
  QMap<QString, LogInformationEntry> logInformation;

  QMap<QString, std::vector<double> > data;

public:

  QString
  getText() const;

private:

  bool _valid = false;
};
}
}
