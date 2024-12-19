#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <ctime>
#include <algorithm>

// -------------------- Clase Empleado --------------------

class Empleado {
private:
    int numeroCarnet;
    std::string nombre;
    std::string fechaNacimiento;
    std::string categoria;
    int salario;
    std::string direccion;
    std::string telefono;
    std::string correo;

    // Conjunto para registrar correos únicos
    static std::set<std::string> correosRegistrados;

    // Función para verificar si el empleado es mayor de edad
    bool esMayorDeEdad(const std::string& fechaNacimiento) {
        int yearNacimiento = std::stoi(fechaNacimiento.substr(0, 4));
        time_t t = time(nullptr);
        tm* now = localtime(&t);
        return (now->tm_year + 1900 - yearNacimiento) >= 18;
    }

public:
    Empleado(int numeroCarnet, const std::string& nombre, const std::string& fechaNacimiento,
             const std::string& categoria, int salario, const std::string& direccion,
             const std::string& telefono, const std::string& correo) {

        if (!esMayorDeEdad(fechaNacimiento)) {
            std::cerr << "Error: El empleado debe ser mayor de edad.\n";
            exit(1);
        }

        if (salario < 250000 || salario > 500000) {
            this->salario = 250000;
        } else {
            this->salario = salario;
        }

        if (categoria != "Administrador" && categoria != "Operario" && categoria != "Peon") {
            std::cerr << "Error: Categoria inválida.\n";
            exit(1);
        }

        if (correosRegistrados.find(correo) != correosRegistrados.end()) {
            std::cerr << "Error: El correo ya está registrado.\n";
            exit(1);
        }

        correosRegistrados.insert(correo);

        this->numeroCarnet = numeroCarnet;
        this->nombre = nombre;
        this->fechaNacimiento = fechaNacimiento;
        this->categoria = categoria;
        this->direccion = direccion.empty() ? "San José" : direccion;
        this->telefono = telefono;
        this->correo = correo;
    }

    int getNumeroCarnet() const {
        return numeroCarnet;
    }

    std::string getNombre() const {
        return nombre;
    }

    void modificarDatos(const std::string& nuevoNombre, const std::string& nuevaDireccion,
                        const std::string& nuevoTelefono, int nuevoSalario) {
        nombre = nuevoNombre;
        direccion = nuevaDireccion;
        telefono = nuevoTelefono;
        salario = (nuevoSalario >= 250000 && nuevoSalario <= 500000) ? nuevoSalario : salario;
    }

    void mostrarInformacion() const {
        std::cout << "Numero de Carnet: " << numeroCarnet << "\n"
                  << "Nombre: " << nombre << "\n"
                  << "Fecha de Nacimiento: " << fechaNacimiento << "\n"
                  << "Categoria: " << categoria << "\n"
                  << "Salario: " << salario << "\n"
                  << "Direccion: " << direccion << "\n"
                  << "Telefono: " << telefono << "\n"
                  << "Correo: " << correo << "\n";
    }
};

// Inicialización del conjunto de correos registrados
std::set<std::string> Empleado::correosRegistrados;

// -------------------- Clase Proyecto --------------------

class Proyecto {
private:
    int codigoProyecto;
    std::string nombre;
    std::string fechaInicio;
    std::string fechaFinalizacion;

    // Conjunto para registrar nombres únicos de proyectos
    static std::set<std::string> nombresProyectos;

public:
    Proyecto(int codigoProyecto, const std::string& nombre, const std::string& fechaInicio, const std::string& fechaFinalizacion) {
        if (nombresProyectos.find(nombre) != nombresProyectos.end()) {
            std::cerr << "Error: El nombre del proyecto ya existe.\n";
            exit(1);
        }

        nombresProyectos.insert(nombre);

        this->codigoProyecto = codigoProyecto;
        this->nombre = nombre;
        this->fechaInicio = fechaInicio;
        this->fechaFinalizacion = fechaFinalizacion;
    }

    int getCodigoProyecto() const {
        return codigoProyecto;
    }

    std::string getNombre() const {
        return nombre;
    }

    void modificarDatos(const std::string& nuevoNombre, const std::string& nuevaFechaInicio,
                        const std::string& nuevaFechaFinalizacion) {
        nombre = nuevoNombre;
        fechaInicio = nuevaFechaInicio;
        fechaFinalizacion = nuevaFechaFinalizacion;
    }

    void mostrarInformacion() const {
        std::cout << "Codigo del Proyecto: " << codigoProyecto << "\n"
                  << "Nombre: " << nombre << "\n"
                  << "Fecha de Inicio: " << fechaInicio << "\n"
                  << "Fecha de Finalizacion: " << fechaFinalizacion << "\n";
    }
};

// Inicialización del conjunto de nombres de proyectos
std::set<std::string> Proyecto::nombresProyectos;

// -------------------- Función Main --------------------

int main() {
    std::vector<Empleado> empleados;
    std::vector<Proyecto> proyectos;
    std::map<int, std::vector<int>> asignaciones; // Mapa para asignar empleados a proyectos

    int opcion;

    do {
        std::cout << "\n--- Menu ---\n";
        std::cout << "1. Agregar Empleado\n";
        std::cout << "2. Agregar Proyecto\n";
        std::cout << "3. Asignar Empleado a Proyecto\n";
        std::cout << "4. Modificar Empleado\n";
        std::cout << "5. Modificar Proyecto\n";
        std::cout << "6. Reportar Empleados\n";
        std::cout << "7. Reportar Proyectos\n";
        std::cout << "8. Listar Asignaciones\n";
        std::cout << "9. Salir\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;
        std::cin.ignore();

        if (opcion == 1) {
            int carnet, salario;
            std::string nombre, fechaNacimiento, categoria, direccion, telefono, correo;

            std::cout << "Numero de Carnet: ";
            std::cin >> carnet;
            std::cin.ignore();
            std::cout << "Nombre: ";
            std::getline(std::cin, nombre);
            std::cout << "Fecha de Nacimiento (YYYY-MM-DD): ";
            std::getline(std::cin, fechaNacimiento);
            std::cout << "Categoria (Administrador/Operario/Peon): ";
            std::getline(std::cin, categoria);
            std::cout << "Salario: ";
            std::cin >> salario;
            std::cin.ignore();
            std::cout << "Direccion: ";
            std::getline(std::cin, direccion);
            std::cout << "Telefono: ";
            std::getline(std::cin, telefono);
            std::cout << "Correo: ";
            std::getline(std::cin, correo);

            empleados.emplace_back(carnet, nombre, fechaNacimiento, categoria, salario, direccion, telefono, correo);
        }

        else if (opcion == 2) {
            int codigo;
            std::string nombre, fechaInicio, fechaFinalizacion;

            std::cout << "Codigo del Proyecto: ";
            std::cin >> codigo;
            std::cin.ignore();
            std::cout << "Nombre del Proyecto: ";
            std::getline(std::cin, nombre);
            std::cout << "Fecha de Inicio (YYYY-MM-DD): ";
            std::getline(std::cin, fechaInicio);
            std::cout << "Fecha de Finalizacion (YYYY-MM-DD): ";
            std::getline(std::cin, fechaFinalizacion);

            proyectos.emplace_back(codigo, nombre, fechaInicio, fechaFinalizacion);
        }

    } while (opcion != 9);

    return 0;
}



