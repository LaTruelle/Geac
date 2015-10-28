[![Build Status](https://travis-ci.org/LaTruelle/Geac.svg)](https://travis-ci.org/LaTruelle/Geac) [![DOI](https://zenodo.org/badge/18964/LaTruelle/Geac.svg)](https://zenodo.org/badge/latestdoi/18964/LaTruelle/Geac)
Geac
====

## Description

Geac (Gaussian ESI Automated Creator) is a simple software to extract useful data from gaussian log files. It allows the user to select one or several output files, according to different filters, and create an appropriate number of raw text files containing interesting data such as xyz coordinates, lowest frequencies, or thermodynamic data.

## Installation

Binaries for some platforms are provided. However, not all end users such as Linux flavors, or different Mac/Windows versions are covered. If the provided binaries do not match, compilation is always possible

## Compilation

Make sure you installed Qt5. Clone the repository, then in the src folder, perform a `qmake` `make` sequence. Usage of QtCreator, even if not necessary, is recommended for ease of use.
