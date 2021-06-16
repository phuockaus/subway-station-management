/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dbLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_DBLIB_H
#define DSA191_A1_DBLIB_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <math.h>

#include "dsaLib.h"

/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */
struct TCity {
    // The structure to store city information
	int id;
	string name;
};

struct TLine {
    // The structure to store line information
	int id;
	int city_id;
	string name;
};

struct TTrack {
    // The structure to store track information
	int id;
	int city_id;
	string geometry;
};
struct TStation {
	int id;
	string name;
	string geometry;
	int city_id;
	
};
struct TStationline{
	int id;
	int station_id;
	int line_id;
	int city_id;
};

class TDataset {
    // This class can be a container that help you manage your tables
private:
	L1List <TCity> *tcity;
	L1List <TLine> *tline;
	L1List <TTrack> *ttrack;
	L1List <TStation> *tstation;
	L1List<TStationline> *tstationline;
public:
	TDataset() {
		tcity = new(L1List<TCity>);
		tline = new(L1List<TLine>);
		ttrack = new(L1List<TTrack>);
		tstation = new(L1List<TStation>);
		tstationline = new(L1List< TStationline>);		
	}
	~TDataset();
	
	int add_city(TCity city);
	void find_city(string name, int &n);

	int add_line(TLine line);
	int count_lines();
	void count_lines_of_city(string name, int &count);
	void list_line_in_city(string name, int* arr, int &count);
	
	int add_track(TTrack track);

	int add_station(TStation station);
	void list_station_in_city(string name, int* arr, int &count);
	void list_station_in_line(int line_id, int* arr, int &count);
	void find_station(string name, int &n);
	void find_station_in_track(int a, int b, int &c);
	void insert_station(TDataset* dataset, string line, int &n);
	void remove_station(TDataset* dataset, int a, int &n);
	int delete_station_from_line(int index);
	int delete_station(int index);
	void update_station(TDataset* dataset, int id, string str, int &result);
	int update_information(TStation station, int index);
	void remove_station_from_line(TDataset* dataset, int id_station, int id_line, int &result);
	void insert_station_to_line(TDataset* dataset, int id_station, int id_line, int pos, int &result);
	int count_stationline();
	int insert_stationline(TStationline tstationline, int index);

	int add_station_line(TStationline station_line);
};


// Please add more or modify as needed
void LoadCity(void* &);
void LoadLine(void* &);
void LoadTrack(void* &);
void LoadStation(void* &);
void LoadStationline(void* &);
void removeItem(string &);
void getCityID(TCity &, string, int &);
void getnumCityInLines(TLine &, int &, int);
void getlistStation(TStation &, int, int*, int &);
void getlistLine(TLine &, int, int*, int &);
void getlistStationOfLine(TStationline &, int, int*, int &);
void getfirstStationID(TStation &, string, int &, bool &);
void getfirstCityID(TCity &, string, int &, bool &);
void getTrackGeometry(TTrack &, string&, int);
void getStationGeometry(TStation &, string&, int);
void getGeometryArray(string, string*, int &);
string getGeometry(string);
void getMaxStationID(TStation &, int &);
void getIndexOfStation(TStationline &, int, bool &, int &);
void getIndexStation(TStation &, int id, bool &, int &);
void getIndexStationAndLine(TStationline &, int , int , bool &, int &);

void LoadData(void* &);
void ReleaseData(void* &);

#endif //DSA191_A1_DBLIB_H
