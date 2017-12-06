#ifndef AMO_TOOLS_SUITE_MOTORDATADB_H
#define AMO_TOOLS_SUITE_MOTORDATADB_H

class MotorData;

std::vector<MotorData> SQLite::get_default_motor_data() {
	return {
			{"KTM", "sickMotor", "Best Motors 2018", "beastMotorType", 900, 3600, 1800, "fullyEnclosed", "frame no. 25",
			          360, "to be the best motor", 0, 1, 1, 1, 1.5, "fullyInsulated", 845, 136000, 28, 4.5, 1, 2, 85, 87, 89, 83,
			          10, 11, 12, 13, 400, 300, 200, 225, 75, 99, 15, 30, 200, 175},
			{"Honda", "some other motor", "Motors 2018", "someMotorType", 900, 3600, 1800, "partiallyEnclosed", "frame no. 15",
						360, "to be a good motor", 0, 1, 1, 1, 1.5, "somewhat Insulated", 845, 136000, 28, 4.5, 1, 2, 85, 87, 89, 83,
						10, 11, 12, 13, 400, 300, 200, 225, 75, 99, 15, 30, 200, 175}
	};
}


#endif //AMO_TOOLS_SUITE_MOTORDATADB_H
