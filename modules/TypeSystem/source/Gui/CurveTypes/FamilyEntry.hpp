#pragma once

#include "TreeEntry.hpp"

#include <QtCore/QMap>
#include <QtCore/QPointer>
#include <QtXml/QDomElement>

#include "CurveTypeEntry.hpp"

namespace Geo {
namespace TypeSystem {
namespace Gui {
namespace CurveTypes {
//

// class CurveTypeEntry;

class FamilyEntry: public TreeEntry
{
public:
  FamilyEntry(QString familyName);

  virtual
  ~FamilyEntry();

  virtual QVariant
  data(int role, int column) const override;

  virtual QWidget*
  delegateWidget(int column) const override;

  void
  setDataFromWidget(QWidget*            editor,
                    QModelIndex const&  index,
                    QAbstractItemModel* model) override;

  void
  setFamily(QString family);

  QString
  getFamily() const { return _family; }

public:
  /// Fetches Family, checks if it duplicates an existing entry
  /// adds to children if not
  void
  addChild(QDomElement& domElement, CurveTypeEntry::XmlSourceType type);

  void
  addChild(Domain::CurveType::Shared curveType);

  void
  addChild();

  virtual QDomElement
  getXmlDescription(QDomDocument& doc) override;

  void
  updateCachedCurveTypeEntry(CurveTypeEntry* curveTypeEntry,
                             QString         newName);

private:
  QVariant
  getDisplayRole(int column) const;

  QVariant
  getEditRole(int column) const;

  QVariant
  getDecorationRole(int column) const;

  QVariant
  getForegroundRole(int column) const;

  Geo::TypeSystem::Gui::CurveTypes::CurveTypeEntry*
  getCachedCurveTypeEntry(QString curveTypeName);

  void
  pushInvalidCurveTypeEntry();

  void
  popInvalidCurveTypeEntry();

protected:
  QString _family;

  // prevents Family duplicates
  QMap<QString, CurveTypeEntry*> _curveTypeMap;

  QPointer<CurveTypeEntry> _invalidCurveTypeEntryStack;
};

//
}
}
}
}
