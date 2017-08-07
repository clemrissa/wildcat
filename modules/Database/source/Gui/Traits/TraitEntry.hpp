#pragma once

#include <algorithm>
#include <vector>
#include <memory>

#include <QtCore/QVariant>

namespace Geo
{
namespace Database
{
namespace Gui
{

class TraitEntry : public QObject
{
public:
  TraitEntry(TraitEntry* parent = nullptr)
    : _parent(parent)
  {
    //
  }

  virtual
  ~TraitEntry() = default;

  TraitEntry*
  parent() const
  {
    return _parent;
  }

  std::vector<std::unique_ptr<TraitEntry>> const &
  entries() const
  {
    return _entries;
  }

  int
  positionOfChildEntry(TraitEntry* const childEntry) const
  {
    auto it = std::find_if(_entries.begin(), _entries.end(), 
                           [&](std::unique_ptr<TraitEntry> const & e)
                           { return (e.get() == childEntry); });

    return it - _entries.begin();
  }

  virtual QVariant
  data(int role, int column) = 0;

protected:

  TraitEntry* _parent;

  std::vector<std::unique_ptr<TraitEntry>> const _entries;
};

//
}
}
}
