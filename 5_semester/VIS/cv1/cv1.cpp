#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

using namespace std;
using namespace std::chrono;

class Run {
protected:
    string RunID;
    string UserID;
    double Distance;
    system_clock::time_point StartTime;
    system_clock::time_point EndTime;
    time_t Date;

public:
    Run(string runId, string userId, double distance)
        : RunID(runId), UserID(userId), Distance(distance) {
        Date = system_clock::to_time_t(system_clock::now());
    }

    virtual void StartRun() {
        StartTime = system_clock::now() - minutes(5) - seconds(27);
        cout << "Run started." << endl;
    }

    virtual void EndRun() {
        EndTime = system_clock::now();
        cout << "Run ended." << endl;
    }

    virtual void GetRunDetails() const {
        auto start = system_clock::to_time_t(StartTime);
        auto end = system_clock::to_time_t(EndTime);
        auto duration = duration_cast<minutes>(EndTime - StartTime).count();

        cout << "Run ID: " << RunID << endl;
        cout << "User ID: " << UserID << endl;
        cout << "Distance: " << Distance << " km" << endl;
        cout << "Start Time: " << ctime(&start);
        cout << "End Time: " << ctime(&end);
        cout << "Duration: " << duration << " minutes" << endl;
    }

    virtual ~Run() {}
};

class OutdoorRun : public Run {
private:
    string Route;

public:
    OutdoorRun(string runId, string userId, double distance, string route)
        : Run(runId, userId, distance), Route(route) {}

    void GetRouteDetails() const {
        cout << "Route: " << Route << endl;
    }

    void GetRunDetails() const override {
        Run::GetRunDetails();
        GetRouteDetails();
    }
};

class TreadmillRun : public Run {
private:
    double Incline;

public:
    TreadmillRun(string runId, string userId, double distance, double incline)
        : Run(runId, userId, distance), Incline(incline) {}

    void GetInclineDetails() const {
        cout << "Incline: " << Incline << "%" << endl;
    }

    void GetRunDetails() const override {
        Run::GetRunDetails();
        GetInclineDetails();
    }
};

int main() {
    OutdoorRun outdoorRun("OR123", "UserA", 5.2, "Park Loop");
    outdoorRun.StartRun();
    outdoorRun.EndRun();
    outdoorRun.GetRunDetails();

    return 0;
}
