#include "Globals.hpp"


#define define_property(name, value)  \
  const std::string globals::name = value; \
  const QString qglobals::name = value;

define_property(ORGANISATION_NAME, "mapret")
define_property(APPLICATION_NAME,  "Modelviewer")
define_property(SHORT_DESCRIPTION, "An application which can display many 3d file formats, developed in C++.")
define_property(LICENSE_NOTICE,
R"(Modelviewer, an application to display various 3d file formats.
Copyright (C) 2019  Markus Prettner

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.)")

#undef define_property
