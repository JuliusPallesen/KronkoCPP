#include "Kronko.h"

void print_args_help() {
	using namespace std;
	cout << "Kronko help:\n";
	cout << "--gui -g:\t\t Open scuffed interactive Kronko GUI\n";
	cout << "--input -i <path>:\t\t The input image (required)\n";
	cout << "--output -o <path>:\t\t Followed by output image path (default: ./output.jpg)\n";
	cout << "--caps -c <path>:\t\t Folder Path containing Cap images used to assemble the image\n";
	cout << "--import -i <path>:\t\t Path to a .json file containing information about previously imported bottlecaps\n";
	cout << "--mean -m:\t\t Picks colors for Caps and Image values by calculating the mean color value (slow)\n";
	cout << "--gauss -g:\t\t Picks colors for Caps and Image values by calculating a gaussian color value (watch out for glare)\n";
	cout << "--point -p:\t\t Picks colors for Caps and Image values by using color value at the center of the image (fast and bad)\n";
	cout << "--normal -n:\t\t Maps points in the image to bottlecaps in order of occurence (no consideration for max percentage)\n";
	cout << "--best -b:\t\t Maps points in the image to bottlecaps by choosing the best fitting caps first and takes maximum percentate into account\n";
	cout << "--max-percent <int>:\t\t Maximum percentage of a single bottlecap being used when using best-mapping\n";
	cout << "--contrast <double>:\t\t Value to increase or decrease the contrast of the input image\n";
	cout << "--saturation <double>:\t\t Value to increase or decrease the saturation of the input image\n";
	cout << "--quantization <int>:\t\t Color quantize image before assembling\n";
}

int main(int argc, char* argv[])
{
	bool kronkoGui = true;
	KronkoConfig cfg;

	for (int i = 1; i < argc; ++i) {
		std::string arg = argv[i];
		if (arg == "--help" || arg == "-?") {
			print_args_help();
			return 0;
		}
		if (arg == "--nogui" || arg == "-g") {
			kronkoGui = false;
		}
		else if (arg == "--caps" || arg == "-c") {
			if (i + 1 < argc) {
				cfg.capImportPaths.push_back(argv[++i]);
			}
		}
		else if (arg == "--output" || arg == "-o") {
			if (i + 1 < argc) cfg.outputFilename = argv[++i];
		}
		else if (arg == "--input" || arg == "-i") {
			if (i + 1 < argc) {
				try
				{
					cfg.img = readimGBRA((argv[++i]));
					cfg.imgOpened = true;
				}
				catch (const std::runtime_error & e)
				{
					std::cerr << e.what() << std::endl;
					return 1;
				}
			}
		}
		else if (arg == "--import" || arg == "-i") {
			if (i + 1 < argc) {
				cfg.capImport.setDB(new JsonDB(std::string(argv[++i])));
			}
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
		else if (arg == "--gauss" || arg == "-g") {
			cfg.setColorPicker(new ColorGauss());
		}
		else if (arg == "--point" || arg == "-p") {
			cfg.setColorPicker(new ColorPoint());
		}
		else if (arg == "--mean" || arg == "-m") {
			cfg.setColorPicker(new ColorAvg());
		}
		else if (arg == "--max-percent") {
			if (i + 1 < argc) cfg.capMapper.setMaxAmount(std::stoi(argv[++i]));
		}
		else if (arg == "--contrast") {
			if (i + 1 < argc) cfg.contrast = std::stod(argv[++i]);
		}
		else if (arg == "--saturation") {
			if (i + 1 < argc) cfg.saturation = std::stod(argv[++i]);
		}
		else if (arg == "--quantization") {
			if (i + 1 < argc) cfg.quantizationNumber = std::stoi(argv[++i]);
		}
		else if (arg == "--random-oriantation") {
			cfg.scramble = true;
		}
	}
	if (kronkoGui) {
		return kronkoGUI(cfg);
	}
	else {
		cfg.execConfig();
	}
	return 0;
}
