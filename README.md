## 基于AT89C52单片机的PID直流电机控制系统仿真
本文所介绍的基于AT89C52单片机的PID直流电机控制系统设计过程主要分为MATLAB建模、Proteus硬件电路的设计以及基于C51语法的单片机程序开发编写。本系统性质为单闭环控制，即通过转速对电机进行调速；将采用增量式编码器进行电机转速的测量，并设定PWM波形生成的开关频率为7KHz，速度回路的采样周期为14ms。

### 1. 所需仿真平台
单片机部分代码主要利用`Keil uVision5`平台进行编译，工具链采用**C51**。仿真电路搭建平台为`Proteus 8 Professional`。

### 2. Release版本
编译后的运行环境为`Atmel AT89C52`单片机平台。

### 3. 运行
1. 将已发布的**HEX**文件放入Proteus 8 Professional仿真平台或以上版本内运行即可；
2. 可通过修改Proteus仿真文件方波的频率（开关频率）来改变PWM相应的频率；
3. 若需要修改源代码可**Clone**软件代码进行修改，注释已在代码中标出。

### 4. 更多
可以进入我的个人博客[Jimmy's TechBlog](https://zmtblog.site)进行查看。


## PID DC motor control system simulation based on AT89C52 single chip microcomputer
The design process of PID DC motor control system based on AT89C52 single-chip microcomputer introduced in this paper is mainly divided into MATLAB modeling, Proteus hardware circuit design, and single-chip program development and writing based on C51 syntax. The nature of this system is single closed-loop control, that is, the motor speed is adjusted by the speed; an incremental encoder will be used to measure the motor speed, and the switching frequency generated by the PWM waveform is set to 7KHz, and the sampling period of the speed loop is 14ms.

### 1. Required simulation platform
Part of the code of the single-chip microcomputer is mainly compiled using the `Keil uVision5` platform, and the tool chain uses **C51**. The simulation circuit building platform is `Proteus 8 Professional`.

### 2. Release version
The compiled operating environment is the `Atmel AT89C52` microcontroller platform.

### 3. Run
1. Put the released **HEX** file into the Proteus 8 Professional simulation platform or above to run;
2. The corresponding frequency of PWM can be changed by modifying the frequency (switching frequency) of the square wave of the Proteus simulation file;
3. If you need to modify the source code, you can modify the **Clone** software code, and the comments have been marked in the code.

### 4. More
You can enter my personal blog [Jimmy's TechBlog](https://zmtblog.site) to view it.

