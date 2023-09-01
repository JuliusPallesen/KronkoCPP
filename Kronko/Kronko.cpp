#include "Kronko.h"

void print_args_help() {
	using namespace std;
	cout << "Kronko help:\n";
	cout << "--gui -g:\t\t Open interactive Kronko GUI\n";
	cout << "--input -i:\t\t Followed by input image path (required)\n";
	cout << "--output -o:\t\t Followed by output image path\n";
	cout << "--import:\t\t Open the import Cap GUI\n";
	cout << "--output -o:\t\t followed by output image path\n";
	cout << "--output -o:\t\t followed by output image path\n";
	cout << "--output -o:\t\t followed by output image path\n";
	cout << "--output -o:\t\t followed by output image path\n";
	cout << "--output -o:\t\t followed by output image path\n";
}

int main(int argc, char* argv[])
{
	bool importGui = false;
	bool kronkoGui = true;
	KronkoConfig cfg;
	cv::Mat img;

	for (int i = 1; i < argc; ++i) {
		std::string arg = argv[i];
		if (arg == "--help" || arg == "-?") {
			print_args_help();
		}
		if (arg == "--nogui" || arg == "-g") {
			kronkoGui = false;
		}
		else if (arg == "--import") {
			importGui = true;
		}
		else if (arg == "--output" || arg == "-o") {
			if (i + 1 < argc) cfg.outputFilename = argv[++i];
		}
		else if (arg == "--input" || arg == "-i") {
			if (i + 1 < argc) {
				try
				{
					img = readimGBRA((argv[++i]));
				}
				catch (const std::runtime_error & e)
				{
					std::cerr << e.what() << std::endl;
					return 1;
				}
				cfg.img = img;
			}
		}
		else if (arg == "--caps" || arg == "-c") {
			if (i + 1 < argc) cfg.database = new JsonDB(std::string(argv[++i]));
		}
		else if (arg == "--res" || arg == "-r") {
			if (i + 2 < argc) {
				cfg.widthRes = std::stoi(argv[i + 1]);
				cfg.heightRes = std::stoi(argv[i + 2]);
				i += 2;
			}
		}
		else if (arg == "--width" || arg == "-w") {
			if (i + 1 < argc) cfg.widthMm = std::stoi(argv[++i]);
		}
		else if (arg == "--normal" || arg == "-n") {
			cfg.capMapper.setMapMode(CAP_MAP_SIMPLE);
		}
		else if (arg == "--best" || arg == "-b") {
			cfg.capMapper.setMapMode(CAP_MAP_HIST);
		}
		else if (arg == "--square-layout" || arg == "-s") {
			cfg.layouter = new SquareLayouter();
		}
		else if (arg == "--triangular-layout" || arg == "-t") {
			cfg.layouter = new TriangleLayouter();
		}
		else if (arg == "--gauss") {
			cfg.colorPicker = new ColorGauss();
		}
		else if (arg == "--point" || arg == "-p") {
			cfg.colorPicker = new ColorPoint();
		}
		else if (arg == "--mean" || arg == "-m") {
			cfg.colorPicker = new ColorAvg();
		}
	}
	if (importGui) cfg.capImport.addFolder(""); 
	if (kronkoGui) {
		return kronkoGUI(cfg);
	}
	else {
		cfg.execConfig();
	}
	return 0;
}
