#include "WellTrait.hpp"

namespace Geo {
namespace Domain {

WellTrait::
WellTrait(QString name)
  : _name(name)
  , _mandatory(false)
    
{
  //
}


WellTrait::
WellTrait(QString name, bool mandatory)
  : _name(name)
  , _mandatory(mandatory)
{
  // 
}


}
}
