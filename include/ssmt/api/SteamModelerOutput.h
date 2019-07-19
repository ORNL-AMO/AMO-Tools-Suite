#ifndef AMO_TOOLS_SUITE_STEAMMODELEROUPUT_H
#define AMO_TOOLS_SUITE_STEAMMODELEROUPUT_H

class BoilerOutput {
private:
};

class DeaeratorOutput {
private:
};

class FlashTankOutput {
private:
};

class HeaderOutput {
private:
};

class HeatLossOutput {
private:
};

class PrvOutput {
private:
};

class TurbineOutput {
private:
};

/**
 * Steam Modeler output data; holds all of the resulting output data.
 */
class SteamModelerOutput {
private:
    BoilerOutput boilerOutput;
    DeaeratorOutput deaeratorOutput;
    FlashTankOutput flashTankOutput;
    HeaderOutput headerOutput;
    HeatLossOutput heatLossOutput;
    PrvOutput prvOutput;
    TurbineOutput turbineOutput;
};

#endif //AMO_TOOLS_SUITE_STEAMMODELEROUPUT_H
