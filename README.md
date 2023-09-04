## Kronko - Turning Pictures into Bottlecap Art

## Table of Contents

- [Introduction](#Introduction)
- [Features](#Features)
- [Getting Started](#Getting-started)
- [Usage](#Usage)
- [Installation](#Installation)
- [Contributing](#Contributing)
- [License](#License)
- [Contact](#Contact)

# Introduction

Kronko is a C++ application I created as a fun side project to refresh my C++ and OpenCV skills. Its main purpose is to turn images into bottlecap artwork, aiming to generate templates for actual bottlecap art. However, achieving easily reproducible and recognizable results can be a bit tricky, often requiring large output images or carefully chosen input images. Kronko offers different approaches for arranging bottlecaps and selecting matching colors. In the following sections, we'll explore some examples of what Kronko can do.

# Features

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

# Getting-started

# Usage

# Installation

# Contributing

# License

# Contact

E-mail: julius@velosoph.de
