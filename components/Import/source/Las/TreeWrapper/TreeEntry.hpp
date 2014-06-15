#ifndef Geo_Import_TreeWrapper_TreeEntry_hpp
#define Geo_Import_TreeWrapper_TreeEntry_hpp

#include <algorithm>
#include <vector>

#include <QSharedPointer>
#include <QVariant>

#include <Las/LasFile.hpp>

namespace Geo {
namespace Import {
namespace TreeWrapper {
/// Composite pattern. Used to represent LAS file strurcture as a tree
class TreeEntry: public QObject {
public:
  enum Column { Name        = 0,
                Description = 1,
                Value       = 2,
                ImportName  = 3,
                Type        = 4,
                Units       = 5,
                ImportUnits = 6,
                Size };

public:
  TreeEntry(QSharedPointer<LasFile> lasFile,
            TreeEntry*              parent = nullptr):
    _parent(parent),
    _lasFile(lasFile)
  {}

  virtual
  ~TreeEntry()
  {
    for (TreeEntry* entry : _entries)
      delete entry;
  }


  TreeEntry*
  parent()
  {
    return _parent;
  }


  std::vector<TreeEntry*> const
  entries() const
  {
    return _entries;
  }


  int
  positionOfChildEntry(TreeEntry* const childEntry) const
  {
    auto it = std::find(_entries.begin(),
                        _entries.end(),
                        childEntry);

    return it - _entries.begin();
  }


  QSharedPointer<LasFile> const
  lasFile() const
  {
    return _lasFile;
  }


  virtual QVariant
  data(int role, int column) = 0;

protected:
  TreeEntry*              _parent;
  QSharedPointer<LasFile> _lasFile;

  std::vector<TreeEntry*> _entries;
};
}
}
}
#endif // Geo_Import_TreeWrapper_TreeEntry_hpp
