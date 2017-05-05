#ifndef Geo_Domain_NArraySerializer_hpp
#define Geo_Domain_NArraySerializer_hpp

#include <QtCore/QSharedPointer>

#include <odb/core.hxx>

#include <sstream>
#include <vector>

namespace Geo {
namespace Domain {
//

/// Basic implementation which makes bite-wise copy of an object
template <typename T>
std::stringstream&
serialize(std::stringstream& stream, T const& t);

// {
// using ByteRepresentation = char[sizeof(T)];

// auto const& br =
// reinterpret_cast<ByteRepresentation const&>(t);

// stream << br;

// return stream;
// }

template <>
std::stringstream&
serialize<double
          >(std::stringstream& stream, double const& t)
{
  size_t bytes = sizeof(double);

  for (size_t i = 0; i < bytes; ++i)
  {
    unsigned long tLong = (unsigned long)t;
    unsigned char b     = (tLong >> (8 * i)) & 0xff;

    stream << b;
  }

  return stream;
}


class AbstractNArraySerializer
{};

template <unsigned D, typename T>
class NArraySerializer : public AbstractNArraySerializer
{
public:
  using ArrayOfLowerDimension = NArraySerializer<D - 1, T>;

  // lower dimension array

public:
  /// Creates non-dimensional value
  NArraySerializer() = default;

  ArrayOfLowerDimension&
  operator[](const unsigned int i)
  {
    return _data[i];
  }


  size_t
  size() const
  {
    return _data.size();
  }


  unsigned int
  d() const
  {
    return D;
  }


private:
  std::vector<ArrayOfLowerDimension> _data;
};

/// specialization for 1 dimension
template <>
class NArraySerializer<1, double> : public AbstractNArraySerializer
{
public:
  using ArrayOfLowerDimension = double;

public:
  /// Creates non-dimensional value
  NArraySerializer()
  {}


  ArrayOfLowerDimension&
  operator[](const unsigned int i)
  {
    return _data[i];
  }


  unsigned
  size() const
  {
    return _data.size();
  }


  unsigned
  d() const
  {
    return 1;
  }


private:
  std::vector<ArrayOfLowerDimension> _data;
};

//
}
}
#endif //  Geo_Domain_NArraySerializer_hpp
