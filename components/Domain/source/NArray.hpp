#ifndef Geo_Domain_NArray_hpp
#define Geo_Domain_NArray_hpp

#include <QtCore/QSharedPointer>

#include <odb/core.hxx>

#include <vector>

namespace Geo {
namespace Domain {


class AbstractNArray
{};

/// Array is a mapping from Dref-dimentional reference point to
/// Dp-dimentional value point
template <unsigned Dref, unsigned Dp, typename T>
class NArray : public AbstractNArray
{
public:
  // array of lower dimension
  using ArrayOfLowerDimension = NArray<Dref - 1, Dp, T>;

public:
  /// Creates non-dimensional value
  NArray() = default;

  ArrayOfLowerDimension&
  operator[](const unsigned int i)
  { return _data[i]; }

  size_t
  size() const
  { return _data.size(); }

  unsigned int
  referenceDimensions() const
  { return Dref; }

private:
  std::vector<ArrayOfLowerDimension> _data;
};


/// specialization for 1 reference dimension
template <unsigned Dp, typename T>
class NArray<1, Dp, T> : public AbstractNArray
{
public:
  /// Creates non-dimensional value
  NArray() {}

  T&
  operator[](unsigned int const i)
  { return _data[i]; }

  size_t
  size() const
  { return _data.size(); }

  unsigned
  referenceDimensions() const
  { return 1; }

private:
  std::array<T, Dp> _data;
};


//
}
}

#endif //  Geo_Domain_NArray_hpp
