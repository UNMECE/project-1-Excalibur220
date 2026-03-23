#include <iostream>
#include <iomanip>

using namespace std;

struct _capacitor
{
    double *time;
    double *voltage;
    double *current;
    double C;
};

typedef struct _capacitor Capacitor;

int main()
{
    const double dt = 1e-10;
    const double finalTime = 5e-6;
    const int numSteps = 50000;
    const double R = 1000.0;
    const double C = 100e-12;
    const double I_const = 1e-2;
    const double V0 = 10.0;

    Capacitor currentCase;
    currentCase.C = C;

    Capacitor voltageCase;
    voltageCase.C = C;

    currentCase.time = new double[numSteps + 1];
    currentCase.voltage = new double[numSteps + 1];
    currentCase.current = new double[numSteps + 1];

    voltageCase.time = new double[numSteps + 1];
    voltageCase.voltage = new double[numSteps + 1];
    voltageCase.current = new double[numSteps + 1];

    currentCase.time[0] = 0.0;
    currentCase.voltage[0] = 0.0;
    currentCase.current[0] = I_const;

    for (int i = 1; i <= numSteps; i++)
    {
        currentCase.time[i] = i * dt;
        currentCase.current[i] = I_const;
        currentCase.voltage[i] = currentCase.voltage[i - 1]
                               + (currentCase.current[i - 1] * dt) / currentCase.C;
    }

    voltageCase.time[0] = 0.0;
    voltageCase.voltage[0] = 0.0;
    voltageCase.current[0] = V0 / R;

    for (int i = 1; i <= numSteps; i++)
    {
        voltageCase.time[i] = i * dt;
        voltageCase.current[i] = voltageCase.current[i - 1]
                               - voltageCase.current[i - 1] * dt / (R * voltageCase.C);
        voltageCase.voltage[i] = V0 - voltageCase.current[i] * R;
    }

    cout << fixed << setprecision(6);

    cout << "CONSTANT CURRENT SOURCE CASE\n";
    cout << "Step\tTime(s)\t\tVoltage(V)\tCurrent(A)\n";
    for (int i = 0; i <= numSteps; i += 200)
    {
        cout << i << "\t"
             << scientific << currentCase.time[i] << "\t"
             << currentCase.voltage[i] << "\t"
             << currentCase.current[i] << "\n";
    }

    cout << "\nCONSTANT VOLTAGE SOURCE CASE\n";
    cout << "Step\tTime(s)\t\tVoltage(V)\tCurrent(A)\n";
    for (int i = 0; i <= numSteps; i += 200)
    {
        cout << i << "\t"
             << scientific << voltageCase.time[i] << "\t"
             << voltageCase.voltage[i] << "\t"
             << voltageCase.current[i] << "\n";
    }

    delete[] currentCase.time;
    delete[] currentCase.voltage;
    delete[] currentCase.current;

    delete[] voltageCase.time;
    delete[] voltageCase.voltage;
    delete[] voltageCase.current;

    return 0;
}