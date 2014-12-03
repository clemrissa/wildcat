#include "Implementation/KeywordWidget.hpp"
//#include "Implementation/FlowLayout.hpp"

#include "Auxiliary/Visibility.hpp"

#include <DependencyManager/MetaSystem/MetaTypeRegistration>

extern "C" {
Geo_Widgets_PUBLIC void
registerComponent()
{
  //REGISTER_TYPE(Geo::Widgets::FlowLayout);
  REGISTER_TYPE(Geo::Widgets::Implementation::KeywordWidget);
}
}
