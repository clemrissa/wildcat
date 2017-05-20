#pragma once

#include <Domain/WellTrait>

#include <QtCore/QObject>

#include <memory>

namespace Geo {
namespace Domain {

class WellTraitAccess : public QObject
{
public:
  typedef std::shared_ptr<WellTraitAccess> Shared;

public:
  virtual
  ~WellTraitAccess()
  {}

  virtual void
  insert(WellTrait::Shared wellTrait) = 0;

  virtual void
  update(WellTrait::Shared wellTrait) = 0;

  virtual void
  remove(WellTrait::Shared wellTrait) = 0;

  virtual void
  remove(unsigned int const& uuid) = 0;

  virtual std::vector<WellTrait::Shared>
  findAll() = 0;

  virtual WellTrait::Shared
  findByPrimaryKey(unsigned int const& pk) = 0;

public:

  virtual void
  createDefaultTraits() = 0;
};
}
}
