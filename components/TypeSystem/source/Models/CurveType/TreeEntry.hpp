#ifndef Geo_TypeSystem_TreeWrapper_TreeEntry_hpp
#define Geo_TypeSystem_TreeWrapper_TreeEntry_hpp

#include <algorithm>
#include <vector>

#include <QtCore/QObject>
#include <QtCore/QSharedPointer>
#include <QtCore/QVariant>

#include <Domain/CurveType>

#include <Database/Connections/Connection>

class QAbstractItemModel;

namespace Geo {
namespace TypeSystem {
namespace Models {
namespace CurveTypes {
//

/// @brief Composite pattern. Used to represent CurveType structure as a tree.
/// Every subclass works with sertain data from the CurveType class.
/// The whole tree is employed then in AbstractItemMoodel for QTreeView
class TreeEntry: public QObject
{
public:
  enum Column { MainFamily  = 0,
                CurveType   = 1,
                Mnemonics   = 2,
                Units       = 3,
                Min         = 4,
                Max         = 5,
                Scale       = 6,
                Continuity  = 7,
                CloseAction = 8,
                Size };

public:
  TreeEntry(Geo::Domain::CurveType::Shared curveType,
            TreeEntry*                     parent = nullptr);

  TreeEntry(TreeEntry* parent);

  TreeEntry();

  virtual
  ~TreeEntry();

  TreeEntry*
  parent() { return _parent; }

  std::vector<TreeEntry*> const
  entries() const { return _entries; }

  int
  positionOfChildEntry(TreeEntry* const childEntry) const;

  Geo::Domain::CurveType::Shared const
  curveType() const { return _curveType; }

  virtual QVariant
  data(int role, int column) const = 0;

  virtual
  bool
  setData(int role, int column, QVariant value)
  { Q_UNUSED(role); Q_UNUSED(column); Q_UNUSED(value); return false; }

  virtual QWidget*
  delegateWidget(int column) const;

  virtual void
  setDataFromWidget(QWidget* editor, QModelIndex const& index,
                    QAbstractItemModel* model)
  { Q_UNUSED(editor); Q_UNUSED(index); Q_UNUSED(model); }

  virtual void
  setConnection(Geo::Database::Connections::Connection::Shared connection);

protected:
  TreeEntry* _parent;

  Geo::Domain::CurveType::Shared _curveType;

  Geo::Database::Connections::Connection::Shared _connection;

  std::vector<TreeEntry*> _entries;
};

//
}
}
}
}
#endif // Geo_TypeSystem_TreeWrapper_TreeEntry_hpp
