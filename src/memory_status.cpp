#include "memory_status.hpp"
#include <be/core/memory_status.hpp>
#include <be/core/logging.hpp>
#include <be/util/binary_units.hpp>

using namespace be;

void log_memory_status() {
   auto mem_stat = system_memory_status();
   auto largest_block = largest_available_system_memory_block();

   U64 physical_total = mem_stat.physical.total;
   U64 physical_used = mem_stat.physical.total - mem_stat.physical.available;
   F64 physical_frac = physical_used / (F64)physical_total;
   physical_frac = round(physical_frac * 1000) / 10.0;

   U64 vmm_total = mem_stat.vmm.total;
   U64 vmm_used = mem_stat.vmm.total - mem_stat.vmm.available;
   F64 vmm_frac = vmm_used / (F64)vmm_total;
   vmm_frac = round(vmm_frac * 1000) / 10.0;

   be_info() << "Memory Status"
      & attr("Physical Usage") << util::binary_unit_string(physical_used) << "B / " << util::binary_unit_string(physical_total) << "B (" << physical_frac << "%)"
      & attr("Process Usage") << util::binary_unit_string(vmm_used) << "B / " << util::binary_unit_string(vmm_total) << "B (" << vmm_frac << "%)"
      & attr("Largest Free Block") << util::binary_unit_string(largest_block) << "B"
      | default_log();
}
