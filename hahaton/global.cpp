#include "global.h"

bool global::check(double* begin_pos, double* end_pos)
{
    if ((begin_pos[0] > right_up[0]) || (end_pos[0] > right_up[0]))
        return false;

    if ((begin_pos[0] < left_down[0]) || (end_pos[0] < left_down[0]))
        return false;

    if ((begin_pos[1] > right_up[1]) || (end_pos[1] > right_up[1]))
        return false;

    if ((begin_pos[1] < left_down[1]) || (end_pos[1] < left_down[1]))
        return false;

    return true;
}

bool global::ConnectToDB()
{
    try
    {      
        Connection = new pqxx::connection("dbname = db1 user = rouser password = Pass1234  host = rc1c-90mkmxvku0h105em.mdb.yandexcloud.net port = 6432 sslmode = require");;
        if (Connection->is_open())
        {
            std::cout << "База успешно открыта: " << Connection->dbname() << std::endl;
            return true;
        }
        else
        {
            std::cout << "Невозможно открыть базу" << std::endl;
            return false;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return false;
    }
}

double global::distance_km(double lat1, double lon1, double lat2, double lon2) 
{
    const double radiant = 0.01745329251;
    double a = 0.5 - cos((lat2 - lat1) * radiant) / 2. + cos(lat1 * radiant) * cos(lat2 * radiant) * (1. - cos((lon2 - lon1) * radiant)) / 2.;

    return (12742 * asin(sqrt(a)));
}

void global::calc_corners()
{
    std::cout << "Расчет угловых координат...\n";

    pqxx::work Work{ *Connection };

    pqxx::result Result = Work.exec("select max(lon), max(lat) from fvf");

    pqxx::field field = Result[0][0];
    right_up[0] = field.as<double>();

    field = Result[0][1];
    right_up[1] = field.as<double>();

    std::cout << "Верхний правый: [" << right_up[0] << " : " << right_up[1] << "]" << std::endl;

    Result = Work.exec("select min(lon), min(lat) from fvf");

    field = Result[0][0];
    left_down[0] = field.as<double>();

    field = Result[0][1];
    left_down[1] = field.as<double>();

    std::cout << "Нижний левый: [" << left_down[0] << " : " << left_down[1] << "]" << std::endl;

    std::cout << "Расчет угловых координат завершен!\n";
}

void global::take_cars(std::string start_time, std::string end_time, double *begin_pos, double *end_pos)
{
    if (!check(begin_pos, end_pos))
    {
        std::cout << "Ошибка координат!\n";
        return;
    }

    std::cout << "Расчет трафика...\n";

    pqxx::work Work{ *Connection };

    pqxx::result Result = Work.exec("select grz, lat, lon, address, date from fvf where date between " + start_time + " and " + end_time + "\
                                    and (lat between " + std::to_string(begin_pos[1]) + " and " + std::to_string(end_pos[1]) + "\
                                    ) and (lon between " + std::to_string(begin_pos[0]) + " and " + std::to_string(end_pos[0]) + ")");

    cars = new car[Result.size()];

    for (int rownum = 0; rownum < Result.size(); ++rownum)
    {
        pqxx::field const field = Result[rownum][0];
        cars->grz = 
    }

    std::cout << "Расчет трафика завершен!\n";
}
