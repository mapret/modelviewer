#include "LicenseDialog.hpp"
#include "plaintext/license_sources.gen.hpp"
#include "ui/licenses.ui.h"


namespace
{
  const char* LICENSES[] =
  {
    plaintext::Glew,
    plaintext::Assimp,
  };
  std::vector<size_t> text_offsets;
}

LicenseDialog::LicenseDialog(QWidget* parent)
  : QDialog(parent),
    ui_(new Ui::Licenses)
{
  ui_->setupUi(this);

  std::string s;
  for (const auto& license : LICENSES)
  {
    size_t name_lenghth = 0;
    while (license[name_lenghth] != '\n')
      name_lenghth++;
    text_offsets.push_back(name_lenghth);
    ui_->lst_names->addItem(QString::fromUtf8(license, (int)name_lenghth));
  }

  QObject::connect(ui_->lst_names, SIGNAL(currentRowChanged(int)), this, SLOT(itemSelected(int)));
  ui_->txt_text->setMinimumWidth(ui_->txt_text->fontMetrics().averageCharWidth() * 80);
}

LicenseDialog::~LicenseDialog()
{
}

void LicenseDialog::itemSelected(int index)
{
  ui_->txt_text->setPlainText(QString::fromUtf8(LICENSES[index] + text_offsets[index] + 1));
}
