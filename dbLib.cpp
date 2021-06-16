/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dbLib.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#include "dbLib.h"
/* TODO: You can implement methods, functions that support your data structures here.
 *
 */
void LoadData(void* &pData) {
	pData = new TDataset();
	LoadCity(pData);
	LoadLine(pData);
	LoadTrack(pData);
	LoadStation(pData);
	LoadStationline(pData);
}
void ReleaseData(void* &data) {
	delete (TDataset*)data;
}
void removeItem(string &str) {
	while (str[0] != ',') {
		str.erase(0, 1);
	}
	str.erase(0, 1);
}
void LoadCity(void* &pData) {
	TDataset* dataset = (TDataset*)pData;
	TCity tempCity;
	ifstream fileInput("cities.csv");
	string line;
	getline(fileInput, line);
	while (getline(fileInput, line)) {
		if (line == "") break;
		tempCity.id = stoi(line);
		line = line.substr(line.find(',') + 1);
		tempCity.name = line.substr(0, line.find(','));
		dataset->add_city(tempCity);
	}
	fileInput.close();
}
void LoadLine(void* &pData) {
	TDataset* dataset = (TDataset*)pData;
	TLine tempLine;
	ifstream fileInput("lines.csv");
	string line;
	getline(fileInput, line);
	while (getline(fileInput, line)) {
		if (line == "") break;
		tempLine.id = stoi(line);
		line = line.substr(line.find(',') + 1);
		tempLine.city_id = stoi(line);
		line = line.substr(line.find(',') + 1);
		if (line.at(0) == '"') {
			tempLine.name = line.substr(1, line.find_last_of('"') - 1);
			line = line.substr(line.find_last_of('"') + 2);
		}
		else tempLine.name = line.substr(0, line.find(','));
		dataset->add_line(tempLine);
	}
	fileInput.close();
}
void LoadTrack(void* &pData) {
	TDataset* dataset = (TDataset*)pData;
	ifstream fileInput("tracks.csv");
	TTrack tempTrack;
	string line;
	getline(fileInput, line);
	while (getline(fileInput, line)) {
		if (line == "") break;

		tempTrack.id = stoi(line);
		removeItem(line);

		if (line.at(0) == '"') {
			tempTrack.geometry = line.substr(1, line.find_last_of('"') - 1);
			line = line.substr(line.find_last_of('"') + 2);
		}
		else {
			tempTrack.geometry = "";
			removeItem(line);
		}
		for (int i = 0; i < 4; i++) {
			removeItem(line);
		}
		tempTrack.city_id = stoi(line);
		dataset->add_track(tempTrack);
	}
	fileInput.close();
}
void LoadStation(void* &pData) {
	TDataset* dataset = (TDataset*)pData;
	TStation tempStation;
	ifstream fileInput("stations.csv");
	string line;
	getline(fileInput, line);
	while (getline(fileInput, line)) {
		if (line == "") break;
		tempStation.id = stoi(line);
		line = line.substr(line.find(',') + 1);

		if (line.at(0) == '"') {
			tempStation.name = line.substr(1, line.find_last_of('"') - 1);
			line = line.substr(line.find_last_of('"') + 2);
		}
		else {
			tempStation.name = line.substr(0, line.find(','));
			line = line.substr(line.find(',') + 1);
		}
		tempStation.geometry = line.substr(0, line.find(','));
		for (int j = 0; j < 4; j++) {
			removeItem(line);
		}
		tempStation.city_id = stoi(line);
		dataset->add_station(tempStation);
	}
	fileInput.close();
}
void LoadStationline(void* &pData) {
	TDataset* dataset = (TDataset*)pData;
	TStationline tempStationline;
	ifstream fileInput("station_lines.csv");
	string line;
	getline(fileInput, line);
	while (getline(fileInput, line)) {
		if (line == "") break;
		tempStationline.id = stoi(line);
		line = line.substr(line.find(',') + 1);
		tempStationline.station_id = stoi(line);
		line = line.substr(line.find(',') + 1);
		tempStationline.line_id = stoi(line);
		line = line.substr(line.find(',') + 1);
		tempStationline.city_id = stoi(line);
		line = line.substr(line.find(',') + 1);
		dataset->add_station_line(tempStationline);
	}
	fileInput.close();
}
void getCityID(TCity &city, string name, int &id) {
	if (city.name == name) id = city.id;
}
void getnumCityInLines(TLine &line, int &count, int id) {
	if (line.city_id == id) count++;
}
void getlistStation(TStation& station, int id, int *arr, int &idx) {
	if (station.city_id == id) {
		arr[idx] = station.id;	
		idx++;
	}
}
void getlistLine(TLine& line, int id, int* arr, int &idx) {
	if (line.city_id == id) {
		arr[idx] = line.id;
		idx++;
	}
}
void getlistStationOfLine(TStationline& stationline, int line_id, int* arr, int &idx) {
	if (stationline.line_id == line_id) {
		arr[idx] = stationline.station_id;
		idx++;
	}
}
void getfirstStationID(TStation & station, string name, int& id, bool& b) {
	if (station.name == name) {
		id = station.id;
		b = false;
	}
}
void getfirstCityID(TCity & city, string name, int& id, bool& b) {
	if (city.name == name) {
		id = city.id;
		b = false;
	}
}
void getTrackGeometry(TTrack & track, string& geometry, int id) {
	if (track.id == id) geometry = track.geometry;
}
void getStationGeometry(TStation &station, string& geometry, int id) {
	if (station.id == id) geometry = station.geometry;
}
void getGeometryArray(string str, string* arr, int& count) {
	str.erase(0, 11);
	int i = 0;
	while (str[0] != ')') {
		if (str[0] == ',') i++;
		else {
			arr[i] += str[0];
		}
		str.erase(0, 1);
	}
	count = i;
}
string getGeometry(string str) {
	str.erase(0, 6);
	string s = "";
	while (str[0] != ')') {
		s += str[0];
		str.erase(0, 1);
	}
	return s;
}
void getMaxStationID(TStation &station, int& id) {
	if (station.id > id) id = station.id;
}
void getIndexOfStation(TStationline &stationline, int id ,bool &b, int &index) {
	if (stationline.station_id == id) {
		b = false;
	}
	else index++;
}
void getIndexStation(TStation &station, int id, bool &b, int &index) {
	if (station.id == id) {
		b = false;
	}
	else index++;
}
void getIndexStationAndLine(TStationline &stationline, int id_station, int id_line, bool &b, int &index) {
	if (stationline.station_id == id_station && stationline.line_id == id_line) {
		b = false;
	}
	else index++;
}

TDataset::~TDataset() {
	
}
int TDataset::count_lines() {
	return (int)tline->getSize();
}
void TDataset::count_lines_of_city(string name, int &count) {
	int id = -1;
	tcity->traverse(getCityID,name,id);
	if (id != -1) {
		count = 0;
		tline->traverse(getnumCityInLines, count, id);
	}
	else count = -1;
}
void TDataset::list_station_in_city(string name, int* arr, int &idx) {
	int id_city = -1;
	tcity->traverse(getCityID, name, id_city);	
	if (id_city != -1) {
		idx = 0;
		tstation->traverse(getlistStation, id_city, arr, idx);
	}
	else idx = 0;
}
void TDataset::list_line_in_city(string name, int *arr, int &idx) {
	int id_city = -1;
	tcity->traverse(getCityID, name, id_city);
	if (id_city != -1) {
		idx = 0;
		tline->traverse(getlistLine, id_city, arr, idx);
	}
	else idx = 0;
}
void TDataset::list_station_in_line(int line_id, int* arr, int &idx) {
	idx = 0;
	tstationline->traverse(getlistStationOfLine, line_id, arr, idx);
}
void TDataset::find_city(string name, int& id) {
	bool b = 1;
	tcity->traverse(getfirstCityID, name, id , b);
}
void TDataset::find_station(string name, int& id) {
	bool b = 1;
	tstation->traverse(getfirstStationID, name, id , b);
}
void TDataset::find_station_in_track(int id_station, int id_track, int& pos) {
	string TrackGeometry;
	ttrack->traverse(getTrackGeometry, TrackGeometry, id_track);
	string StationGeometry;
	tstation->traverse(getStationGeometry, StationGeometry, id_station);
	string* arr = new string[1000];
	int count;
	getGeometryArray(TrackGeometry,arr, count);
	string result = getGeometry(StationGeometry);
	for (int i = 0; i < count; i++) {
		if (arr[i] == result) {
			pos = i;
			break;
		}
	}
}
void TDataset::insert_station(TDataset* dataset, string line, int& id) {
	tstation->traverse(getMaxStationID, id);
	id++;

	TStation tempStation;	
	tempStation.id = id;
	
	if (line.at(0) == '"') {
		tempStation.name = line.substr(1, line.find_last_of('"') - 1);
		line = line.substr(line.find_last_of('"') + 2);
	}
	else tempStation.name = line.substr(0, line.find(','));
	line = line.substr(line.find(',') + 1);

	tempStation.geometry = line.substr(0, line.find(','));
	line = line.substr(line.find(',') + 1);

	dataset->add_station(tempStation);
}
void TDataset::remove_station(TDataset* dataset, int id, int& result) {
	int index = 0;
	bool b = true;
	while (b) {
		index = 0;
		tstationline->traverse(getIndexOfStation, id, b, index);
		if (!b) {
			dataset->delete_station_from_line(index);
			b = true;
		}
		else b = false;
	}
	index = 0;
	b = true;
	tstation->traverse(getIndexStation, id, b, index);
	if (b) return;
	dataset->delete_station(index);
	result = 0;
}
void TDataset::update_station(TDataset* dataset, int id_station, string description, int &result) {
	bool b = true;
	int index = 0;
	tstation->traverse(getIndexStation, id_station, b, index);
	if (b) return;
	
	string name = description.substr(0, description.find(','));
	description = description.substr(description.find(',') + 1);

	string geometry = description.substr(0, description.find(','));
	TStation station;
	station.name = name;
	station.geometry = geometry;
	station.id = id_station;
	station.city_id = dataset->tstation->at(index).city_id;

	dataset->update_information(station, index);	
	result = 0;
}
void TDataset::remove_station_from_line(TDataset* dataset, int id_station, int id_line, int &result) {
	bool b = true;
	int index = 0;
	tstationline->traverse(getIndexStationAndLine, id_station , id_line, b, index);
	if (b) return;

	dataset->delete_station_from_line(index);
	result = 0;
}
int TDataset:: count_stationline(){
	return (int)tstationline->getSize();
}
void TDataset::insert_station_to_line(TDataset* dataset, int id_station, int id_line, int pos, int &result) {
	bool b = true;
	int index = 0;
	tstationline->traverse(getIndexStationAndLine, id_station, id_line, b, index);
	if (!b) return;

	TStationline stationline;
	stationline.station_id = id_station;
	stationline.line_id = id_line;
	if (pos > count_stationline()) return;
	dataset->insert_stationline(stationline, pos);
	result = 0;
}

int TDataset::add_city(TCity city) {
	return tcity->push_back(city);
}
int TDataset::add_line(TLine line) {
	return tline->push_back(line);
}
int TDataset::add_track(TTrack track) {
	return ttrack->push_back(track);
}
int TDataset::add_station(TStation station) {
	return tstation->push_back(station);
}
int TDataset::add_station_line(TStationline station_line) {
	return tstationline->push_back(station_line);
}
int TDataset::delete_station_from_line(int index) {
	return tstationline->remove(index);
}
int TDataset::delete_station(int index) {
	return tstation->remove(index);
}
int TDataset::update_information(TStation station, int index) {
	if (tstation->remove(index) == 0) return tstation->insert(index, station);
	else return -1;
}
int TDataset::insert_stationline(TStationline stationline, int index) {
	return tstationline->insert(index, stationline);
}