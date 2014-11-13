#ifndef Geo_Import_LasFile_hpp
#define Geo_Import_LasFile_hpp

#include <QtCore/QDateTime>
#include <QtCore/QMap>
#include <QtCore/QPair>
#include <QtCore/QSharedPointer>
#include <QtCore/QString>
#include <QtCore/QVector>

namespace Geo {
namespace Import {
/**
 * Class contains all the informaation from a Las file split into special
 * structures
 */
class LasFile: public QObject
{
  Q_OBJECT

public:
  typedef QSharedPointer<LasFile> Shared;

public:
  LasFile(): valid(false)
  {
  }

  LasFile(LasFile const& lasFile);

  struct WellInformationEntry
  {
    QString name; // TODO remove. it is used as a key
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
    double  start;
    double  stop;
    double  step;
    double  nullValue;
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

  LasRequired                              lasRequired;
  QMap<QString, WellInformationEntry>      wellInformation;
  QMap<QString, ParameterInformationEntry> parameterInformation;
  QMap<QString, LogInformationEntry>       logInformation;

  QMap<QString, QVector<double> > data;

  bool valid;

public:
  QString
  getText() const;
};
}
}
#endif // Geo_Import_LasFile_hpp
