#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

void mostrarMenu();
void tomaDeAsistencia();
void mostrarListado();
string obtenerEstadoDeAsistencia();

int main()
{
    mostrarMenu();
    return 0;
}

void pauseConsole()
{
    cin.ignore();
    cin.get();
}

void clearConsole()
{
#ifdef __unix__
    system("clear");
#elif __APPLE__
    system("clear");
#elif defined(_WIN32) || defined(WIN32)
    system("cls");
#endif // defined
}

void mostrarMenu()
{
    int opcion;
    bool repetir = true;

    do
    {
        clearConsole();

        cout << "\n\n\t\t\tMENU" << endl;
        cout << "\t-----------------------------------------" << endl;
        cout << "\n\t1. Tomar asistencia" << endl;
        cout << "\t2. Listado completo" << endl;
        cout << "\t0. SALIR" << endl;

        cout << "\n\tIngrese una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            tomaDeAsistencia();
            break;

        case 2:
            mostrarListado();
            break;

        case 0:
            repetir = false;
            break;
        }
    } while (repetir);
}

void tomaDeAsistencia()
{
    ifstream testOpenFile("asistencia.csv");
    bool fileExists = testOpenFile.good();
    testOpenFile.close();

    ofstream csvFile;
    csvFile.open("asistencia.csv", ofstream::app);
    if (!fileExists)
    {
        csvFile << "DNI,"
                << "Nombre/s,"
                << "Apellido/s,"
                << "Carrera,"
                << "Materia,"
                << "Fecha,"
                << "Hora,"
                << "Estado_de_la_Asistencia\n";
    }

    clearConsole();

    string dni, nombres, apellidos, carrera, materia, fecha, hora, estado;
    cout << "Ingrese el DNI: ";
    cin >> dni;
    cin.ignore();

    cout << "Ingrese el/los Nombre/s: ";
    getline(cin, nombres);

    cout << "Ingrese el/los Apellido/s: ";
    getline(cin, apellidos);

    cout << "Ingrese la Carrera: ";
    getline(cin, carrera);

    cout << "Ingrese la Materia: ";
    getline(cin, materia);

    cout << "Ingrese la Fecha: ";
    getline(cin, fecha);

    cout << "Ingrese la Hora: ";
    getline(cin, hora);

    estado = obtenerEstadoDeAsistencia();

    csvFile << dni << ","
            << nombres << ","
            << apellidos << ","
            << carrera << ","
            << materia << ","
            << fecha << ","
            << hora << ","
            << estado << "\n";

    csvFile.close();
}

string obtenerEstadoDeAsistencia()
{
    string estado;
    cout << "Ingrese el Estado de la Asistencia (Presente/Ausente): ";
    getline(cin, estado);

    while (estado != "Presente" && estado != "Ausente")
    {
        cout << "Estado de asistencia inválido. Por favor, ingrese 'Presente' o 'Ausente': ";
        getline(cin, estado);
    }

    return estado;
}

void mostrarListado()
{
    ifstream csvFile("asistencia.csv");
    if (!csvFile)
    {
        cout << "No se encontró el archivo 'asistencia.csv'" << endl;
        return;
    }

    string line;
    while (getline(csvFile, line))
    {
        cout << line << endl;
    }

    csvFile.close();
    pauseConsole();
}
