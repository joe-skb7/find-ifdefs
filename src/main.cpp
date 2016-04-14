#include <params.h>
#include <parser.h>

#include <cstdlib>
#include <iostream>

using namespace std;

static void printUsage(char *app)
{
	cout << "Usage: " << app << " <def> <file>" << endl << endl
		<< "DESCRIPTION:" << endl
		<< "  Find all #ifdefs that specified definition is wrapped "
		<< "with" << endl << endl
		<< "PARAMS:" << endl
		<< "  def:   definition to check file for" << endl
		<< "  file:  file to check for definition" << endl << endl
		<< "EXAMPLE:" << endl
		<< "  $ " << app << " CONFIG_USB_GADGET "
		<< "include/configs/am43xx_evm.h" << endl;
}

int main(int argc, char *argv[])
{
	bool res;
	Params params;
	Parser parser;

	res = params.parseParams(argc, argv);
	if (!res) {
		printUsage(argv[0]);
		return EXIT_FAILURE;
	}

	res = parser.readFile(params.file());
	if (!res) {
		printUsage(argv[0]);
		return EXIT_FAILURE;
	}

	res = parser.parse(params.def());
	if (!res) {
		printUsage(argv[0]);
		return EXIT_FAILURE;
	}

	parser.printDef();
	cout << endl;
	parser.printIfdefs();

	return EXIT_SUCCESS;
}
