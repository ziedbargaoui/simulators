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
public:
	ThreadData();
	virtual ~ThreadData();
    int thread_id;
    LiveTraffic *live_traffic ;

	float longitude=0;
	float latitude=0;
	std::string flight;
	std::string country;
};

#endif /* SRC_THREADDATA_H_ */
