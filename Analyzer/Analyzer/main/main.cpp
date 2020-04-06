#include "../Generator/Generator.h"
#include "../RegExAnalyzer/RegExAnalyzer.h"


int main(int argc, char* argv[]) {
	try
	{
	Generator generator("Generator\\Output\\Output.txt");
	generator.Create(5000);
	RegExAnalyzer RegEx_analyzer;
	RegEx_analyzer.analyze();
	}
	catch (const exception& __ex)
	{
		cout << __ex.what() << endl;
	}
	system("pause");
	return 0;
}