// SPDX-FileCopyrightText: 2023 Pollux authors <https://github.com/polluxio/pollux-payload/blob/main/AUTHORS>
// SPDX-License-Identifier: Apache-2.0
// Inspired by:
// https://github.com/Swistusmen/Particle-Swarm-Optimization

#include <fstream>
#include <vector>
#include <functional>
#include <array>
#include <string>

void SavePoints(std::vector<std::vector<double>> points, std::function<double(double, double)> fun,
	std::string filename)
{
	std::ofstream file;
	//file.open("../../Viewer/"+filename);
	file.open("/home/nonoc/"+filename);
	for (int i = 0; i < points.size(); i++)
	{
		file << points[i][0] << " " << points[i][1] << " " << fun(points[i][0], points[i][1]) << "\n";
	}
	file.flush();
	file.close();
}
