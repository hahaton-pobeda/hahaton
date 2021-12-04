#pragma once
#include <iostream>
#include <pqxx/pqxx>
#include <vector>
#include <windows.system.h>
#include <ctime>

struct cam
{
    std::string address;
    double coords[2];
    tm date;
};

struct car
{
    cam* camera = nullptr;
    std::string grz;
};

class global
{
private:
    bool check(double[2], double[2]);

public:
    double left_down[2], right_up[2];

    car* cars = nullptr;

    pqxx::connection *Connection;

//-----Functions

    bool ConnectToDB();

    double distance_km(double, double, double, double);

    void calc_corners();

    void take_cars(std::string, std::string, double[2], double[2]);
};