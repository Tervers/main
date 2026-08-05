/*
Modify Programming Project 8 from Chapter 5 so that it includes the following
	function:
	void find_closest_flight(int desired_time, int *departure_time,
							 int *arrival_time);

This function will find the flight whose departure time is closest to
	desired_time (expressed in minutes since midnight). It will store the
	departure and arrival times of this flight (also expressed in minutes since
	midnight) in the variables pointed to by departure_time and arrival_time,
	respectively
*/

#include <stdio.h>


void find_closest_flight(int desired_time, int *departure_time,
	int *arrival_time);


