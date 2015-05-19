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
  using ArrayOfLowerDimension =  NArray<D - 1, T>;            // lower
                                                              // dimension
                                                              // array

public:
  /// Creates non-dimensional value
  NArray() = default;

  ArrayOfLowerDimension&
  operator[](const unsigned int i)
  {
    return _data[i];
  }

  size_t
  size() const { return _data.size(); }

  unsigned
  d() const { return D; }

private:
  std::vector<ArrayOfLowerDimension> _data;
};

/// specialization for 1 dimension
template <>
class NArray<1, double> : public AbstractNArray
{
public:
  using ArrayOfLowerDimension =  double;

public:
  /// Creates non-dimensional value
  NArray()
  {
  }

  ArrayOfLowerDimension&
  operator[](const unsigned int i)
  {
    return _data[i];
  }

  size_t
  size() const { return _data.size(); }

  unsigned
  d() const { return 1; }

private:
  std::vector<ArrayOfLowerDimension> _data;
};

//
}
}

#endif //  Geo_Domain_NArray_hpp
