#pragma once

#include <map>
#include <string>
#include <vector>


class Styles
{
  public:
    Styles();
    const std::vector<std::string>& getNames() const;
    bool setStyle(const std::string& name);

  private:
    std::vector<std::string> names_;
    std::map<std::string, std::string> name_mapping_;
    std::string current_theme_;

    void saveSettings();
    void loadSettings();
};
