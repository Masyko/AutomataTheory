%option noyywrap
%option c++
%x Geo Latitude CommaAfterLatitude Longitude AfterLongitude Height Tail Error
%{
#include <map>
#include <string>
#include <fstream>
#include <array>
#include <iostream>

bool debug_flag = false;
int line = 1;

std::map<std::string, std::multimap<std::string, std::string>> _heights;
std::array<std::string,3> storage;

const size_t latitude_index = 0;
const size_t longitude_index = 1;
const size_t height_index = 2;

void store_latitude(std::string latitude_str){
	storage[latitude_index] = latitude_str;
}

void store_longitude(std::string longitude_str){
	storage[longitude_index] = longitude_str;
}

void store_height(std::string height_str){
	storage[height_index] = height_str;
}

void clear_storage(){
	storage[latitude_index] = "";
	storage[longitude_index] = "";
	storage[height_index] = "";
}

void AddStorageList(){
	auto key_it = _heights.find(storage[height_index]);
    		if (key_it != _heights.end()) {
    			auto& value = key_it->second;
    			value.insert(std::pair{ storage[latitude_index], storage[longitude_index] });
    		}
    		else {
    			std::multimap<std::string, std::string> t;
    			t.insert(std::pair{ storage[latitude_index], storage[longitude_index] });
    			_heights.insert(std::pair{ storage[height_index], std::move(t) });
    		}
}

%}

geo "geo:"
float_number [0-9]+(\.[0-9]+)?
int_number [0-9]+
semicolon ";"
comma ","
equal "="
u "u"

%%
<INITIAL,Geo>{
^{geo} { BEGIN(Latitude); if(debug_flag) {std::cout << line << " Geo : BEGIN Latitude" << std::endl;} }
. {BEGIN(Error); if(debug_flag) {std::cout << line << " Geo : ERROR" << std::endl;} }
}

<Latitude>{
{float_number} {
    std::string latitude_str = YYText();
    double latitude = std::stod(latitude_str);
    if(latitude >= -90 && latitude <= 90){
        store_latitude(latitude_str);
        BEGIN(CommaAfterLatitude); if(debug_flag) {std::cout << line << " Latitude : BEGIN CommaAfterLatitude" << std::endl;}
    }
    else{
        BEGIN(Error); if(debug_flag) {std::cout << line << " Latitude : ERROR" << std::endl;}
    }
}
. {BEGIN(Error); if(debug_flag) {std::cout << line << " Latitude : ERROR" << std::endl;} }
}

<CommaAfterLatitude>{
{comma} {BEGIN(Longitude); if(debug_flag) {std::cout << line << " CommaAfterLatitude : BEGIN Longitude" << std::endl;} }
. {clear_storage(); BEGIN(Error); if(debug_flag) {std::cout << line << " CommaAfterLatitude : ERROR" << std::endl;} }
}


<Longitude>{
{float_number} {
    std::string longitude_str = YYText();
    double longitude = std::stod(longitude_str);
    if(longitude >= -180 && longitude <= 180){
        store_longitude(longitude_str);
        BEGIN(AfterLongitude); if(debug_flag) {std::cout << line << " Longitude : BEGIN AfterLongitude" << std::endl;}
    }
    else{
        clear_storage(); BEGIN(Error); if(debug_flag) {std::cout << line << " Longitude : ERROR" << std::endl;}
    }
}
. { clear_storage();BEGIN(Error); if(debug_flag) {std::cout << line << " Longitude : ERROR" << std::endl;} }
}

<AfterLongitude>
{
{comma} { BEGIN(Height); if(debug_flag) {std::cout << line << " AfterLongitude : BEGIN Height" << std::endl;} }
. { unput(YYText()[0]); store_height("0"); BEGIN(Tail); if(debug_flag) {std::cout << line << " AfterLongitude : BEGIN Tail" << std::endl; } }
}


<Height>{
{int_number} {
    store_height(YYText());
    BEGIN(Tail); if(debug_flag) {std::cout << line << " Height : BEGIN Tail" << std::endl;}
    }
. {clear_storage(); BEGIN(Error); {if(debug_flag) std::cout << line << " Height : ERROR" << std::endl;} }
}

<Tail>{
({semicolon}{u}{equal}{int_number})?$ { AddStorageList(); BEGIN(Geo); if(debug_flag) {std::cout << line << " Tail : Success" << std::endl;} return 1; }
. { clear_storage(); BEGIN(Error); {if(debug_flag) std::cout << line << " Tail : ERROR" << std::endl;} }
}


<Error>{
\n { BEGIN(Geo); return 0; }
. {;}
}
%%