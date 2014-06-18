#ifndef Geo_Database_Connections_SettingsWidgetModel_Entry_hpp
#define Geo_Database_Connections_SettingsWidgetModel_Entry_hpp

#include <QVariant>

#include <algorithm>
#include <vector>

namespace Geo {
namespace Database {
namespace Models {
namespace SettingsWidgetModel {
//

class Entry: public QObject {
public:
  enum Column { Type = 0, Database = 1, Size };

public:
  Entry(Entry* parent = nullptr):
    _parent(parent)
  {
    //
  }


  virtual
  ~Entry()
  {
    for (Entry* entry : _entries)
      delete entry;
  }


  Entry*
  parent() const
  {
    return _parent;
  }


  std::vector<Entry*> const
  entries() const
  {
    return _entries;
  }


  int
  positionOfChildEntry(Entry* const childEntry) const
  {
    auto it = std::find(_entries.begin(), _entries.end(), childEntry);

    return it - _entries.begin();
  }


  virtual QVariant
  data(int role, int column) = 0;

protected:
  Entry* _parent;

  std::vector<Entry*> _entries;
};
}
}
}
}
#endif // Geo_Database_Connections_SettingsWidgetModel_Entry_hpp
