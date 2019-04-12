#include "Globals.hpp"


#define define_property(name, value)  \
  const std::string globals::name = value; \
  const QString qglobals::name = value;

define_property(ORGANISATION_NAME, "mapret")
define_property(APPLICATION_NAME,  "Modelviewer")
define_property(SHORT_DESCRIPTION, "An application which can display many 3d file formats, developed in C++.")

#undef define_property
