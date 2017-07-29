#pragma once

#include <algorithm>
#include <vector>

#include <QtCore/QObject>
#include <QtCore/QSharedPointer>
#include <QtCore/QVariant>
#include <QtCore/QVector>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>

#include <Domain/CurveType>

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
namespace CurveTypes
{
//

/// @brief Composite pattern. Used to represent CurveType structure as a tree.
/// Every subclass works with sertain data from the CurveType class.
/// The whole tree is employed then in AbstractItemMoodel for QTreeView
class TreeEntry
  : public QObject
  , public Database::Mixin::ConnectionAcceptor
{
public:
  enum Column { FamilyOrCurveName,
                Mnemonic,
                Synonyms,
                Units,
                Min,
                Max,
                Scale,
                Continuity,
                CloseAction,
                Size};

  enum State { Active,
               Deleted };

public:
  TreeEntry(TreeEntry* parent = nullptr);

  virtual
  ~TreeEntry();

  TreeEntry*
  parent() { return _parent; }

  QVector<TreeEntry*> const
  entries() const { return _entries; }

  int
  positionOfChildEntry(TreeEntry* const childEntry) const;

  virtual QVariant
  data(int role, int column) const = 0;

  virtual
  bool
  setData(int column, QVariant value)
  { Q_UNUSED(column); Q_UNUSED(value); return false; }

  virtual QWidget*
  delegateWidget(int column) const = 0;

  virtual void
  setDataFromWidget(QWidget*            editor,
                    QModelIndex const&  index,
                    QAbstractItemModel* model) = 0;

public:
  virtual QDomElement
  getXmlDescription(QDomDocument& doc) = 0;

public slots:
  virtual void
  setConnection(std::shared_ptr<IConnection> connection) override;

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

  std::shared_ptr<IConnection> _connection;

  QVector<TreeEntry*> _entries;

  State _state;
};

//
}
}
}
}
