#ifndef AMO_TOOLS_SUITE_MOTORDATADB_H
#define AMO_TOOLS_SUITE_MOTORDATADB_H

class MotorData;

std::vector<MotorData> SQLite::get_default_motor_data() {
	return {
			{
					"GE", "X$D Ultra IEEE 841", "M9455", "NEMA Design B", 50, 1800, 1780, "TEFC", "326T", 460,
					"IEEE 841 Petroleum/Chemical", 0, 0, 0, 0, 1.15, "F", 511, 4, 615, 99.5, 5, 38, 48, 94.5, 94.7,
					94.3, 91.6, 78, 73.6, 63.3, 41.5, 147.4, 294.8, 206.4, 63.5, 25.7, 362.5, 92.9, 115.2, 2000
			},
			{
					"WEG Electric", "W22-NEMA Premium SD", "20018ET3G447", "NEMA Design B", 200, 1800, 0, "TEFC",
					"447/9T", 460, "undefined", 0, 0, 0, 0, 1.15, "undefined", 1899, 21098, 0, 0, 0, 0, 96.2, 96.2,
					95.4, 0, 85, 82, 73, 0, 582, 1455, 1396.8, 230, 0, 1564, 16, 35, 0, 0
			},
			{
					"Teco/Westinghouse", "MAX-E2/841", "HB2004", "NEMA Design B", 200, 1800, 1786, "TEFC", "447T", 460,
					"undefined", 0, 0, 0, 0, 1.15, "F", 2420, 23132, 0, 0, 0, 0, 96.2, 95.8, 95,0, 84.5, 82.5, 78.5,0,
					588, 1234.8, 705.6, 230, 46.4, 1450, 0, 0, 0, 0
			}
	};
}


#endif //AMO_TOOLS_SUITE_MOTORDATADB_H
