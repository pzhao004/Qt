/*!
 *   @author Mettler Toledo
 *   @date   2020/06/04 09:00
 */

#include "hmi/contexts/context_factory.h"

namespace context {

/** @brief     Singleton class instance initialize */
SINGLETON_CPP_FULL(ContextFactory);

void ContextFactory::initialize() {
  _context_general = nullptr;
  _context_configuration = nullptr;
  _context_sample = nullptr;
  _context_conditioning = nullptr;
  _context_calibration_ph = nullptr;
  _context_measure_ph = nullptr;
  _context_report = nullptr;
}

void ContextFactory::setContextGeneral(ContextGeneral* context) {
  std::lock_guard<std::mutex> lock(_mutex);
  _context_general = context;
}

ContextGeneral* ContextFactory::getContextGeneral() {
  std::lock_guard<std::mutex> lock(_mutex);
  return _context_general;
}

void ContextFactory::setContextConfiguration(ContextConfiguration* context) {
  std::lock_guard<std::mutex> lock(_mutex);
  _context_configuration = context;
}

ContextConfiguration* ContextFactory::getContextConfiguration() {
  std::lock_guard<std::mutex> lock(_mutex);
  return _context_configuration;
}

void ContextFactory::setContextSample(ContextSample* context) {
  std::lock_guard<std::mutex> lock(_mutex);
  _context_sample = context;
}

ContextSample* ContextFactory::getContextSample() {
  std::lock_guard<std::mutex> lock(_mutex);
  return _context_sample;
}

void ContextFactory::setContextConditioning(ContextConditioning* context) {
  std::lock_guard<std::mutex> lock(_mutex);
  _context_conditioning = context;
}

ContextConditioning* ContextFactory::getContextConditioning() {
  std::lock_guard<std::mutex> lock(_mutex);
  return _context_conditioning;
}

void ContextFactory::setContextCalibrationpH(ContextCalibrationpH* context) {
  std::lock_guard<std::mutex> lock(_mutex);
  _context_calibration_ph = context;
}

ContextCalibrationpH* ContextFactory::getContextCalibrationpH() {
  std::lock_guard<std::mutex> lock(_mutex);
  return _context_calibration_ph;
}

void ContextFactory::setContextMeasurepH(ContextMeasurepH* context) {
  std::lock_guard<std::mutex> lock(_mutex);
  _context_measure_ph = context;
}

ContextMeasurepH* ContextFactory::getContextMeasurepH() {
  std::lock_guard<std::mutex> lock(_mutex);
  return _context_measure_ph;
}

void ContextFactory::setContextReport(ContextReport* context) {
  std::lock_guard<std::mutex> lock(_mutex);
  _context_report = context;
}

ContextReport* ContextFactory::getContextReport() {
  std::lock_guard<std::mutex> lock(_mutex);
  return _context_report;
}

}  // namespace context
