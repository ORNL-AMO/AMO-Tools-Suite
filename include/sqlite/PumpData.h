#ifndef AMO_TOOLS_SUITE_PUMPDATADB_H
#define AMO_TOOLS_SUITE_PUMPDATADB_H

class PumpData;
std::vector<PumpData> SQLite::get_default_pump_data() {
	return {
		     {"manufacturer", 
				"model", 
				"serialNumber", 
				"status", 
				"pumpType", 
				"shaftOrientation", 
				"shaftSealType", 
				"fluidType", 
				"priority", 
				"driveType",
				"flangeConnectionClass", 
				"flangeConnectionSize",
				"componentId", 
				"system",
				"location",
				"motorEfficiencyClass",
				2, 
				1, 
				9000, 
				2018, 
				1780, 
				33,
				5, 
				6,
				15, 
				11, 
				13, 
				250, 
				85, 
				1.5, 
				600, 
				400, 
				70, 
				20, 
				88, 
				15, 
				15, 
				15,
				33,
				33,
				33,
				33,
				33,
				33,
				33,
				33,
				33,
				33,
				33
		      }	/*
			{
					"manufacturer2", "model2", "type2", "serialNumber2", "status2", "pumpType2", "radialBearingType2",
					"thrustBearingType2", "shaftOrientation2", "shaftSealType2", "fluidType2", "priority2", "driveType2",
					"flangeConnectionClass2", "flangeConnectionSize2", 1, 2, 1, 9000, 2018, 1780, 5, 90, 6, 89, 90,
					85, 99, 15, 11, 13, 14, 0.5, 250, 85, 1.5, 600, 400, 70, 15, 20, 88, 15, 15, 15, 1
			}
			*/
	};
}


#endif //AMO_TOOLS_SUITE_PUMPDATADB_H