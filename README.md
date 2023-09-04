# Kronko - Turning Pictures into Bottlecap Art

## Table of Contents

- [Introduction](##Introduction)
- [Features](##Features)
- [Getting Started](##Getting-started)
- [Usage](##Usage)
- [Installation](##Installation)
- [Contributing](##Contributing)
- [License](##License)
- [Contact](##Contact)

## Introduction

Kronko is a C++ application I created as a fun side project to refresh my C++ and OpenCV skills. Its main purpose is to turn images into bottlecap artwork, aiming to generate templates for actual bottlecap art. However, achieving easily reproducible and recognizable results can be a bit tricky, often requiring large output images or carefully chosen input images. Kronko offers different approaches for arranging bottlecaps and selecting matching colors. In the following sections, we'll explore some examples of what Kronko can do.

## Features

Kronko is a tool designed to transform images into bottlecap artwork. Explore the following key features:

- **Interactive GUI:** Kronko offers a scuffed opencv GUI using buttonpresses to trigger certain functions.

- **Image Transformation:** Easily convert your chosen input image into bottlecap artwork.

- **Cap Image Library:** incorporate your own bottlecap images by specifying the folder path containing the caps you wish to use in your artwork.

- **Cap Information Import:** Reuse previously imported bottlecap information conveniently by importing it from a .json file. The json file can also be used to limit the amount of bottlecaps that are available as well as manually change the color value of bottlecaps.

- **Color Selection:** Customize your artwork's color scheme using various methods:
  - **Mean Color:** Calculate colors based on the mean color value of the input image (slower but precise).
  - **Gaussian Color:** Apply a Gaussian color calculation method (exercise caution with glare).
  - **Point Color:** Swiftly select colors using the center color value of the image (quick but lower quality).

- **Mapping Strategies:** Choose between two mapping strategies for arranging bottlecaps:
  - **Normal Mapping:** Map image points to bottlecaps in the order of occurrence, without considering maximum usage percentages.
  - **Best-Fit Mapping:** Prioritize the selection of the best-fitting bottlecaps while considering maximum percentage utilization.

- **Image Enhancement:** Fine-tune your input image to try achieving better results:
  - **Contrast Adjustment:** Adjust the image's contrast using a specified value.
  - **Saturation Adjustment:** Modify the image's saturation with a user-defined value.
  - **Color Quantization:** Simplify your image's color palette using color quantization before the assembly process.

With Kronko's diverse set of features, you have the power to create unique and visually captivating bottlecap artwork tailored to your preferences.

## Getting-started

Try building Kronko yourself. Kronko is dependant on [OpenCV](https://github.com/opencv/opencv) and [Niels Lohmann's JSON library](https://github.com/nlohmann/json). Not much time has been invested into making this project easily deployable on other devices yet and it likely never will, so tough luck bucko ;)

## Usage

### KronkoGUI
While its not pretty and not easy to use, KronkoGUI still offers a most of Kronkos functionality while also providing a handy preview of what's happening. KronkoGUI launches automatically when executing the .exe file. The accompanying console window gives some more insight into what's going on in the background. To supress the GUI from launchging (for example when using Kronko from the commandline) just add the --nogui parameter.

#### After opening KronkoGUI:

- Commandline Parameters effect the configuration of the GUI
- When opening the KronkoGUI you will first be asked to open an input image (.jpg/.png). 
- The "Width (mm)" slider determines the width of your output artwork (bottlecaps have a ~26mm diameter)
- The "Resolution" slider determines the width resolution of your output image. This can be handy when working with lower resolution input images.

#### Keyboard Shortcuts within KronkoGUI:

- **1, 2:** Switch between different layout options (like Square and Triangle) for arranging bottlecaps.
- **g:** Use the Gaussian Color Picker for selecting colors.
- **m:** Pick the Mean Color Picker for color selection.
- **p:** Opt for the Point Color Picker for quick color choices.
- **s:** Apply normal mapping to use bottlecaps in the order they appear.
- **h:** Use best mapping, giving priority to the best-fitting bottlecaps.
- **i:** Import a Caps folder to access a collection of bottlecap images.
- **c:** Clear the database to start fresh.
- **s:** Save the current image as your artwork.
- **b:** Load a backup image or reset the current one.
- **r:** Toggle sliders on/off to resize the KronkoGUI window as needed.
- **Esc/x:** Exit KronkoGUI.

With KronkoGUI and these handy keyboard shortcuts, you'll have everything you need for your creative project.

### Command-Line Arguments
Kronko accepts the following command-line arguments to customize its behavior:

- `--gui` or `-g`: Opens the scuffed interactive Kronko GUI.
- `--input <path>` or `-i <path>` (required): Specifies the path to the input image.
- `--output <path>` or `-o <path>`: Defines the output image path (default: ./output.jpg).
- `--caps <path>` or `-c <path>`: Specifies the folder path containing cap images used for assembling the artwork.
- `--import <path>` or `-i <path>`: Provides the path to a .json file containing information about previously imported bottlecaps.
- `--mean` or `-m`: Picks colors for caps and image values by calculating the mean color value (slower but precise).
- `--gauss` or `-g`: Picks colors for caps and image values by calculating a Gaussian color value (be cautious of glare).
- `--point` or `-p`: Picks colors for caps and image values by using the color value at the center of the image (fast but potentially lower quality).
- `--normal` or `-n`: Maps points in the image to bottlecaps in order of occurrence, without considering the maximum percentage.
- `--best` or `-b`: Maps points in the image to bottlecaps by choosing the best-fitting caps first and taking maximum percentage into account.
- `--max-percent <int>`: Sets the maximum percentage of a single bottlecap used when using the best-mapping strategy.
- `--contrast <double>`: Adjusts the contrast of the input image by specifying a value.
- `--saturation <double>`: Modifies the saturation of the input image with a user-defined value.
- `--quantization <int>`: Applies color quantization to the image before assembling.

Use these command-line arguments to tailor Kronko's behavior to your specific requirements when creating bottlecap artwork.

### Importing your own Bottlecap images
1. Take Pictures of your desired bottlecaps (make sure its straight from the top, good lighting, minimal glare)
2. Crop the Images exactly to size so that the edges of the Bottlecap touch the edges of the image
3. (Optional) Erase everything from the image except the background
4. Save the imagea as a .png
5. Import the folder containing the .png images into Kronko (either `--caps` <path> or **i** in KronkoGUI)
6. Edit the resulting JSON file (either in ./ or specified by `--import` <path>) 

### Tweaking results
Play arround with the resolution, output width, different layout options, different color picking methods when importing/assembling, contrast, saturation or color quantization.

Additionally you could generate a lot of possibilities by iterating through different parameters like i do in [My batch script](conv_all_imgs.bat)

## Contributing
Feel free to contribute either code or suggestions. Standards are low B-).

## License

This project uses third-party libraries such as OpenCV and nlhomann/json, each of which has its own respective license. 

- [OpenCV License](https://opencv.org/license/): OpenCV is distributed under the 3-Clause BSD License, which allows you to use, modify, and distribute the library as long as you retain the original copyright notice.

- [nlhomann/json License](https://github.com/nlohmann/json#license): nlhomann/json is distributed under the MIT License, which permits you to use, modify, and distribute the library with minimal restrictions.

As for the code and assets specific to this project, you are free to use, modify, and distribute them in any way you see fit. We encourage open collaboration and innovation.

## Contact

E-mail: julius@velosoph.de
