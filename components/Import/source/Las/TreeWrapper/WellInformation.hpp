#ifndef Geo_Import_TreeWrapper_WellInformation_hpp
#define Geo_Import_TreeWrapper_WellInformation_hpp

#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>

#include <Database/Connections/Connection>
#include <Domain/WellTrait>

#include "TreeEntry.hpp"

#include <Uni/Logging/Logging>

namespace Geo {
namespace Import {
namespace TreeWrapper {
//
class WellName: public TreeEntry
{
public:
  WellName(QSharedPointer<LasFile> lasFile,
           TreeEntry*              parent):
    TreeEntry(lasFile, parent)
  {
  }

  QVariant
  data(int role, int column) override
  {
    if (role != Qt::DisplayRole)
      return QVariant();

    switch (column) {
    case TreeEntry::Name:
      return tr("Well");
      break;

    case TreeEntry::Value:
      return _lasFile->lasRequired.wellName;
      break;

    case TreeEntry::ImportValue:
      return _lasFileToImport->lasRequired.wellName;
      break;

    default:
      return QVariant();
      break;
    }
  }

  void
  copyDataToLasToImport() override
  {
    _lasFileToImport->lasRequired.wellName =
      _lasFile->lasRequired.wellName;
  }
};

class WellStart: public TreeEntry
{
public:
  WellStart(QSharedPointer<LasFile> lasFile,
            TreeEntry*              parent):
    TreeEntry(lasFile, parent)
  {
  }

  QVariant
  data(int role, int column) override
  {
    if (role != Qt::DisplayRole)
      return QVariant();

    switch (column) {
    case TreeEntry::Name:
      return tr("Start");
      break;

    case TreeEntry::Value:
      return _lasFile->lasRequired.start;
      break;

    case TreeEntry::ImportValue:
      return _lasFileToImport->lasRequired.start;
      break;

    case TreeEntry::Units:
      return _lasFile->lasRequired.units;
      break;

    default:
      return QVariant();
      break;
    }
  }

  void
  copyDataToLasToImport() override
  {
    _lasFileToImport->lasRequired.start =
      _lasFile->lasRequired.start;
  }
};

class WellStop: public TreeEntry
{
public:
  WellStop(QSharedPointer<LasFile> lasFile,
           TreeEntry*              parent):
    TreeEntry(lasFile, parent)
  {
  }

  QVariant
  data(int role, int column) override
  {
    if (role != Qt::DisplayRole)
      return QVariant();

    switch (column) {
    case TreeEntry::Name:
      return tr("Stop");
      break;

    case TreeEntry::Value:
      return _lasFile->lasRequired.stop;
      break;

    case TreeEntry::ImportValue:
      return _lasFileToImport->lasRequired.stop;
      break;

    case TreeEntry::Units:
      return _lasFile->lasRequired.units;
      break;

    default:
      return QVariant();
      break;
    }
  }

  void
  copyDataToLasToImport() override
  {
    _lasFileToImport->lasRequired.stop =
      _lasFile->lasRequired.stop;
  }
};

class WellStep: public TreeEntry
{
public:
  WellStep(QSharedPointer<LasFile> lasFile,
           TreeEntry*              parent):
    TreeEntry(lasFile, parent)
  {
  }

  QVariant
  data(int role, int column) override
  {
    if (role != Qt::DisplayRole)
      return QVariant();

    switch (column) {
    case TreeEntry::Name:
      return tr("Step");
      break;

    case TreeEntry::Value:
      return _lasFile->lasRequired.step;
      break;

    case TreeEntry::ImportValue:
      return _lasFileToImport->lasRequired.step;
      break;

    case TreeEntry::Units:
      return _lasFile->lasRequired.units;
      break;

    default:
      return QVariant();
      break;
    }
  }

  void
  copyDataToLasToImport() override
  {
    _lasFileToImport->lasRequired.step =
      _lasFile->lasRequired.step;
  }
};

class WellNull: public TreeEntry
{
public:
  WellNull(QSharedPointer<LasFile> lasFile,
           TreeEntry*              parent):
    TreeEntry(lasFile, parent)
  {
  }

  QVariant
  data(int role, int column) override
  {
    if (role != Qt::DisplayRole)
      return QVariant();

    switch (column) {
    case TreeEntry::Name:
      return tr("Null");
      break;

    case TreeEntry::Value:
      return _lasFile->lasRequired.nullValue;
      break;

    case TreeEntry::ImportValue:
      return _lasFileToImport->lasRequired.nullValue;
      break;

    case TreeEntry::Units:
      return _lasFile->lasRequired.units;
      break;

    default:
      return QVariant();
      break;
    }
  }

  void
  copyDataToLasToImport() override
  {
    _lasFileToImport->lasRequired.nullValue =
      _lasFile->lasRequired.nullValue;
  }
};

// ---------------------

class LasRequiredGroup: public TreeEntry
{
public:
  LasRequiredGroup(QSharedPointer<LasFile> lasFile,
                   TreeEntry*              parent):
    TreeEntry(lasFile, parent)
  {
    _entries.push_back(new WellName(_lasFile, this));

    _entries.push_back(new WellStart(_lasFile, this));

    _entries.push_back(new WellStop(_lasFile, this));

    _entries.push_back(new WellStep(_lasFile, this));

    _entries.push_back(new WellNull(_lasFile, this));
  }

  QVariant
  data(int role, int column) override
  {
    if (role != Qt::DisplayRole)
      return QVariant();

    switch (column) {
    case TreeEntry::Name:
      return tr("Las Required");
      break;

    default:
      return QVariant();
      break;
    }
  }
};

class WellInfo: public TreeEntry
{
public:
  WellInfo(QSharedPointer<LasFile> lasFile,
           TreeEntry*              parent,
           int                     position):
    TreeEntry(lasFile, parent), _position(position)
  {
  }

  QVariant
  data(int role, int column) override
  {
    if (role != Qt::DisplayRole)
      return QVariant();

    QString key = _lasFile->wellInformation.keys()[_position];

    switch (column) {
    case TreeEntry::Name:
      return _lasFile->wellInformation[key].name;
      break;

    case TreeEntry::Description:
      return _lasFile->wellInformation[key].description;
      break;

    case TreeEntry::Value:
      return _lasFile->wellInformation[key].value;
      break;

    case TreeEntry::ImportValue:
      return _lasFileToImport->wellInformation[key].value;
      break;

    case TreeEntry::Units:
      return _lasFile->wellInformation[key].units;
      break;

    default:
      return QVariant();
      break;
    }
  }

  bool
  setData(int role, int column, QVariant value) override
  {
    QString key = _lasFile->wellInformation.keys()[_position];

    bool result = false;

    switch (column) {
    case TreeEntry::ImportValue: {
      _lasFileToImport->wellInformation[key].value = value.toString();

      result = true;
      break;
    }

    default:
      break;
    }

    return result;
  }

  void
  copyDataToLasToImport() override
  {
    QString key = _lasFile->wellInformation.keys()[_position];

    _lasFileToImport->wellInformation[key] =
      _lasFile->wellInformation[key];
  }

  QWidget*
  delegateWidget(int column) override
  {
    using Geo::Domain::WellTrait;

    QWidget* result = nullptr;

    if (_connection.isNull())
      return result;

    switch (column) {
    case TreeEntry::ImportValue: {
      QLineEdit* line = new QLineEdit();

      QString key = _lasFile->wellInformation.keys()[_position];
      line->setText(_lasFileToImport->wellInformation[key].value);

      result = line;
      break;
    }

    case TreeEntry::Type: {
      QComboBox* comboBox = new QComboBox();

      auto dataAccessFactory = _connection->dataAccessFactory();

      auto wellTraitAccess = dataAccessFactory->wellTraitAccess();

      QVector<WellTrait::Shared> traits = wellTraitAccess->findAll();

      for (WellTrait::Shared t : traits)
        comboBox->addItem(t->name());

      result = comboBox;

      break;
    }

    default:
      break;
    }

    return result;
  }

private:
  int _position;
};

class WellInformationGroup: public TreeEntry
{
public:
  WellInformationGroup(QSharedPointer<LasFile> lasFile,
                       TreeEntry*              parent):
    TreeEntry(lasFile, parent)
  {
    for (int i = 0; i < _lasFile->wellInformation.keys().size(); ++i)
      _entries.push_back(new WellInfo(_lasFile, this, i));
  }

  QVariant
  data(int role, int column) override
  {
    if (role != Qt::DisplayRole)
      return QVariant();

    switch (column) {
    case TreeEntry::Name:
      return tr("Well Information");
      break;

    default:
      return QVariant();
      break;
    }
  }
};

//
}
}
}

#endif // Geo_Import_TreeWrapper_WellInformation_hpp
