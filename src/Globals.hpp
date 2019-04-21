#pragma once

#include <string>
#include <QtCore/QString>


#define add_property(name) \
  namespace globals  { extern const std::string name; } \
  namespace qglobals { extern const QString name;     }

add_property(ORGANISATION_NAME)
add_property(APPLICATION_NAME)
add_property(SHORT_DESCRIPTION)
add_property(LICENSE_NOTICE)

#undef add_property
