#ifndef Geo_Database_SettingsTreeEntry_hpp
#define Geo_Database_SettingsTreeEntry_hpp

#include <QVariant>

#include <algorithm>
#include <vector>

namespace Geo {
namespace Database {
class SettingsTreeEntry: public QObject {
public:
  enum Column { Database = 0, Action = 1, Size };

public:
  SettingsTreeEntry(SettingsTreeEntry* parent = nullptr):
    _parent(parent)
  {
    //
  }


  virtual
  ~SettingsTreeEntry()
  {
    for (SettingsTreeEntry* entry : _entries)
      delete entry;
  }


  SettingsTreeEntry*
  parent() const
  {
    return _parent;
  }


  std::vector<SettingsTreeEntry*> const
  entries() const
  {
    return _entries;
  }


  int
  positionOfChildEntry(SettingsTreeEntry* const childEntry) const
  {
    auto it = std::find(_entries.begin(), _entries.end(), childEntry);

    return it - _entries.begin();
  }


  virtual QVariant
  data(int role, int column) = 0;

protected:
  SettingsTreeEntry* _parent;

  std::vector<SettingsTreeEntry*> _entries;
};
}
}
#endif // Geo_Database_SettingsTreeEntry_hpp
