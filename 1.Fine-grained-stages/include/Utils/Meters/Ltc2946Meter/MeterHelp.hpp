#ifndef ADB_INCLUDE_UTILS_MeterHelp_HPP_
#define ADB_INCLUDE_UTILS_MeterHelp_HPP_
#include <Utils/Meters/Ltc2946Meter/Ltc2946Meter.hpp>
#include <memory>
using namespace DIVERSE_METER;
#define newEnergyMeter() std::make_shared<Ltc2946Meter>();
#endif