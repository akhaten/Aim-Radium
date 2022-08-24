#ifndef AIM_RADIUM_HPP
#define AIM_RADIUM_HPP

#include <Gui/BaseApplication.hpp>
#include <Gui/RadiumWindow/SimpleWindowFactory.hpp>
#include <Gui/Viewer/Viewer.hpp>

#include <QPainter>
#include <QPen>
#include <QPoint>

#include "ShooterFPS.hpp"

/**
 * Simple custom windows for custom KeyEvent demonstration
 */
class AimRadium : 
    public Ra::Gui::SimpleWindow
{
    // Q_OBJECT

  public:
    /// Reuse the SimpleWindow constructors
    using Ra::Gui::SimpleWindow::SimpleWindow;

    explicit AimRadium( uint w = 800, uint h = 640, QWidget* parent = nullptr ) :
        Ra::Gui::SimpleWindow::SimpleWindow( w, h, parent ) {
        //! [Initialize KeyEvent context and actions for demo window]
        //! [Initialize KeyEvent context and actions for demo window]
        // setAttribute(Qt::WA_TranslucentBackground, true);
    
        // auto viewerwidget = Widget::createWindowContainer(getViewer());
        // setCentralWidget(viewerwidget);
        
        //    auto viewer =  getViewer();
        //    shooter = new Ra::Gui::ShooterFPS(*(viewer->getCameraManipulator()));
        //    viewer->setCameraManipulator(shooter);
    
    }

    void configure() override {

        
        TO_FORWARD = getViewer()->addKeyReleaseEventAction(
            "TO_FORWARD", "Key_Z", "", "", "false", [this]( QKeyEvent* event ) {
                Ra::Gui::ShooterFPS* shooter = dynamic_cast<Ra::Gui::ShooterFPS*>(getViewer()->getCameraManipulator());
                shooter->moveToForward();
            } );

        TO_BACKWARD = getViewer()->addKeyReleaseEventAction(
            "TO_BACKWARD", "Key_S", "", "", "false", [this]( QKeyEvent* event ) {
                Ra::Gui::ShooterFPS* shooter = dynamic_cast<Ra::Gui::ShooterFPS*>(getViewer()->getCameraManipulator());
                shooter->moveToBackward();
            } );

        TO_LEFT = getViewer()->addKeyReleaseEventAction(
            "TO_LEFT", "Key_Q", "", "", "false", [this]( QKeyEvent* event ) {
                Ra::Gui::ShooterFPS* shooter = dynamic_cast<Ra::Gui::ShooterFPS*>(getViewer()->getCameraManipulator());
                shooter->moveToLeft();
            } );
            
        TO_RIGHT = getViewer()->addKeyReleaseEventAction(
            "TO_RIGHT", "Key_D", "", "", "false", [this]( QKeyEvent* event ) {
                Ra::Gui::ShooterFPS* shooter = dynamic_cast<Ra::Gui::ShooterFPS*>(getViewer()->getCameraManipulator());
                shooter->moveToRight();
            } );

    }

    //! [Manage KeyEvent reaching the window]
    private:
        //! [KeyEvent for demo window]
        // Ra::Gui::KeyMappingManager::Context m_demoContext {};

        Ra::Gui::KeyMappingManager::KeyMappingAction TO_FORWARD;
        Ra::Gui::KeyMappingManager::KeyMappingAction TO_BACKWARD;
        Ra::Gui::KeyMappingManager::KeyMappingAction TO_LEFT;
        Ra::Gui::KeyMappingManager::KeyMappingAction TO_RIGHT;
        // Ra::Gui::KeyMappingManager::KeyMappingAction JUMP;
    

    public:
    //    Ra::Gui::ShooterFPS* shooter;
};

/**
 * Define a factory that set instanciate the Demonstration Window
 */
class AimRadiumFactory : 
    public Ra::Gui::BaseApplication::WindowFactory
{
  public:
    ~AimRadiumFactory() = default;
    inline Ra::Gui::MainWindowInterface* createMainWindow() const override {
        auto window = new AimRadium();
        return window;
    }
};

#endif // AIM_RADIUM_HPP