/*!
 *   @author Mettler Toledo
 *   @date   2019/12/09 01:28:27
 */

// delegate includes
#include <gen_hmi/component/projecthmipluginproxyprovider.h>
#include <hmi/component/projecthmiplugin.h>
#include <setup/component/setupdelegateplugin.h>
#include "hmi/contexts/context_factory.h"
#include "hmi/hamburgermenu/hamburgermenu.h"
#include "hmi/interaction/interactionstypestng.h"
#include "hmi/interaction/okcancelpopupinteractioncontext.h"
#include "setup/log_config.h"

#if defined(CHECK_MEMLEAK)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace hmi {
namespace component {


ProjectHmiPlugin::ProjectHmiPlugin(ProjectHmiPluginProxyProvider* pProvider) : _pProvider(pProvider) {
}

ProjectHmiPlugin::~ProjectHmiPlugin() { _pProvider = nullptr; }

#if 0
void ProjectHmiPlugin::systemStartInProgressImpl(bool& fRet) {
  UTILLOG(HMI, LL_BOOT, (TEXT("ProjectHmiPlugin::systemStartInProgressImpl()")));
  fRet = true;
}

void ProjectHmiPlugin::systemStartedImpl(bool& fRet) {
  UTILLOG(HMI, LL_BOOT, (TEXT("ProjectHmiPlugin::systemStartedImpl()")));
  fRet = true;
}

void ProjectHmiPlugin::systemShutdownInProgressImpl(bool& fRet) {
  UTILLOG(HMI, LL_BOOT, (TEXT("ProjectHmiPlugin::systemShutdownInProgressImpl()")) );
  fRet = true;
}

void ProjectHmiPlugin::systemShutdownImpl(bool& fRet) {
  UTILLOG(HMI, LL_BOOT, (TEXT("ProjectHmiPlugin::systemShutdownImpl()")));
  fRet = true;
}
#endif

coreex::CProxyProvider* ProjectHmiPlugin::getProxyProviderProject() { return _pProvider; }

std::unique_ptr<CompoundControllerBase> ProjectHmiPlugin::createCompoundController(ContextManager& context_manager) {
  // first way to new a object pointer
  // std::unique_ptr<CompoundControllerBase> eventFilterPointer(new hmi::ContextKeyEvent(nullptr, context_manager));
  // second way to new a object pointer
  std::unique_ptr<CompoundControllerBase> eventFilterPointer =
      std::make_unique<hmi::ContextKeyEvent>(nullptr, context_manager);
  return eventFilterPointer;
}

bool ProjectHmiPlugin::initProjectSpecificHmi(QQmlApplicationEngine& engine, ContextManager& context_manager,
                                              HamburgerMenuManager& hamburger_menu_manager,
                                              CompoundControllerBase& compound_controller_base) {
  qDebug() << &compound_controller_base << &engine;
  context::ContextGeneral* context_general_ptr;
  context::ContextConfiguration* context_configuration_ptr;
  context::ContextSample* context_sample_ptr;
  context::ContextConditioning* context_conditioning_ptr;
  context::ContextCalibrationpH* context_calibration_ph_ptr;
  context::ContextMeasurepH* context_measure_ph_ptr;
  context::ContextReport* context_report_ptr;

  context_general_ptr = new context::ContextGeneral(context_manager);
  context_configuration_ptr = new context::ContextConfiguration(context_manager);
  context_sample_ptr = new context::ContextSample(context_manager);
  context_conditioning_ptr = new context::ContextConditioning(context_manager);
  context_calibration_ph_ptr = new context::ContextCalibrationpH(context_manager);
  context_measure_ph_ptr = new context::ContextMeasurepH(context_manager);
  context_report_ptr = new context::ContextReport(context_manager);

  engine.rootContext()->setContextProperty("GENERALCXT", context_general_ptr);
  engine.rootContext()->setContextProperty("CONFIG", context_configuration_ptr);
  engine.rootContext()->setContextProperty("SAMPLE", context_sample_ptr);
  engine.rootContext()->setContextProperty("CONDITIONING", context_conditioning_ptr);
  engine.rootContext()->setContextProperty("CALIBRATION", context_calibration_ph_ptr);
  engine.rootContext()->setContextProperty("MEASURE", context_measure_ph_ptr);
  engine.rootContext()->setContextProperty("REPORT", context_report_ptr);
  engine.rootContext()->setContextProperty("MAINSCREEN", new context::ContextMainScreen(context_manager));

  context::ContextFactory::getInstance().initialize();
  context::ContextFactory::getInstance().setContextGeneral(context_general_ptr);
  context::ContextFactory::getInstance().setContextConfiguration(context_configuration_ptr);
  context::ContextFactory::getInstance().setContextSample(context_sample_ptr);
  context::ContextFactory::getInstance().setContextConditioning(context_conditioning_ptr);
  context::ContextFactory::getInstance().setContextCalibrationpH(context_calibration_ph_ptr);
  context::ContextFactory::getInstance().setContextMeasurepH(context_measure_ph_ptr);
  context::ContextFactory::getInstance().setContextReport(context_report_ptr);

  if (QFontDatabase::addApplicationFont(":/NotoSans-SemiCondensed.ttf") == -1) {
    qFatal("Failed to load font from resources");
  }
  QFontDatabase theFontDatabase;
  QStringList theStringList = theFontDatabase.families();
  QFont default_font("Noto Sans SemCond");
  QGuiApplication::setFont(default_font);

#ifdef CORE_PLATFORM_WIN32
  engine.rootContext()->setContextProperty("CONTROLPANEL", new hmi::ControlPanelContext());
  const QUrl url(QStringLiteral("qrc:/maincontrol.qml"));
  engine.load(url);
#endif
  populateHamburgerMenu(context_manager, hamburger_menu_manager);
  hmi::InteractionController* interaction_controller;
  _pProvider->getHmiProxy()->getInteractionController(interaction_controller);
  interaction_controller->registerInteractionType(model::kInteractionTypeOkCancelPopup,
                                                  []() { return new context::OkCancelPopupInteractionContext(); });
  return true;
}

void ProjectHmiPlugin::cleanupProjectSpecificHmi() {}

void ProjectHmiPlugin::populateHamburgerMenu(ContextManager& context_manager,
                                             HamburgerMenuManager& hamburger_menu_manager) {
  auto root_menu = new HamburgerMenu(QStringLiteral("root"));
  auto item_method = new HamburgerMenu(QStringLiteral("Methods"),
                                       QStringLiteral("qrc:///icons/placeholder_menuitem_pr.png"), root_menu);
  auto item_buffer = new HamburgerMenu(QStringLiteral("Buffers"),
                                       QStringLiteral("qrc:///icons/placeholder_menuitem_pr.png"), root_menu);
  auto item_sensor = new HamburgerMenu(QStringLiteral("Sensors"),
                                       QStringLiteral("qrc:///icons/placeholder_menuitem_pr.png"), root_menu);
  auto item_setting = new HamburgerMenu(QStringLiteral("Settings"),
                                        QStringLiteral("qrc:///icons/placeholder_menuitem_pr.png"), root_menu);
  auto item_maintenace = new HamburgerMenu(QStringLiteral("Maintenance"),
                                           QStringLiteral("qrc:///icons/placeholder_menuitem_pr.png"), root_menu);
  new HamburgerMenu(QStringLiteral(".Information"), QStringLiteral("qrc:///icons/placeholder_menuitem_pr.png"),
                    item_maintenace);
  new HamburgerMenu(QStringLiteral(".Service"), QStringLiteral("qrc:///icons/placeholder_menuitem_pr.png"),
                    item_maintenace);
  new HamburgerMenu(QStringLiteral(".Import/Export"), QStringLiteral("qrc:///icons/placeholder_menuitem_pr.png"),
                    item_maintenace);
  new HamburgerMenu(QStringLiteral(".Firmware Update"), QStringLiteral("qrc:///icons/placeholder_menuitem_pr.png"),
                    item_maintenace);
  new HamburgerMenu(QStringLiteral(".Firmware History"), QStringLiteral("qrc:///icons/placeholder_menuitem_pr.png"),
                    item_maintenace);
  new HamburgerMenu(QStringLiteral(".Reset"), QStringLiteral("qrc:///icons/placeholder_menuitem_pr.png"),
                    item_maintenace);
  QObject::connect(item_method, &HamburgerMenu::triggered,
                   [&context_manager]() { context_manager.push(new context::ContextMethod(context_manager), true); });
  QObject::connect(item_buffer, &HamburgerMenu::triggered,
                   [&context_manager]() { context_manager.push(new context::ContextBuffer(context_manager), true); });
  QObject::connect(item_sensor, &HamburgerMenu::triggered,
                   [&context_manager]() { context_manager.push(new context::ContextSensor(context_manager), true); });
  QObject::connect(item_setting, &HamburgerMenu::triggered,
                   [&context_manager]() { context_manager.push(new context::ContextSetting(context_manager), true); });
  hamburger_menu_manager.setRootMenuItem(root_menu);

  auto footer_menu = new HamburgerMenu(QStringLiteral("footer"));
  auto topLevel = new HamburgerMenu(QStringLiteral("Log out / Lock"),
                                    QStringLiteral("qrc:///icons/placeholder_workaction_re.png"), footer_menu);
  new HamburgerMenu(QStringLiteral("Lock"), topLevel);
  new HamburgerMenu(QStringLiteral("Log out"), topLevel);
  hamburger_menu_manager.setFooterMenuItem(footer_menu);
}

}  // namespace component
} // namespace hmi

