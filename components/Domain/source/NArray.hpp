#ifndef Geo_Domain_NArray_hpp
#define Geo_Domain_NArray_hpp

#include <QtCore/QSharedPointer>

#include <odb/core.hxx>

#include <vector>

namespace Geo {
namespace Domain {
//

class AbstractNArray
{
};

template <unsigned D, typename T>
class NArray: public AbstractNArray
{
public:
  using LDA =  NArray<D - 1, T>;            // lower dimension array

public:
  /// Creates non-dimensional value
  NArray()
  {
  }

  LDA&
  operator[](const unsigned int i)
  {
    return _data[i];
  }

  unsigned
  size() const { return _data.size(); }

  unsigned
  d() const { return D; }

private:
  std::vector<LDA> _data;
};

/// specialization for 1 dimension
template <>
class NArray<1, double> : public AbstractNArray
{
public:
  using LDA =  double;

public:
  /// Creates non-dimensional value
  NArray()
  {
  }

  LDA&
  operator[](const unsigned int i)
  {
    return _data[i];
  }

  unsigned
  size() const { return _data.size(); }

  unsigned
  d() const { return 1; }

private:
  std::vector<LDA> _data;
};

//
}
}
#endif //  Geo_Domain_NArray_hpp
