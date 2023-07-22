/**
 * Author: Hendrik van Arragon, 2023
 * SPDX-License-Identifier: MIT
 */

#ifndef DYNAMIC_RASTER_DYNAMIC_RASTER_H
#define DYNAMIC_RASTER_DYNAMIC_RASTER_H DYNAMIC_RASTER_DYNAMIC_RASTER_H

#include <abmt/time.h>
#include <abmt/os.h>


namespace dynamic_raster{
    
extern abmt::time dyn_raster_intervals[10];

//@node:auto
//@raster: source
struct dyn_raster{
    int param_default_interval_ms = 10;
    int param_dyn_raster_num = 0;
    
    bool execute = false;
    
    void init(){
        abmt::die_if(param_dyn_raster_num < 0 && param_dyn_raster_num >= 10,
            "dyn_raster_num out of range "
        );
        dyn_raster_intervals[param_dyn_raster_num] = abmt::time::ms(param_default_interval_ms);
    }
    
    abmt::time poll(){
        execute = !execute;
        if(execute){
            return 0;
        }
        return dyn_raster_intervals[param_dyn_raster_num];
    }
};

//@node:auto
struct set_dyn_interval{
    std::string param_raster_name = "a_source";
    int param_dyn_raster_num = 0;
    int in_interval_ms = 10;
    
    void init(){
        abmt::die_if(param_dyn_raster_num < 0 && param_dyn_raster_num >= 10,
            "dyn_raster_num out of range "
        );
    }

    void tick(){
        dyn_raster_intervals[param_dyn_raster_num] = abmt::time::ms(in_interval_ms);
    }

};


} // namespace dynamic_raster

#endif // DYNAMIC_RASTER_DYNAMIC_RASTER_H
