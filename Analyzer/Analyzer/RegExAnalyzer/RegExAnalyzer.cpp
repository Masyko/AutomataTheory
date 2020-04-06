#include "RegExAnalyzer.h"
#include <map>
#include <vector>

RegExAnalyzer::RegExAnalyzer(string __input_file_path, string __output_file_path, string __height_file_path):
	Analyzer("RegExAnalyzer",__input_file_path,__output_file_path, __height_file_path)
{}

void RegExAnalyzer::analyze()
{
	try
	{
		open_files();

		regex Geolocation_regex ("(geo\\:)((\\-?)([0-9]+)(\\.?)([0-9]+))(\\,)((\\-?)([0-9]+)(\\.?)([0-9]+))((\\,)([0-9]+))?((\\;u\\=)([0-9]+))?");
		cmatch Result;
		string tmp_str;

		map<size_t, vector<pair<double, double>>> height_using; //высоота(ключ),координаты(широта и долгота)

		size_t latitude_index = 2;
		size_t latitude_low_limit = -90;
		size_t latitude_up_limit = 90;

		size_t longitude_index = 8;
		size_t longitude_low_limit = -180;
		size_t longitude_up_limit = 180;

		size_t height_index = 15;
		while (getline(_input_file, tmp_str))
		{
			if (regex_match(tmp_str.c_str() /*перевели строку в указатель на char*/, Result, Geolocation_regex)) {
				double latitude;
				double longitude;
				string latitude_str(Result[latitude_index]);
				istringstream latitude_ss(latitude_str);
				latitude_ss >> latitude;
				string longitude_str(Result[longitude_index]);
				istringstream longitude_ss(longitude_str);
				longitude_ss >> longitude;
				if (latitude >= -90 && latitude <= 90 && longitude >= -180 && longitude <= 180) {
					_output_file << tmp_str << " - BINGO!" << endl;

					size_t height = 0;
					if (Result[height_index].matched) {
						height = stoi(Result[height_index]);
					}
					
					auto key_it = height_using.find(height);
					if (key_it != height_using.end()) {
						auto& vec = key_it->second; //переменная вектора  которая хранится в паре с ключом
						vec.push_back({ latitude, longitude }); // записываем координаты к высоте

					}else {
						vector<pair<double, double>> temp_vec{ {latitude, longitude} };
						height_using.insert({ height, move(temp_vec) });
					}
				}
				else {
					_output_file << tmp_str << " - not suitable" << endl;
				}
			}
			else {
				_output_file << tmp_str << " - not suitable" << endl;
			}
		}
		
		for (auto&& h : height_using) { //рассматриваем ту же пару но уже разименованную
			auto& height = h.first;
			auto& coords = h.second;
			for (auto&& coord : coords) {
				_height_file << "Height : " << height << " Latitude : " << coord.first << " Longitude : " << coord.second << endl;
			}
		}


		close_files();
	}
	catch (const invalid_argument& __ex)
	{
		cout << __ex.what() << endl;
	}
}
