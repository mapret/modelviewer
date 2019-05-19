#pragma once

#include <memory>
#include <QtWidgets/QDialog>


namespace Ui { class Controls; }

class ControlsDialog : public QDialog
{
  public:
    ControlsDialog(QWidget* parent = nullptr);
    ~ControlsDialog();

  private:
    std::unique_ptr<Ui::Controls> ui_;
};
