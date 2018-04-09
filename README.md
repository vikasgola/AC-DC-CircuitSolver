# AC Circuit Solver

The application makes a circuit( provided input in given in a file named as in.txt in the SPICE netlist format) as svg file and  solves the circuit.

## Specifications

- The SVG file generates out as **in.txt.svg**.You can use the zoom feature of SVG using browsers only.
- The results (magnitude and initial phase of voltages and currents) are generated in a file namely **results.txt**.
- It is supposed that all sources have zero initial phase difference (at time=0s ) and DC offset is zero.
- The circuit is solved using Modified Nodal Analysis method.
- The value of the current and voltage of components may not be have the value as desired but very near to the desired value. It is so because the assumed value of pi is not very presice.

## System Requirements

AC circuit solver runs on Linux based platforms only. It requires the following packages :

- Eigen library. To install in ubuntu...

	sudo apt-get install libeigen3-dev

- A web browser supporting SVG Chrome or Firefox or anyother.

## Usage Instuctions

Compile the program with **make** command.

To run the main program, run: **make run**

This will create two files that are useful for the user namely in.out.svg that has the SVG code written in it and results.txt that has the value of magitude and initial phase of currents and voltages of respective components (Same frequency sources are grouped together).

## License

   Copyright [2018] [Vikas Gola]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
