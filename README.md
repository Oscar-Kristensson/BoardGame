# WorldGame

is a tool for automating stoichiometric calculations by automatically calculating the mass, molarmass, amount of substance, concentration, volume and more.

## Usage and installation
### VS 2022
Run the following script:

``` bash
scripts/vs
```

Then open the generated solution file in VS and compile as normal.

### Cmake
Run cmake :)


## Usage
1. It is recommended to enter the molecules in the reaction. This step is not necessary unless you want to fill the molarmass, but is recommended inorder to allow for balansing checks. To add more molecules, press the "add column button" (CTRL + SHIFT + K). When adding molecules, all subscript numbers should be prefixed with a underscore. For example: CO_2. Superscript characters should be prefixed with either ' or ^, for example: H_3O'+.

2. Balance you reaction by using the ratio inputs. 

3. Add the correct operators by clicking the operator to open the dropdown menu. To see options for equilibrium calculations, you have to use the double arrow operator.

3. When all the required information for the calculation is enterd, click the Calculate button. Please note that some inputs are going to be locked to protect from unexpected erros. The inputs can be unlocked by pressing the unlock icon.


## Licenses
ChemistryCalculator uses fonts and icons from Google Fonts. The licenses can be found in the licenses folder. The license for the icons can be found through this (external)
[link](https://www.apache.org/licenses/LICENSE-2.0.html).

## Contributing
Currently, there is no plan or system for contributing. The code quality is not on top, because it is my first HTML and JS project. If you want to contribute, feel free to reach out.

## Authors
- [@Oscar-Kristensson](https://github.com/Oscar-Kristensson)
