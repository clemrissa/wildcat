#ifndef Geo_Domain_CurveType_hpp
#define Geo_Domain_CurveType_hpp

#include <QtCore/QSharedPointer>

#include <odb/core.hxx>

namespace Geo {
namespace Domain {
//


#ifdef ODB_COMPILER
  #pragma db object
#endif
class CurveType 
{
public:
  typedef QSharedPointer<CurveType> Shared;

public:
  enum Scale {
    Linear,
    Log2,
    Log10,
    ScaleSize
  };

  enum Type {
    Continuous,
    TopBottom,
    Blocks,
    TypeSize
  };

  CurveType();

public: // setter getters

  QString mainFamily() const { return _mainFamily; }
  QString family() const { return _family; }
  QString unit() const { return _unit; }
  double min() const { return _min; }
  double max() const { return _max; }
  Scale scale() const { return _scale; }
  Type type() const { return _type; }

  void setMainFamily(QString const mainFamily) { _mainFamily = mainFamily; }
  void setFamily(QString const family) { _family = family; }
  void setUnit(QString const unit) { _unit = unit; }
  void setMin(double const min) { _min = min; }
  void setMax(double const max) { _max = max; }
  void setScale(Scale const scale) { _scale = scale; }
  void setType(Type const type) { _type = type; }

private:
  friend class odb::access;


#ifdef ODB
  #pragma db id auto
#endif
  unsigned int _id;

  QString _mainFamily;
  QString _family;
  QString _unit; // TODO: change to unit data type
  double _min;
  double _max;

  Scale _scale;
  Type _type;
};

//
}
}
#endif //  Geo_Domain_CurveType_hpp
