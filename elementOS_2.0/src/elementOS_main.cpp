#include "elementOS_2.0.h"

void AutoRoute(){
    
}

void Initialize(){
  wait(1000,msec);
  
}

eos::brain_button select = eos::brain_button(50 , 200 , 30 , 100 , "Select" , HEX_GREEN , HEX_WHITE);
eos::brain_button confirm = eos::brain_button(200 , 200 , 30 , 100 , "Confirm" , HEX_GREEN , HEX_WHITE);
eos::brain_button back = eos::brain_button(350 , 200 , 30 , 100 , "Back" , HEX_GREEN , HEX_WHITE);

void BrainInfoDisplay(){
    eos::DrawLine(0 , 190 , 480 , 190 , HEX_WHITE);
    select.DisplayButton();
    confirm.DisplayButton();
    back.DisplayButton();

    // 多级菜单状态
    static int menu_level = 0; 
    static int menu_index = 0; 
    static bool prev_select = false, prev_confirm = false, prev_back = false;

    // 菜单项
    const char* main_menu[] = {"Robot", "System", "Settings", "About"};
    const int main_count = 4;
    const char* settings_menu[] = {"Alliance", "Websocket Test"};
    const int settings_count = 2;

    // 当前按键状态
    bool cur_select = select.IsPressed();
    bool cur_confirm = confirm.IsPressed();
    bool cur_back = back.IsPressed();

    // 边沿检测
    bool press_select = cur_select && !prev_select;
    bool press_confirm = cur_confirm && !prev_confirm;
    bool press_back = cur_back && !prev_back;

    int count = (menu_level == 0) ? main_count : settings_count;

    // select 切换选项
    if(press_select){
        menu_index = (menu_index + 1) % count;
    }

    // confirm 确认所选项
    if(press_confirm){
        eos::ClearBrainScreen();
        if(menu_level == 0){
            // 在主菜单中
            if(menu_index == 0){
                // 进入 Robot 子菜单
                menu_level = 1;
                menu_index = 0;
            }else if(menu_index == 1){
                // 进入 System 子菜单
                menu_level = 2;
                menu_index = 0;
            }else if(menu_index == 2){
                // 进入 Settings 子菜单
                menu_level = 3;
                menu_index = 0;
            }else if(menu_index == 3){
                // 进入 About 子菜单
                menu_level = 4;
                menu_index = 0;
            }
        }else if(menu_level == 3){
            // 在 Settings 子菜单中
            if(menu_index == 0){
                // 切换联队
                menu_level = 5;
                menu_index = 0;
            }else if(menu_index == 1){
                // WebSocket 测试
                menu_level = 6;
                menu_index = 0;
            }
        }
    }

    // back 返回上一级
    if(press_back){
        eos::ClearBrainScreen();
        if(menu_level > 0 && menu_level <= 4){
            menu_level = 0;
            menu_index = 0;
        }else if(menu_level >= 5){
            menu_level = 3;
            menu_index = 0;
        }
    }

    // 绘制菜单项到 LCD
    if(menu_level == 0){
        // 主菜单
        eos::LCD->printAt(1 , 1*SINGLE_LINE_HIGHT , "ElemnetOS Menu               ");
        for(int i=0;i<main_count;i++){
            char buf[32];
            if(i == menu_index) snprintf(buf, sizeof(buf), "> %s", main_menu[i]);
            else snprintf(buf, sizeof(buf), "  %s", main_menu[i]);
            eos::LCD->printAt(1 , (3+i)*SINGLE_LINE_HIGHT , buf);
        }
    }else if(menu_level == 1){
        // Robot 子菜单
        eos::LCD->printAt(1 , 1*SINGLE_LINE_HIGHT , "Robot information                 ");
        eos::LCD->printAt(1 , 3*SINGLE_LINE_HIGHT , "> Pose");
        eos::LCD->printAt(1 , 4*SINGLE_LINE_HIGHT , "  x:");
        eos::LCD->printAt(1 , 5*SINGLE_LINE_HIGHT , "  y:");
        eos::LCD->printAt(1 , 6*SINGLE_LINE_HIGHT , "  yaw:");
        eos::LCD->printAt(1 , 7*SINGLE_LINE_HIGHT , "> Chassis Temperature");
        eos::LCD->printAt(1 , 8*SINGLE_LINE_HIGHT , "  max:");
        eos::LCD->printAt(1 , 9*SINGLE_LINE_HIGHT , "  avg:");

        eos::LCD->printAt(250 , 3*SINGLE_LINE_HIGHT , "> Alliance:"); eos::LCD->printAt(250 + 12*SINGLE_LETTER_WIDTH , 3*SINGLE_LINE_HIGHT , eos::ALLIANCE == 0 ? "Red" : "Blue");

    }else if(menu_level == 2){
        // System 子菜单
        eos::LCD->printAt(1 , 1*SINGLE_LINE_HIGHT , "System information                ");
        eos::LCD->printAt(1 , 3*SINGLE_LINE_HIGHT , "> Battery Status");
        eos::LCD->printAt(1 , 4*SINGLE_LINE_HIGHT , "  capacity:"); eos::LCD->printAt(12*SINGLE_LETTER_WIDTH , 4*SINGLE_LINE_HIGHT , "%d%%" , eos::SystemBatteryCapacity());
        eos::LCD->printAt(1 , 5*SINGLE_LINE_HIGHT , "  volt:"); eos::LCD->printAt(8*SINGLE_LETTER_WIDTH , 5*SINGLE_LINE_HIGHT , " %.2fV" , eos::SystemBatteryVoltage());
        eos::LCD->printAt(1 , 6*SINGLE_LINE_HIGHT , "  amp:"); eos::LCD->printAt(7*SINGLE_LETTER_WIDTH , 6*SINGLE_LINE_HIGHT , " %.2fA" , eos::SystemBatteryCurrent());
        
    }else if(menu_level == 3){
        // Settings 子菜单
        eos::LCD->printAt(1 , 1*SINGLE_LINE_HIGHT , "Settings                          ");
        for(int i=0;i<settings_count;i++){
            char buf[32];
            if(i == menu_index) snprintf(buf, sizeof(buf), "> %s", settings_menu[i]);
            else snprintf(buf, sizeof(buf), "  %s", settings_menu[i]);
            eos::LCD->printAt(1 , (3+i)*SINGLE_LINE_HIGHT , buf);
        }
    }else if(menu_level == 4){
        // About 子菜单
        eos::LCD->printAt(1 , 1*SINGLE_LINE_HIGHT , "About ElementOS                   ");
        eos::LCD->printAt(1 , 3*SINGLE_LINE_HIGHT , "> Version: 2.0.0");
        eos::LCD->printAt(1 , 4*SINGLE_LINE_HIGHT , "> Developed by Dove-ctrl");
        eos::LCD->printAt(1 , 6*SINGLE_LINE_HIGHT , "> Enable WebSocket on VEX extension");
        eos::LCD->printAt(1 , 7*SINGLE_LINE_HIGHT , "  to experience full functionality.");
    }else if(menu_level == 5){
        // Alliance 设置
        eos::LCD->printAt(1 , 1*SINGLE_LINE_HIGHT , "Set Alliance                      ");
        eos::LCD->printAt(1 , 3*SINGLE_LINE_HIGHT , "> Current Alliance:"); eos::LCD->printAt(20*SINGLE_LETTER_WIDTH , 3*SINGLE_LINE_HIGHT , eos::ALLIANCE == 0 ? "Red  " : "Blue  ");
        eos::LCD->printAt(1 , 4*SINGLE_LINE_HIGHT , "> Press Confirm to toggle alliance.");
        if(press_confirm){
            eos::ALLIANCE = 1 - eos::ALLIANCE;
        }
    }else if(menu_level == 6){
        // WebSocket 测试
        eos::LCD->printAt(1 , 1*SINGLE_LINE_HIGHT , "WebSocket Test                    ");
        eos::LCD->printAt(1 , 3*SINGLE_LINE_HIGHT , "> A test message will be sent to test connection.");
        eos::LCD->printAt(1 , 4*SINGLE_LINE_HIGHT , "> Press Confirm to send message.");
        if(press_confirm){
            printf("ElementOS WebSocket Test Message\n");
        }
    }

    // 保存按键状态
    prev_select = cur_select;
    prev_confirm = cur_confirm;
    prev_back = cur_back;
}

void ControllerInfoDisplay(){
    eos::ControllerPrint("联队:" , 1 , 1);
    if(eos::ALLIANCE == 0){
        eos::ControllerPrint("Red" , 1 , 9);
    }else{
        eos::ControllerPrint("Blue" , 1 , 9);
    }

    eos::ControllerPrint("Powered by ElemntOS" , 2 , 1);
}

void EosMain(){
    eos::ClearControllerScreen();
    eos::ClearBrainScreen();
    eos::TerminalClear();
    
    //遥控器显示
    eos::ControllerPrint("==================" , 1 , 1);
    eos::ControllerPrint("校准中" , 2 , 10);
    eos::ControllerPrint("==================" , 3 , 1);
    //主控显示
    eos::LCD->printAt(1 , 1*SINGLE_LINE_HIGHT , "> The System has started.");
    eos::LCD->printAt(1 , 2*SINGLE_LINE_HIGHT , "> System is Initializing. Do not move robot!");

    //开始初始化
    Initialize();
    eos::ClearControllerScreen();

    if(!(eos::COMPETITION->isFieldControl() || eos::COMPETITION->isCompetitionSwitch())){
        //未接入场控

        eos::brain_button op_debug = eos::brain_button(50 , 100 , 100 , 160 , "Op Debug" , HEX_GREEN , HEX_WHITE);
        eos::brain_button auto_debug = eos::brain_button(280 , 100 , 100 , 160 , "Auto Debug" , HEX_YELLOW , HEX_BLACK);

        //选择调试模式
        while(true){
            //遥控器显示
            eos::ControllerPrint("手动调试: B" , 1 , 7);
            eos::ControllerPrint("自动调试: A" , 2 , 7);
            eos::ControllerPrint("==================" , 3 , 1);
            //主控显示
            eos::LCD->printAt(1 , 3*SINGLE_LINE_HIGHT , "> Initialization complete!");
            eos::LCD->printAt(1 , 4*SINGLE_LINE_HIGHT , "> Selecting your debugging type ");
            eos::LCD->printAt(1 , 5*SINGLE_LINE_HIGHT , "  to enter the system.");
            op_debug.DisplayButton();
            auto_debug.DisplayButton();

            if(eos::A() || auto_debug.IsPressed()){
                eos::AUTODEBUG = true; eos::OPDEBUG = false;
                break;
            }else if(eos::B() || op_debug.IsPressed()){
                eos::AUTODEBUG = false; eos::OPDEBUG = true;
                break;
            }
            
            eos::SystemWait(); 
        }
        eos::ClearControllerScreen();
        eos::ClearBrainScreen();
        eos::READY = true;

        //遥控器显示
        ControllerInfoDisplay();

        while(true){
            if(!eos::AUTODEBUG && !eos::OPDEBUG){
                break;
            }

            BrainInfoDisplay();
            eos::SystemWait();
        }
    }else{
        //接入场控
        eos::READY = true;

        //遥控器显示
        ControllerInfoDisplay();

        while(true){
            BrainInfoDisplay();
            eos::SystemWait();
        }
    }

    eos::SystemWait(1000);
    eos::SystemExit();
}