#pragma once

#include <algorithm>
#include <vector>
#include <memory>

#include <QtCore/QObject>
#include <QtCore/QVariant>

namespace Geo
{
namespace Database
{
namespace Gui
{

class ExplorerEntry : public QObject
{
public:

  enum Column
  {
    Category    = 0,
    Description = 1,
    Size
  };

public:

  ExplorerEntry(ExplorerEntry* parent = nullptr)
    : _parent(parent)
  {
    //
  }

  virtual
  ~ExplorerEntry()
  {}

  ExplorerEntry*
  parent() const
  {
    return _parent;
  }

  std::vector<std::unique_ptr<ExplorerEntry> > const &
  entries() const
  {
    return _entries;
  }

  int
  positionOfChildEntry(ExplorerEntry* const childEntry) const
  {
    auto it = std::find_if(_entries.begin(),
                           _entries.end(),
                           [&](std::unique_ptr<ExplorerEntry> const & e )
          {
            return (e.get() == childEntry);
          } );

    return it - _entries.begin();
  }

  virtual QVariant
  data(int role, int column) = 0;

  virtual
  bool
  setData(int role, int column, QVariant value)
  {
    Q_UNUSED(role);
    Q_UNUSED(column);
    Q_UNUSED(value);
    return false;
  }

protected:

  ExplorerEntry* _parent;

  std::vector<std::unique_ptr<ExplorerEntry> > _entries;
};

//
}
}
}
