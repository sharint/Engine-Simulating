#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<double> createVector(int* values, int size);

double simulateEngine(double I, const vector<double>& M, const vector<double>& V,
                      double overheatingTemperature, double HM, double HV, double C, double environmentTemperature) {
    double time = 0.0;
    double currentV = 0.0;
    double engineTemperature = environmentTemperature;

    while (engineTemperature < overheatingTemperature) {
        double VH = M[currentV] * HM + pow(currentV, 2) * HV;
        double VC = C * (environmentTemperature - engineTemperature);

        engineTemperature += VH - VC;
        currentV += M[currentV] / I;

        time += 1.0;
    }

    return time;
}

void runTests() {
    double I = 10.0;
    int arrM[] = { 20, 75, 100, 105, 75, 0 };
    int arrV[] = { 0, 75, 150, 200, 250, 300 };
    vector<double> M = createVector(arrM,6);
    vector<double> V = createVector(arrV,6);;
    double overheatingTemperature = 110.0;
    double HM = 0.01;
    double HV = 0.0001;
    double C = 0.1;

    double environmentTemperature;
    cout << "Введите температуру окружающей среды (в градусах Цельсия): ";
    cin >> environmentTemperature;

    double timeToOverheat = simulateEngine(I, M, V, overheatingTemperature, HM, HV, C, environmentTemperature);
    cout << "Время до перегрева: " << timeToOverheat << " сек" << endl;

    double maxPower = 0.0;
    double maxPowerSpeed = 0.0;

    for (int i = 0; i < V.size(); i++) {
        double power = M[i] * V[i] / 1000.0;
        if (power > maxPower) {
            maxPower = power;
            maxPowerSpeed = V[i];
        }
    }

    cout << "Максимальная мощность: " << maxPower << " кВт" << endl;
    cout << "Скорость коленвала при максимальной мощности: " << maxPowerSpeed << " рад/сек" << endl;
}

vector<double> createVector(int* values, int size){
    vector<double> vec;
    vec.reserve(size);
    for(int i = 0; i < size;i++){
        vec.push_back(values[i]);
    }
    return vec;
}

int main() {
    runTests();

    return 0;
}