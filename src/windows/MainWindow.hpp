#pragma once

#include "widgets/Styles.hpp"
#include <memory>
#include <QtWidgets/QMainWindow>


class GlWidget;
class QListWidgetItem;
namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  protected:
    void closeEvent(QCloseEvent* event) override;

  private:
    Styles styles_;
    std::unique_ptr<Ui::MainWindow> ui_;
    GlWidget* gl_widget_;

  private slots:
    void openFileModal();
    void exitAction();
    void fileLoaded(QString path);
    void fileLoadError(QString path, QString message);
    void setWireframeVisible(bool value);
    void resetCamera();
    void resetCameraZoom();
    void startAnimation(QListWidgetItem* item);
    void animationChanged(QString name, float duration);
    void animationUpdated(float timestamp);
    void toggleAnimation();
    void resetAnimation();
    void setAnimationTime(int value);
    void setAnimationSpeed(double value);
    void showControls();
    void showLicenses();
    void showAbout();
    void showAboutQt();
};
