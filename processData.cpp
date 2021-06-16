/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : processData.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : Implementation of main features in the assignment
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#include "processData.h"
/* TODO: You can implement methods, functions that support your data structures here.
 * */
using namespace std;

void Initialization() {
    // If you use global variables, please initialize them explicitly in this function.
}

void Finalization() {
    // Release your data before exiting
}

int CountLines(void* pData) {
	TDataset* dataset = (TDataset*)pData;
	return dataset->count_lines();
}
int CountLinesOfCity(void *pData, string name) {
	TDataset* dataset = (TDataset*)pData;
	int count;
	dataset->count_lines_of_city(name, count);
	return count;
}
void ListStationOfCity(void* pData, string name, int* arr ,int &count) {
	TDataset* dataset = (TDataset*)pData;
	dataset->list_station_in_city(name, arr, count);
}
void ListLineOfCity(void* pData, string name, int* arr, int &count) {
	TDataset* dataset = (TDataset*)pData;
	dataset->list_line_in_city(name, arr, count);
}
void ListStationOfLine(void* pData, int line_id, int *arr, int &count) {
	TDataset* dataset = (TDataset*)pData;
	dataset->list_station_in_line(line_id, arr, count);
}
int FindCity(void* pData, string name) {
	TDataset* dataset = (TDataset*)pData;
	int result = -1;
	dataset->find_city(name, result);
	return result;
}
int FindStation(void* pData, string name) {
	TDataset* dataset = (TDataset*)pData;
	int result = -1;
	dataset->find_station(name, result);
	return result;
}
int FindStationInTrack(void* pData, int id_station, int id_track) {
	TDataset* dataset = (TDataset*)pData;
	int result = -1;
	dataset->find_station_in_track(id_station, id_track, result);
	return result;
}
int InsertStation(void* pData, string line) {
	TDataset* dataset = (TDataset*)pData;
	int result = -1;
	dataset->insert_station(dataset,line,result);
	return result;
}
int RemoveStation(void* pData, int id) {
	TDataset* dataset = (TDataset*)pData;
	int result = -1;
	dataset->remove_station(dataset, id, result);
	return result;
}
int UpdateStation(void* pData, int id, string description) {
	TDataset* dataset = (TDataset*)pData;
	int result = -1;
	dataset->update_station(dataset, id, description, result);
	return result;
}
int RemoveStationFromLine(void* pData, int id_station, int id_line) {
	TDataset* dataset = (TDataset*)pData;
	int result = -1;
	dataset->remove_station_from_line(dataset, id_station, id_line, result);
	return result;
}
int InsertStationToLine(void* pData, int id_station, int id_line, int pos) {
	TDataset* dataset = (TDataset*)pData;
	int result = -1;
	dataset->insert_station_to_line(dataset, id_station, id_line, pos, result);
	return result;
}
void ProcessRequest(const char* pRequest, void* pData, void* &pOutput, int &N) {
	// TODO: Implement this function for processing a request
	// NOTE: You can add other functions to support this main process.
	//       pData is a pointer to a data structure that manages the dataset
	//       pOutput is a pointer reference. It is set to nullptr and student must allocate data for it in order to save the required output
	//       N is the size of output, must be a non-negative number

	string str = (string)pRequest;

	/* Count the number of lines in the dataset.*/
	if (str == "CL")
	{
		pOutput = new int;
		*((int*)pOutput) = CountLines(pData);
		N = 1;
	}
	/*Count the number of lines in the given city.*/
	if (str.substr(0, 3) == "CL ")
	{
		string temp = str.substr(3);
		pOutput = new int;
		*((int*)pOutput) = CountLinesOfCity(pData, temp);
		N = 1;
	}

	/*List stations of a city.*/
	if (str.substr(0, 4) == "LSC ")
	{
		string temp = str.substr(4);
		int *arr = new int[16000];
		int count;
		ListStationOfCity(pData, temp, arr, count);
		pOutput = arr;
		N = count;
	}

	/*List lines of a city.*/
	if (str.substr(0, 4) == "LLC ")
	{
		string temp = str.substr(4);
		int *arr = new int[1500];
		int count;
		ListLineOfCity(pData, temp, arr, count);
		pOutput = arr;
		N = count;
	}

	/*List stations of a line.*/
	if (str.substr(0, 4) == "LSL ")
	{
		string temp = str.substr(4);
		if (temp[0]<'0' || temp[0]>'9') return;
		int idline = stoi(temp);
		int *arr = new int[17000];
		int count;				
		ListStationOfLine(pData, idline, arr, count);
		pOutput = arr;
		N = count;
	}

	/*Find a city with the given name.*/
	if (str.substr(0, 3) == "FC ")
	{
		string temp = str.substr(3);
		pOutput = new int;
		*((int*)pOutput) = FindCity(pData ,temp);
		N = 1;
	}

	/*Find a station with the given name.*/
	if (str.substr(0, 3) == "FS ")
	{
		string temp = str.substr(3);
		if (temp[0] = '\"') {
			temp.erase(0, 1);
			temp.erase(temp.length(), 1);
		}
		pOutput = new int;
		*((int*)pOutput) = FindStation(pData, temp);
		N = 1;
	}

	/*Find the position of a station in a track.*/
	if (str.substr(0, 4) == "SLP ")
	{
		string temp = str.substr(4);
		if (temp[0]<'0' || temp[0]>'9') return;
		int id_station = stoi(temp);
		while (temp[0] != ' ') temp.erase(0, 1);
		temp.erase(0, 1);
		if (temp[0]<'0' || temp[0]>'9') return;
		int id_track = stoi(temp);

		pOutput = new int;
		*((int*)pOutput) = FindStationInTrack(pData, id_station, id_track);		
		N = 1;
	}
		
	/*Insert a station into the dataset*/
	if (str.substr(0, 3) == "IS ") {
		string line = str.substr(3);
		pOutput = new int;
		*((int*)pOutput) = InsertStation(pData, line);
		N = 1;		
	
	}
	
	/*Remove a station from the dataset*/
	if (str.substr(0, 3) == "RS ")
	{
		string temp = str.substr(3);
		if (temp[0]<'0' || temp[0]>'9') return;
		int id_station = stoi(temp);
		pOutput = new int;
		*((int*)pOutput) = RemoveStation(pData, id_station);
		N = 1;		
	}

	/*Update the information of a station with id*/
	if (str.substr(0, 3) == "US ")
	{
		string temp = str.substr(3);
		if (temp[0]<'0' || temp[0]>'9') return;
		int id_station = stoi(temp);
		while (temp[0] != ' ') temp.erase(0, 1);
		temp.erase(0, 1);
		string description = temp;
		pOutput = new int;
		*((int*)pOutput) = UpdateStation(pData, id_station, description);
		N = 1;
	}

	/*Insert a station to a line at index*/
	if (str.substr(0, 4) == "ISL ")
	{
		string temp = str.substr(4);

		if (temp[0]<'0' || temp[0]>'9') return;
		int id_station = stoi(temp);
		while (temp[0] != ' ') temp.erase(0, 1);
		temp.erase(0, 1);

		if (temp[0]<'0' || temp[0]>'9') return;
		int id_line = stoi(temp);
		while (temp[0] != ' ') temp.erase(0, 1);
		temp.erase(0, 1);

		if (temp[0]<'0' || temp[0]>'9') return;
		int pos = stoi(temp);

		pOutput = new int;
		*((int*)pOutput) = InsertStationToLine(pData, id_station, id_line, pos);
		N = 1;
	}

	/*Remove a station from a line*/
	if (str.substr(0, 4) == "RSL ")
	{
		string temp = str.substr(4);
		int id_station = stoi(temp);
		if (temp[0]<'0' || temp[0]>'9') return;
		while (temp[0] != ' ') temp.erase(0, 1);
		temp.erase(0, 1);
		if (temp[0]<'0' || temp[0]>'9') return;
		int id_line = stoi(temp);
		
		pOutput = new int;
		*((int*)pOutput) = RemoveStationFromLine(pData, id_station, id_line);
		N = 1;
		
	}
}

