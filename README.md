# DBSA Project - Chess Database
<div align="center">
<a href="https://www.bruface.eu/">
<img src="https://www.bruface.eu/sites/default/files/BUA-BRUFACE_RGB_Update_DEF_1_0_0.jpg" height=100"/>
</a>
</div>

## Overview
This repo is our project "Chess Database" in the course "Database System Architecture" at Université Libre de Bruxelles (ULB). We are required to build a PostgreSQL extension that provides functionalities for storing and retrieving chess games in a PostgreSQL database. It uses Portable Game Notation (PGN) for recording full games, Standard Algebraic Notation (SAN) for moves, and Forsyth–Edwards Notation (FEN) for board states.

## Built With
<div align="center">
<a href="https://www.postgresql.org/">
  <img src="https://www.postgresql.org/media/img/about/press/elephant.png" height=40 hspace=10/>
</a>
<a href="https://python-chess.readthedocs.io/en/latest/">
  <img src="https://backscattering.de/web-boardimage/board.png?fen=r1bqkb1r/pppp1Qpp/2n2n2/4p3/2B1P3/8/PPPP1PPP/RNB1K1NR&lastmove=h5f7&check=e8" height=40 hspace=10/>
</a>
</div>

## Usage
### Method 1: Using the Installation Shell Script
A shell script is provided to automate the installation of the necessary dependencies and the extension itself. Follow these steps to use the script:
1. Make the Script executable
   ```sh
   chmod +x runall.sh
   ```
2. Install the Python chess library, build and install the extension.
   ```bash
   ./runall.sh
   ```

### Method 2: Manually Installing (Alternative Method)
If you prefer to install the dependencies and the extension manually, follow these steps:
1. Install the chess package for Python
   ```sh
   pip install chess
   ```
2. Build and install the Extension
   ```sh
   cd path/to/your/extension
   make
   sudo make install
   ```

### Test
Once the extension is installed (either via the script or manually), you can start storing and querying chess games in your PostgreSQL database using the provided functionalities. You can open the file located at /Testing/Sql with all the queries to test the extension.