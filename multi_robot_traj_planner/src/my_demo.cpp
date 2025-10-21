#include <random>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

// 随机起点终点，生成mission_random.json，32个机器人

double round2(double val) {
    return std::round(val * 100.0) / 100.0;
}

int main() {
    int N = 32;
    double xy_min = -5.0, xy_max = 5.0, theta = 1.0;
    double radius = 0.15, speed = 1.0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(xy_min, xy_max);

    json mission;
    mission["robots"] = {
        {"robot", {{"radius", radius}, {"speed", speed}}},
        {"default", {{"radius", radius}, {"speed", speed}}},
        {"seed", {{"seed", {rd()}}}}
    };

    for (int i = 0; i < N; ++i) {
        double sx = round2(dis(gen));
        double sy = round2(dis(gen));
        double gx = round2(dis(gen));
        double gy = round2(dis(gen));
        json agent = {
            {"name", "robot"},
            {"start", {sx, sy, theta}},
            {"goal", {gx, gy, theta}},
            {"radius", radius},
            {"speed", speed}
        };
        mission["agents"].push_back(agent);
    }

    std::ofstream file("Integrated-Design-Practice-C/multi_robot_traj_planner/missions/mission_random.json");
    file << mission.dump(2);
    file.close();
    return 0;
}