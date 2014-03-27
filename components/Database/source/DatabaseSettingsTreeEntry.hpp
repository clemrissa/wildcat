#ifndef Geo_Database_DatabaseSettingsTreeEntry_hpp
#define Geo_Database_DatabaseSettingsTreeEntry_hpp

#include <QVariant>

#include <algorithm>
#include <vector>

namespace Geo {
namespace Database {
class DatabaseSettingsTreeEntry: public QObject {
public:
  enum Column { Database = 0, Action = 1, Size };

public:
  DatabaseSettingsTreeEntry(DatabaseSettingsTreeEntry* parent = nullptr):
    _parent(parent) {
    //
  }

  virtual
  ~DatabaseSettingsTreeEntry() {
    for (DatabaseSettingsTreeEntry* entry : _entries)
      delete entry;
  }

  DatabaseSettingsTreeEntry*
  parent() const {
    return _parent;
  }

  std::vector<DatabaseSettingsTreeEntry*> const
  entries() const {
    return _entries;
  }

  int
  positionOfChildEntry(DatabaseSettingsTreeEntry* const childEntry) const {
    auto it = std::find(_entries.begin(), _entries.end(), childEntry);

    return it - _entries.begin();
  }

  virtual QVariant
  data(int role, int column) = 0;

protected:
  DatabaseSettingsTreeEntry* _parent;

  std::vector<DatabaseSettingsTreeEntry*> _entries;
};
}
}
#endif // Geo_Database_DatabaseSettingsTreeEntry_hpp
