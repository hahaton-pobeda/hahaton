#pragma once
#include <iostream>
#include <pqxx/pqxx>
#include <vector>
#include <windows.system.h>
#include <ctime>
#include <cmath>
#define N 4

struct cam
{
    std::string address;
    double coords[2];
    tm date;
};

struct car
{
    std::vector <cam> camera;
    std::string grz;
    //int directions[2]; // directions[0] - начальный сектор, directions[1] - конечный сектор, directions[0] == directions[1] == -1 => ошибка => в этом случае не учитываем машину
};

struct area
{
    double coords[2][2];
};

class global
{
private:
    bool check(double[2], double[2]);

public:

    double left_down[2], right_up[2];

    int matrix_directions[N * N][N * N] = { {0} };

    car* cars = nullptr;

    area* areas = nullptr;

    pqxx::connection *Connection;

//-----Functions

    bool ConnectToDB();

    double distance_km(double, double, double, double);

    void calc_corners();

    void take_cars(std::string start_time, std::string end_time, double* begin_pos, double* end_pos);

    area* make_areas();

    int* take_direction(cam, cam);

    void fill_matrix(int*);
};
