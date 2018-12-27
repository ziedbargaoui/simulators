/*
 * LiveTraffic.cpp
 *
 *  Created on: Dec 25, 2018
 *      Author: zied
 */

#include "LiveTraffic.h"

LiveTraffic::LiveTraffic() {
	// TODO Auto-generated constructor stub

}

LiveTraffic::~LiveTraffic() {
	// TODO Auto-generated destructor stub
}

float LiveTraffic::getLongitude() const {
	return longitude;
}

namespace
{
    std::size_t callback(
            const char* in,
            std::size_t size,
            std::size_t num,
            std::string* out)
    {
        const std::size_t totalBytes(size * num);
        out->append(in, totalBytes);
        return totalBytes;
    }
}


void LiveTraffic::fetchLiveData() {

    const std::string url("https://opensky-network.org/api/states/all?icao24=70c0ee");

    CURL* curl = curl_easy_init();

    // Set remote URL.
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    // Don't bother trying IPv6, which would increase DNS resolution time.
    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

    // Don't wait forever, time out after 10 seconds.
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);

    // Follow HTTP redirects if necessary.
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    // Response information.
    long httpCode(0);
    std::unique_ptr<std::string> httpData(new std::string());

    // Hook up data handling function.
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

    // Hook up data container (will be passed as the last parameter to the
    // callback handling function).  Can be any pointer type, since it will
    // internally be passed as a void pointer.
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());

    // Run our HTTP GET command, capture the HTTP response code, and clean up.
    curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    curl_easy_cleanup(curl);

    if (httpCode != CURLE_HTTP_RETURNED_ERROR)
    {
        std::cout << "\nGot successful response from " << url << std::endl;

        // Response looks good - done using Curl now.  Try to parse the results
        // and print them out.
        Json::Value jsonData;
        Json::Reader jsonReader;

        if (jsonReader.parse(*httpData.get(), jsonData))
        {
            std::cout << "Successfully parsed JSON data" << std::endl;
            std::cout << "\nJSON data received:" << std::endl;
            std::cout << jsonData.toStyledString() << std::endl;

            const std::size_t unixTimeMs(
                    jsonData["time"].asUInt64());
            const std::string timeString(jsonData["time"].asString());

            std::cout << "Natively parsed:" << std::endl;
            std::cout << "\tUnix timeMs: " << unixTimeMs << std::endl;

    		setFlight(jsonData["states"][0][1].asString());
    		setCountry(jsonData["states"][0][2].asString());
    		setLongitude(jsonData["states"][0][5].asDouble() );
    		setLatitude(jsonData["states"][0][6].asDouble());
    		setVerticalRate(jsonData["states"][0][11].asDouble());
    		setGeoAltitude(jsonData["states"][0][13].asDouble());

            std::cout << std::endl;
        }
        else
        {
            std::cout << "Could not parse HTTP data as JSON" << std::endl;
            std::cout << "HTTP data was:\n" << *httpData.get() << std::endl;
         }
    }
    else
    {
        std::cout << "Couldn't GET from " << url << " - exiting" << std::endl;
     }

/*
	http_client client(U("https://opensky-network.org/"));

	http_response response;

	// Build request URI and start the request.
	uri_builder builder(U("/api/states/all"));
	// builder.append_query(U("time"), U("1545746400"));
	// builder.append_query(U("icao24"), U("abd9d9"));

	response = client.request(methods::GET, builder.to_string()).get();

	json::value flight_live_data = response.extract_json().get();

	if (!flight_live_data[U("states")].is_null()) {
		// && flight_live_data[U("states")][0][6]!= NULL && flight_live_data[U("states")][0][5] != NULL
		json::value data = flight_live_data[U("states")][0];

		std::cout << "flight data: " << data << "\n";

		setFlight(data[1].as_string());
		setCountry(data[2].as_string());
		setLongitude(data[5].as_double());
		setLatitude(data[6].as_double());
		setVerticalRate(data[11].as_double());
		setGeoAltitude(data[13].as_double());

	}else {
		throw std::runtime_error("no data");
	}
	*/
}

