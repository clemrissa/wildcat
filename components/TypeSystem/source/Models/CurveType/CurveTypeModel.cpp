#include "CurveTypeModel.hpp"

#include "FamilyEntry.hpp"

#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QDomText>

using Geo::TypeSystem::Models::CurveTypes::FamilyEntry;
using Geo::TypeSystem::Models::CurveTypes::TreeEntry;

using Geo::TypeSystem::Models::CurveTypes::CurveTypeModel;

CurveTypeModel::
CurveTypeModel()
{
  // for (LasFile::Shared lasFile : lasFiles)
  // _lasFileEntries.append(new LasFileEntry(lasFile));

  // TODO: load existing CurveTypes from database
}


CurveTypeModel::
~CurveTypeModel()
{
  for (TreeEntry* entry : _familyEntries)
    delete entry;
}


QVariant
CurveTypeModel::
data(const QModelIndex& index, int role) const
{
  if (!index.isValid())
    return QVariant();

  TreeEntry* entry =
    static_cast<TreeEntry*>(index.internalPointer());

  return entry->data(role, index.column());
}


QModelIndex
CurveTypeModel::
index(int row, int column, const QModelIndex& parent) const
{
  if (!parent.isValid())
    return QAbstractItemModel::createIndex(row, column,
                                           _familyEntries[row]);

  TreeEntry* entry =
    static_cast<TreeEntry*>(parent.internalPointer());

  if (entry->entries().size() == 0)
    return QModelIndex();

  return QAbstractItemModel::createIndex(row, column,
                                         entry->entries()[row]);
}


bool
CurveTypeModel::
setData(const QModelIndex& index,
        const QVariant&    value,
        int                role)
{
  if (role != Qt::EditRole)
    return false;

  auto treeEntry =
    static_cast<TreeEntry*>(index.internalPointer());

  bool result = treeEntry->setData(role, index.column(), value);

  if (result)
    emit dataChanged(index, index);

  return result;
}


QModelIndex
CurveTypeModel::
parent(const QModelIndex& index) const
{
  TreeEntry* entry =
    static_cast<TreeEntry*>(index.internalPointer());

  Q_ASSERT(entry);

  TreeEntry* parentEntry = entry->parent();

  if (parentEntry == nullptr)
    return QModelIndex();

  TreeEntry* parentParentEntry = parentEntry->parent();

  int position = 0;

  if (parentParentEntry == nullptr)
    position = getEntryPosition(parentEntry);
  else
    position = parentParentEntry->positionOfChildEntry(parentEntry);

  return QAbstractItemModel::createIndex(position, 0, parentEntry);
}


int
CurveTypeModel::
columnCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent);

  return TreeEntry::Column::Size;
}


int
CurveTypeModel::
rowCount(const QModelIndex& parent) const
{
  if (!parent.isValid())
    return _familyEntries.size();

  TreeEntry* entry =
    static_cast<TreeEntry*>(parent.internalPointer());

  return entry->entries().size();
}


QVariant
CurveTypeModel::
headerData(int             section,
           Qt::Orientation orientation,
           int             role)  const
{
  QVariant result;

  if (role != Qt::DisplayRole)
    return result;

  if (orientation == Qt::Vertical)
    return result;

  switch (section) {
  case TreeEntry::FamilyOrCurveType:
    result = tr("Family / Curve Type");
    break;

  case TreeEntry::Mnemonic:
    result = tr("Mnemonic");
    break;

  case TreeEntry::Synonims:
    result = tr("Synonims");
    break;

  case TreeEntry::Units:
    result = tr("Units");
    break;

  case TreeEntry::Min:
    result = tr("Min");
    break;

  case TreeEntry::Max:
    result = tr("Max");
    break;

  case TreeEntry::Scale:
    result = tr("Scale");
    break;

  case TreeEntry::Continuity:
    result = tr("Continuity");
    break;
  }

  return result;
}


Qt::ItemFlags
CurveTypeModel::
flags(const QModelIndex& index) const
{
  Qt::ItemFlags flags = QAbstractItemModel::flags(index);

  flags |= Qt::ItemIsEditable;

  // flags ^= Qt::ItemIsSelectable;

  return flags;
}


void
CurveTypeModel::
loadXml(QString fileName)
{
  QDomDocument doc("CurveTypes");

  QFile file(fileName);

  if (!file.open(QIODevice::ReadOnly))
    return;

  if (!doc.setContent(&file)) {
    file.close();
    return;
  }

  file.close();

  // ------

  beginResetModel();
  {
    QDomElement docElem = doc.documentElement();

    QDomNode n = docElem.firstChild();

    while (!n.isNull()) {
      // try to convert the node to an element.
      QDomElement loginfo = n.toElement();

      QDomElement mnem = loginfo.firstChildElement("CurveMnemonic");

      QDomElement family;

      // work with pair MainFamily-Family
      if (mnem.isNull())
        family = loginfo.firstChildElement("MainFamily");
      // work with Family-SubFamily
      else
        family = loginfo.firstChildElement("Family");

      //

      QString familyName = family.text();

      FamilyEntry* familyEntry = nullptr;

      if (_familyEntryMap.contains(familyName))
        familyEntry = _familyEntryMap[familyName];

      else {
        familyEntry = new FamilyEntry(loginfo);

        _familyEntryMap[familyName] = familyEntry;

        _familyEntries.append(familyEntry);
      }

      familyEntry->addChild(loginfo);

      n = n.nextSibling();
    }
  }
  endResetModel();
  //
}


void
CurveTypeModel::
saveXml(QString fileName)
{
  QDomDocument doc("CurveTypes");

  QDomElement root = doc.createElement("CurveTypes");
  doc.appendChild(root);

  for (auto e : _familyEntries)
    root.appendChild(e->getXmlDescription(doc));

  // -

  QFile file(fileName);

  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    return;

  QTextStream out(&file);

  out << doc.toString();
}


void
CurveTypeModel::
setConnection(Database::Connections::Connection::Shared connection)
{
  Q_UNUSED(connection);

  // TODO
}


void
CurveTypeModel::
onClicked(const QModelIndex& index)
{
  auto treeEntry =
    static_cast<TreeEntry*>(index.internalPointer());

  if (index.column() == TreeEntry::CloseAction
      // && index.row() != _unitEntries.size() - 1)
      ) {
    treeEntry->switchState();

    int  row = index.row();
    emit dataChanged(this->index(TreeEntry::FamilyOrCurveType, row),
                     this->index(TreeEntry::CloseAction, row));
  }
}


int
CurveTypeModel::
getEntryPosition(TreeEntry* const entry) const
{
  auto it = std::find(_familyEntries.begin(),
                      _familyEntries.end(), entry);

  return it - _familyEntries.begin();
  //
}
