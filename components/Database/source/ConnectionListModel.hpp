#ifndef Geo_Database_ConnectionListModel_hpp
#define Geo_Database_ConnectionListModel_hpp

#include <Database/Connection>

#include <QObject>
#include <QObjectList>

#include <boost/iterator/iterator_facade.hpp>

namespace Geo {
namespace Database {
namespace Auxiliary {
template <class StdIterator,
          class Type>
class Iterator
  : public boost::iterator_facade<Iterator<StdIterator, Type>,
                                  Type,
                                  boost::forward_traversal_tag> {
private:
  typedef boost::iterator_facade<Iterator<StdIterator, Type>,
                                 Type,
                                 boost::forward_traversal_tag>
    Base;

public:
  typedef typename Base::reference Reference;
  typedef typename Base::pointer   Pointer;

public:
  Iterator() : _iterator() {}

  explicit
  Iterator(StdIterator const& iterator) : _iterator(iterator) {}

private:
  friend class boost::iterator_core_access;

  void
  increment() { ++_iterator; }

  bool
  equal(Iterator const& other) const {
    return _iterator == other._iterator;
  }

  Reference
  dereference() const {
    return static_cast<Type*>(_iterator);
  }

private:
  StdIterator _iterator;
};
}

class ConnectionListModel {
public:
  typedef QObjectList ConnectionList;
  typedef Auxiliary::Iterator<
      typename ConnectionList::const_iterator,
      Connection const*>
    ConstIterator;

public:
  virtual
  ~ConnectionListModel() {}

  virtual
  ConstIterator
  begin() const = 0;

  virtual
  ConstIterator
  end() const = 0;
};
}
}
#endif
