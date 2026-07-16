# ElementOS

> A lightweight operating-system-style framework for VEX V5 robotics, built on top of the VEXcode SDK.

ElementOS 把一台 VEX V5 机器人需要面对的「初始化、调试、赛局选择、信息显示、菜单交互」等流程抽象成一个统一的系统层，让你把精力集中在底盘控制、机械臂逻辑和自动路线上，而不用反复重写界面与状态管理代码。

---

## ✨ Main Features

- **双模式切换**
  - **调试模式**（未接入场控）：可选择手动调试（Op Debug）或自动调试（Auto Debug），自动调试默认 1 号路线，无需连接场控即可完整调试。
  - **赛局模式**（接入场控）：直接在主控屏幕上点选 16 条自动路线，红/蓝联盟自动判定。
- **多级菜单系统**：主控屏幕上的多级菜单，支持查看机器人信息、系统设置、重新校准等，菜单导航通过虚拟按钮操作。
- **触屏虚拟按钮 (`brain_button`)**：在主控屏幕上绘制可点击的矩形按钮，支持按下检测、边沿触发（`JustPressed`）、单/双键控制布尔状态。
- **统一的信息显示 API**：一套 API 同时驱动主控屏幕（`BrainPrint`）、遥控器屏幕（`ControllerPrint`）与彩色终端输出（`TerminalPrint`），终端支持 ANSI 彩色高亮。
- **实时状态监测**：电池电量 / 电流 / 电压、联盟颜色、当前路线编号等关键信息在遥控器屏幕上增量刷新，避免频繁全屏重绘。
- **路线导演框架**：内置多个全局状态位，自动路线逻辑只需按路线编号编写即可被系统调度。

---

## 🚀 Installation Guide

ElementOS 基于 VEXcode 开发，集成方式非常轻量：

1. 在 VEXcode Pro V5 中打开或新建你的项目。
2. 将本仓库的 `src` 文件夹下的内容拖入你项目对应的 `src` 文件夹。
3. 将本仓库的 `include` 文件夹下的内容拖入你项目对应的 `include` 文件夹。
4. 在你的 `main.cpp` 中完成硬件配置后，调用：

   ```cpp
   #include "elementOS.h"

   void autonomous(void) {
    waitUntil(eos::READY);
    eos::AutoRoute();
   }
    
    void usercontrol(void) {
      waitUntil(eos::READY);
      if(eos::AUTODEBUG){
        eos::AutoRoute();
      }else{
        while(true){
          eos::SystemWait();
        }
      }
    }
    
    int main() {
  
      Competition.autonomous(autonomous);
      Competition.drivercontrol(usercontrol);
    
      eos::SystemInitialize(&Brain , &Controller , &Competition);
      thread eos_main(eos::EosMain);
      waitUntil(eos::READY);
    
      while (true) {
        wait(100, msec);
      }
    }
   ```

   ElementOS 会接管启动校准、模式选择、路线选择与菜单交互的完整流程。

> 仅需拖放 `src` 与 `include` 即可，无需改动 VEXcode 工程结构与构建配置。

---

## 📜 Version History

### ElementOS 1.1 (2024.6.4)
支持在未连接场控的情况下进行调试。

### ElementOS 1.2 (2024.8.29)
增强 PC 端信息显示功能（类似上位机）；修复了上一版本中遥控器与主控频繁通信导致连接中断的问题。

### ElementOS 2.0 (2025.12.8)
重新设计系统界面与交互逻辑，引入多级菜单以查看与编辑更多信息。

### ElementOS 2.1 (2026.7.16)
优化了多级菜单代码；添加了16条自动路线可供调试和选择。

---

## 👤 Author

**Dove-ctrl** — 2941178026@qq.com
