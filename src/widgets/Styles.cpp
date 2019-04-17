#include "Styles.hpp"
#include <QtCore/QFile>
#include <QtCore/QSettings>
#include <QtCore/QTextStream>
#include <QtWidgets/QApplication>

#include "rcc/qdarkstyle_src.h"


Styles::Styles()
{
  const static std::initializer_list<std::pair<const char*, const char*>> styles =
  {
      {"Default",    ""},
      {"QDarkStyle", "qdarkstyle/style.qss"}, //https://github.com/ColinDuquesnoy/QDarkStyleSheet
  };

  for (const auto& style : styles)
  {
    names_.push_back(style.first);
    name_mapping_[style.first] = style.second;
  }
  loadSettings();
}

const std::vector<std::string>& Styles::getNames() const
{
  return names_;
}

bool Styles::setStyle(const std::string& name)
{
  current_theme_ = name;
  if (name == "Default")
  {
    qApp->setStyleSheet("");
    saveSettings();
    return true;
  }

  auto it = name_mapping_.find(name);
  if (it == name_mapping_.end())
    return false;

  QFile f(QString::fromStdString(":/" + it->second));
  f.open(QFile::ReadOnly | QFile::Text);
  QTextStream stylesheet(&f);
  qApp->setStyleSheet(stylesheet.readAll());
  saveSettings();
  return true;
}

void Styles::saveSettings()
{
  QSettings settings;
  settings.setValue("current_style", QString::fromStdString(current_theme_));
}

void Styles::loadSettings()
{
  QSettings settings;
  auto style = settings.value("current_style", "Default").toString().toStdString();
  setStyle(style);
}
