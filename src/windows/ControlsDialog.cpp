#include "ControlsDialog.hpp"
#include "ui/controls.ui.h"


ControlsDialog::ControlsDialog(QWidget* parent)
  : QDialog(parent),
    ui_(new Ui::Controls)
{
  ui_->setupUi(this);
}

ControlsDialog::~ControlsDialog()
{
}
