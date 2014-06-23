#include "FlowLayout.hpp"
#include "KeywordWidget.hpp"

#include "Auxiliary/Visibility.hpp"

#include <DependencyManager/MetaSystem/MetaTypeRegistration>

extern "C" {
Geo_Widgets_PUBLIC void
registerComponent()
{
  REGISTER_TYPE(Geo::Widgets::FlowLayout);
  REGISTER_TYPE(Geo::Widgets::KeywordWidget);
}
}
