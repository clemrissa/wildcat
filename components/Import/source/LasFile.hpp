#ifndef Geo_Import_LasFile_hpp
#define Geo_Import_LasFile_hpp

#include <QtCore/QDateTime>
#include <QtCore/QMap>
#include <QtCore/QPair>
#include <QtCore/QString>
#include <QtCore/QVector>

namespace Geo {
namespace Import {
/**
 * Class contains all the informaation from a Las file split into special
 * structures
 */
class LasFile {
public:
  LasFile(): valid(false) {}

  struct WellInformationEntry {
    QString name;
    QString units;
    QString value;
  };

  struct WellInformation {
    QString wellName;
    double  start;
    double  stop;
    double  step;
    double  nullValue;
    QString units;

    QMap<QString, WellInformationEntry> entries;
  };

  struct CurveInformationEntry {
    QString units;
    QString code;
    QString description;
  };

  struct ParameterInformationEntry {
    QString mnem;
    QString unit;
    QString comment;
  };

public:
  QString
  getText() const;

  WellInformation                      wellInformation;
  QMap<QString, CurveInformationEntry> curveInformation;
  QVector<ParameterInformationEntry>   parameterInformation;

  QMap<QString, QVector<double> > data;

  bool valid;
};
}
}
#endif // Geo_Import_LasFile_hpp
