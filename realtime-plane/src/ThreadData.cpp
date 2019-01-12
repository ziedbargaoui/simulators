/*
 * ThreadData.cpp
 *
 *  Created on: Jan 5, 2019
 *      Author: zied
 */

#include "ThreadData.h"

ThreadData::ThreadData() {
	// TODO Auto-generated constructor stub
	live_traffic = new LiveTraffic();
}

ThreadData::~ThreadData() {
	// TODO Auto-generated destructor stub
	delete live_traffic;
}

