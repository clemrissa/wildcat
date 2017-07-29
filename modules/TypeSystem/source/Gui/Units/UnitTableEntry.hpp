#pragma once

#include <algorithm>
#include <vector>

#include <QtCore/QObject>
#include <QtCore/QSharedPointer>
#include <QtCore/QVariant>
#include <QtXml/QDomElement>

#include <Domain/Unit>

#include <Database/Connections/IConnection>
#include <Database/Mixin/ConnectionAcceptor>

class QAbstractItemModel;

namespace Geo
{

using Database::IConnection;

namespace TypeSystem
{
namespace Gui
{
namespace Units
{
//

/// @brief Composite pattern. Used to represent CurveType structure as a tree.
/// Every subclass works with sertain data from the CurveType class.
/// The whole tree is employed then in AbstractItemMoodel for QTreeView
class UnitTableEntry :
  public QObject,
  public Database::Mixin::ConnectionAcceptor
{
public:
  enum Column { Name        = 0,
                Symbol      = 1,
                Scale       = 2,
                Offset      = 3,
                Dimensions  = 4,
                CloseAction = 5,
                Size };

  enum State { Active,
               Deleted };

public:
  UnitTableEntry(Geo::Domain::Unit::Shared unit);

  UnitTableEntry();

  virtual
  ~UnitTableEntry();

  int
  positionOfChildEntry(UnitTableEntry* const childEntry) const;

  Geo::Domain::Unit::Shared const
  curveType() const { return _unit; }

  State
  getState() const { return _state; }

  virtual QVariant
  data(int role, int column) const;

  static QString
  headerData(int column);

  virtual bool
  setData(int role, int column, QVariant value)
  { Q_UNUSED(role); Q_UNUSED(column); Q_UNUSED(value); return false; }

  virtual QWidget*
  delegateWidget(int column) const;

  virtual void
  setDataFromWidget(QWidget* editor, QModelIndex const& index,
                    QAbstractItemModel* model)
  { Q_UNUSED(editor); Q_UNUSED(index); Q_UNUSED(model); }

public:
  // xml

  QDomElement
  getXmlDescription(QDomDocument& doc);

public:
  Geo::Domain::Unit::Shared
  unit() const;

  bool
  getPersisted() const { return _persisted; }

  void
  setPersisted(bool const persisted) { _persisted = persisted; }

  void
  addXmlData(QDomElement& data);

public slots:
  virtual void
  setConnection(std::shared_ptr<IConnection> connection);

  void
  switchState();

private:
  QVariant
  getDisplayOrEditRole(int column) const;

  QVariant
  getDecorationRole(int column) const;

  QVariant
  getForegroundRole(int column) const;

private:
  // UnitTableEntry* _parent;

  Geo::Domain::Unit::Shared _unit;

  State _state;

  bool _persisted;

  std::shared_ptr<IConnection> _connection;

  std::vector<UnitTableEntry*> _entries;
};

//
}
}
}
}
