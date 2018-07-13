#ifndef AMO_TOOLS_SUITE_WALLLOSSESSURFACEDATA_H
#define AMO_TOOLS_SUITE_WALLLOSSESSURFACEDATA_H

class WallLosses;

std::vector<WallLosses> SQLite::get_default_wall_losses_surface() {
    return {
            {"Horizontal cylinders", 1.016},
            {"Longer vertical cylinders", 1.235},
            {"Vertical plates", 1.394},
            {"Horizontal plate facing up, warmer than air", 1.79},
            {"Horizontal plate facing down, warmer than air", 0.89},
            {"Horizontal plate facing up, cooler than air", 0.89},
            {"Horizontal plate facing down, cooler than air", 1.79},
    };
}

#endif //AMO_TOOLS_SUITE_WALLLOSSESSURFACEDATA_H
