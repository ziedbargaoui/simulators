/*
 * LiveTraffic.h
 *
 *  Created on: Dec 25, 2018
 *      Author: zied
 */
#include <iostream>
#include <tgmath.h>

/*
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
*/

#include <cstdint>
#include <memory>
#include <string>

#include <curl/curl.h>
#include <jsoncpp/json/json.h>

#ifndef SRC_LIVETRAFFIC_H_
#define SRC_LIVETRAFFIC_H_


/*using namespace utility;// Common utilities like string conversions
using namespace web;// Common features like URIs.
using namespace web::http;// Common HTTP functionality
using namespace web::http::client;// HTTP client features
using namespace concurrency::streams;// Asynchronous streams
*/


class LiveTraffic {
public:
	LiveTraffic();
	virtual ~LiveTraffic();
	void fetchLiveData();

	float getBaroAltitude() const {	return baro_altitude;}

	void setBaroAltitude(float baroAltitude) {	baro_altitude = baroAltitude;}

	float getGeoAltitude() const {	return geo_altitude;}

	void setGeoAltitude(float geoAltitude) {geo_altitude = geoAltitude;	}

	float getLatitude() const {	return latitude;}

	void setLatitude(float latitude) {this->latitude = latitude;}

	float getLongitude() const {	return longitude;};

	void setLongitude(float longitude) {this->longitude = longitude;}

	float getVelocity() const {	return velocity;}

	void setVelocity(float velocity) {	this->velocity = velocity;}

	float getVerticalRate() const {	return vertical_rate;}

	void setVerticalRate(float verticalRate) {	vertical_rate = verticalRate;}

	const std::string& getCountry() const {	return country;	}

	void setCountry(const std::string& country) {this->country = country;}

	const std::string& getFlight() const {return flight;}

	void setFlight(const std::string& flight) {this->flight = flight;}

protected:
	CURL* curl;

	std::string icao24 = "00b026";
	std::string flight;
	std::string country;

	int		time_position;
	float	longitude;
	float	latitude;
	float	baro_altitude;
	float	velocity;
	float	vertical_rate;
	float	geo_altitude;
};

#endif /* SRC_LIVETRAFFIC_H_ */
