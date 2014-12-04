#include "Implementation/ConnectionSettingsWidget.hpp"
#include "Implementation/KeywordWidget.hpp"

#include "Auxiliary/Visibility.hpp"

#include <DependencyManager/MetaSystem/MetaTypeRegistration>

extern "C" {
Geo_Widgets_PUBLIC void
registerComponent()
{
  REGISTER_TYPE(Geo::Widgets::Implementation::KeywordWidget);
  REGISTER_TYPE(Geo::Widgets::Implementation::ConnectionSettingsWidget);
}
}
