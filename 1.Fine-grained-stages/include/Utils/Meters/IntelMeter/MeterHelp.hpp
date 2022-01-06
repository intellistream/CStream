#ifndef ADB_INCLUDE_UTILS_MeterHelp_HPP_
#define ADB_INCLUDE_UTILS_MeterHelp_HPP_
#include <Utils/Meters/IntelMeter/IntelMeter.hpp>
#include <memory>
using namespace DIVERSE_METER;
#define newEnergyMeter() std::make_shared<IntelMeter>();
#endif