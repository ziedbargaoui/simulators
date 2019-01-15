/*
 * ThreadData.h
 *
 *  Created on: Jan 5, 2019
 *      Author: zied
 */

#ifndef SRC_THREADDATA_H_
#define SRC_THREADDATA_H_

#include "LiveTraffic.h"

class ThreadData {
private:
	float longitude=0;
	float latitude=0;
	std::string flight;
	std::string country;
public:
	ThreadData();
	virtual ~ThreadData();

	float getLatitude() const {
		return latitude;
	}

	void setLatitude(float latitude = 0) {
		this->latitude = latitude;
	}

	float getLongitude() const {
		return longitude;
	}

	void setLongitude(float longitude = 0) {
		this->longitude = longitude;
	}

	const std::string& getCountry() const {
		return country;
	}

	void setCountry(const std::string& country) {
		this->country = country;
	}

	const std::string& getFlight() const {
		return flight;
	}

	void setFlight(const std::string& flight) {
		this->flight = flight;
	}

    int thread_id;
    LiveTraffic *live_traffic ;
};

#endif /* SRC_THREADDATA_H_ */
