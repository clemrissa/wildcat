#ifndef Geo_TypeSystem_TreeWrapper_TreeEntry_hpp
#define Geo_TypeSystem_TreeWrapper_TreeEntry_hpp

#include <algorithm>
#include <vector>

#include <QtCore/QObject>
#include <QtCore/QSharedPointer>
#include <QtCore/QVariant>

#include <Domain/CurveType>

#include <Database/Connections/Connection>
#include <Database/Mixin/ConnectionAcceptor>

class QAbstractItemModel;

namespace Geo {
namespace TypeSystem {
namespace Models {
namespace CurveTypes {
//

/// @brief Composite pattern. Used to represent CurveType structure as a tree.
/// Every subclass works with sertain data from the CurveType class.
/// The whole tree is employed then in AbstractItemMoodel for QTreeView
class TreeEntry:
  public QObject,
  public Database::Mixin::ConnectionAcceptor
{
public:
  enum Column { FamilyOrCurveType,
                Mnemonic,
                Synonims,
                Units,
                Min,
                Max,
                Scale,
                Continuity,
                CloseAction,
                Size };

  enum State { Active,
               Deleted };

public:
  TreeEntry(TreeEntry* parent = nullptr);

  virtual
  ~TreeEntry();

  TreeEntry*
  parent() { return _parent; }

  std::vector<TreeEntry*> const
  entries() const { return _entries; }

  int
  positionOfChildEntry(TreeEntry* const childEntry) const;

  virtual QVariant
  data(int role, int column) const = 0;

  virtual
  bool
  setData(int role, int column, QVariant value)
  { Q_UNUSED(role); Q_UNUSED(column); Q_UNUSED(value); return false; }

  virtual QWidget*
  delegateWidget(int column) const;

  // virtual void
  // setDataFromWidget(QWidget* editor, QModelIndex const& index,
  // QAbstractItemModel* model)
  // { Q_UNUSED(editor); Q_UNUSED(index); Q_UNUSED(model); }

public slots:
  virtual void
  setConnection(Geo::Database::Connections::Connection::Shared connection)
  override;

public:
  State
  getState() const { return _state; }

  void
  switchState();

  void
  setState(State state);

protected:
  // propagates Active status update recursively to parent
  void
  setParentStateActive();

  void
  setChildState(State state);

protected:
  TreeEntry* _parent;

  Geo::Database::Connections::Connection::Shared _connection;

  std::vector<TreeEntry*> _entries;

  State _state;
};

//
}
}
}
}
#endif // Geo_TypeSystem_TreeWrapper_TreeEntry_hpp
