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

    pqxx::result Result = Work.exec("select grz, lat, lon, address, date from fvf where (date between " + start_time + " and " + end_time + "\
                                    and (lat between " + std::to_string(begin_pos[1]) + " and " + std::to_string(end_pos[1]) + "\
                                    ) and (lon between " + std::to_string(begin_pos[0]) + " and " + std::to_string(end_pos[0]) + ")" + "\
                                    ) ORDER BY grz, date"); // ЗДЕСЬ ИЗМЕНИЛИ

    std::vector <car> cars;

    car car_temp;
    cam cam_temp;

    for (int rownum = 0; rownum < Result.size(); ++rownum)
    {
        // Нужно пройтись по строчкам:
        // если rownum == 0 , то просто cars[0].grz = Result[0][0]
        // иначе (если rownum > 0) если Result[rownum][0] отличается от grz текущего автомобиля, то создаем новый автомобиль и присваиваем ему этот grz
        // пока grz одинаковый и дата текущей и предыдущей строчек различная, создаем новую камеру в машине

        pqxx::field field = Result[rownum][0];

        if (rownum == 0) 
        {
            car_temp.grz = field.as<std::string>();
            cars.push_back(car_temp);

            field = Result[rownum][3];
            cam_temp.address = field.as<std::string>();

            //field = Result[rownum][4];
            //cam_temp.date = field.as<tm>();

            field = Result[rownum][2];
            cam_temp.coords[0] = field.as<double>();

            field = Result[rownum][1];
            cam_temp.coords[1] = field.as<double>();

            cars[0].camera.push_back(cam_temp);
        }
        else 
        {
            if (field.as<std::string>() == cars[cars.size()-1].grz) 
            {
                field = Result[rownum][3];
                cam_temp.address = field.as<std::string>();

                //field = Result[rownum][4];
                //cam_temp.date = field.as<tm>();

                field = Result[rownum][2];
                cam_temp.coords[0] = field.as<double>();

                field = Result[rownum][1];
                cam_temp.coords[1] = field.as<double>();

                cars[cars.size()-1].camera.push_back(cam_temp);

                if (cars[cars.size()-1].camera.size() >= 2) 
                {
                    fill_matrix(take_direction(cars[cars.size() - 1].camera[cars[cars.size() - 1].camera.size() - 2],
                        cars[cars.size() - 1].camera[cars[cars.size() - 1].camera.size() - 1]),
                        matrix_directions);
                }
            }
            else 
            {
                car_temp.grz = field.as<std::string>();
                cars.push_back(car_temp);

                field = Result[rownum][3];
                cam_temp.address = field.as<std::string>();

                //field = Result[rownum][4];
                //cam_temp.date = field.as<tm>();

                field = Result[rownum][2];
                cam_temp.coords[0] = field.as<double>();

                field = Result[rownum][1];
                cam_temp.coords[1] = field.as<double>();

                cars[cars.size()-1].camera.push_back(cam_temp);
            }
        }
    }

    std::cout << "Расчет трафика завершен!\n";
}

area* global::make_areas() {
    // left_down -> right_up
    //[x][y][[lon1][lat1][lon2][lat2]]

    // эта функция должна вызваться до машин, но после поиска углов
    // функция возвращает массив N*N структур area
    // В каждом area отмечены левый нижний угол [0] и правый верхний угол [1] соответствующего сектора

    double h_x = (right_up[0] - left_down[0]) / N;
    double h_y = (right_up[1] - left_down[1]) / N;

    areas = new area[N*N];

    for (int i=0; i < N; i++) {
        for (int j=0; j < N; j++) {
            areas[i*N+j].coords[0][0] = left_down[0] + j*h_x;
            areas[i*N+j].coords[0][1] = right_up[1] - (i+1)*h_y;

            areas[i*N+j].coords[1][0] = left_down[0] + (j+1)*h_x;
            areas[i*N+j].coords[1][1] = right_up[1] - i*h_y;
        }
    }

    // cout << areas[0].coords[0][0] << " and " << left_down[0] << endl;
    return areas;
}

int* global::take_direction(cam cam1, cam cam2) {
    // Нужно пройтись по массиву машин, внутри которого
    // camera[нач] , camera[кон]
    // отсеиваем ненужные результаты: если начальная и конечная координаты находятся в одном секторе, то сразу возвращаем [-1, -1]
    // иначе вернем два номера районов [нач. район, кон. район]
    // areas - глобальный
    static int previous[2] = { -1, -1 };
    int answer[2] = { -1, -1 };

    if (fabs(cam1.coords[0] - cam2.coords[0]) < 1e-14 && fabs(cam1.coords[1] - cam2.coords[1]) < 1e-14)
        return answer;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (cam1.coords[0] > areas[i * N + j].coords[0][0] && cam1.coords[0] <= areas[i * N + j].coords[1][0])
                if (cam1.coords[1] > areas[i * N + j].coords[0][1] && cam1.coords[0] <= areas[i * N + j].coords[1][1])
                {
                    answer[0] = i * N + j;
                    break;
                }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (cam2.coords[0] > areas[i * N + j].coords[0][0] && cam2.coords[0] <= areas[i * N + j].coords[1][0])
                if (cam2.coords[1] > areas[i * N + j].coords[0][1] && cam2.coords[0] <= areas[i * N + j].coords[1][1])
                {
                    answer[1] = i * N + j;
                    break;
                }

    if (answer[0] == previous[0] && answer[1] == previous[1]) {
        answer[0] = -1;
        answer[1] = -1;
    }
    else {
        previous[0] = answer[0];
        previous[1] = answer[1];
    }

    return answer;
}

void global::fill_matrix(int* directions, int matrix[][N]) {
    // В самом-самом начале матрица должна быть заполнена нулями, по главной диагонали -1
    // car.directions[0] - откуда
    // car.directions[1] - куда
    // Перемещаемся из строки в столбец
    // если машина не уехала из сектора, то из take_directions вернется direcions[0] == directions[1]

    if (directions[0] == -1 || directions[1] == -1) {
        return;
    }
    matrix[directions[0]][directions[1]] += 1;
}
