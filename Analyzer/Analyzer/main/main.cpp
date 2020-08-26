#include "../StringGenerator/StringGenerator.h"
#include "../RegExAnalyzer/RegExAnalyzer.h"
#include "../AutomataAnalyzer/AutomataAnalyzer.h"
#include "../FlexAnalyzer/FlexAnalyzer.h"

int main(int argc, char* argv[]) {

    try {
//        StringGenerator generator("../Input/Input.txt");
//        generator.generate(10000);
        RegExAnalyzer regex_analyzer("../Input/Input.txt");
        regex_analyzer.analyze();
        Automata_Analyzer::AutomataAnalyzer automata_analyzer("../Input/Input.txt");
        automata_analyzer.analyze();
        FlexAnalyzer flex_analyzer("../Input/Input.txt");
        flex_analyzer.analyze();

        auto& RegExTimes = regex_analyzer.get_times();
        auto& AutomataTimes = automata_analyzer.get_times();
        auto& FlexTimes = flex_analyzer.get_times();

        auto RegExCount = RegExTimes.size();
        auto AutomataCount = AutomataTimes.size();
        auto FlexCount = FlexTimes.size();

        if(RegExCount != AutomataCount || RegExCount != FlexCount || AutomataCount != FlexCount){
            throw  std::invalid_argument("Times count is not equal");
        }

        std::ofstream times_file("../Times.txt", std::ios_base::trunc);
        times_file << "RegExTimes AutomataTimes FlexTimes" << std::endl;

        std::vector<std::vector<size_t>> all_times = {RegExTimes,AutomataTimes,FlexTimes};
        for(size_t i = 0; i< RegExCount; ++i){
            times_file << RegExTimes[i] << " " << AutomataTimes[i] << " " << FlexTimes[i] << std::endl;
        }

    }catch (const std::invalid_argument& __ex){
        std::cout << __ex.what() << std::endl;
    }

    system("pause");
	return 0;
}