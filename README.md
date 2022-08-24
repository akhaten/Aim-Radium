# Aim-Radium
Aim trainer (Like AimLab)

Dependencies:

Install Radium-Engine (https://github.com/STORM-IRIT/Radium-Engine/tree/release-candidate)

To compile my application :
```bash
mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH=../Radium-Engine/Bundle-GNU/lib/cmake/Radium
make
./StaticTrainer  or ./AnimationTrainer
```