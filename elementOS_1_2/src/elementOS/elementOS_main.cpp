#include "elementOS.h"

bool INITIALIZE_DONE = false;

int PROGRAMFLAG = 0;

void COMPETITIONINFO(){
    int i; i = 1;
    eos::ClearControllerScreen();
    while (true)
    {
        eos::ControllerPrint("电池:" , 1 , 2);eos::ControllerPrint("%%", 1 , 13);
        eos::ControllerPrint( 
            (int(eos::BRAIN->Battery.capacity()) >= 100 ? 99 : int(eos::BRAIN->Battery.capacity())), 
            1 , 10
        );

        eos::ControllerPrint("Beyond the Best" , 2 , 1);
        
        eos::ControllerPrint(">" , 3 , i);
        i = (i >= 18 ? 1 : i + 1);
        if(i == 1){eos::ClearControllerLine(3);}

        eos::SystemWait(1000);
    }
}

int SYSTEMINFO(const controller::button btn){
    if(btn.pressing()){
        waitUntil(!btn.pressing());
        eos::ClearControllerScreen();
        while (true)
        {
            eos::ControllerPrint("电池:" , 1 , 2);eos::ControllerPrint("%%", 1 , 13);
            eos::ControllerPrint( 
                (int(eos::BRAIN->Battery.capacity()) >= 100 ? 99 : int(eos::BRAIN->Battery.capacity())), 
                1 , 10
            );
            
            eos::ControllerPrint("SD卡状态:" , 2 , 2);
            eos::ControllerPrint(
                ( eos::BRAIN->SDcard.isInserted() ? "是" : "否" ),
                2 , 15
            );

            eos::ControllerPrint("&由elementOS驱动&" , 3 , 2);

            if(btn.pressing()){
                waitUntil(!btn.pressing());
                eos::ClearControllerScreen();
                return 1;
            }

            eos::SystemWait();
        }
        
    }else{return 0;}
}

void elementOS(void* cpt){
    competition* p = (competition*)cpt;

    eos::controller_button tournament(eos::U , "-联赛-");
    eos::controller_button skill(eos::L , "-技能赛-");
    eos::controller_button driver_debug(eos::R , "-手动调试-");
    eos::controller_button auto_debug(eos::D , "-自动调试-");

    eos::controller_button port(eos::U , "-端口-");
    eos::controller_button control(eos::L , "-控制-");
    eos::controller_button setting(eos::R , "-设置-");
    eos::controller_button check(eos::D , "-自检-");

    eos::controller_button page_up(eos::R1);
    eos::controller_button page_down(eos::R2);

    while (true)//程序选择循环，两页
    {
        int page = 1;

        while (page != 0)
        {   
            eos::ClearControllerScreen();
            if(page == 1){//第一页

                while (page == 1)
                {
                    tournament.Display(1 , 11);
                    skill.Display(2 , 2);
                    driver_debug.Display(2 , 16);
                    auto_debug.Display(3 , 9);

                    SYSTEMINFO(eos::CONTROLLER->ButtonX);

                    if(page_down.IsClicked()){page ++;}
                    
                    if(tournament.IsClicked()){
                        if(eos::MessageBox("确认进入：" , 9 , "联赛" , 12)){PROGRAMFLAG = 1; page = 0;}
                        else{page = 1;}
                    }
                    else if(skill.IsClicked()){
                        if(eos::MessageBox("确认进入：" , 9 , "技能赛" , 11)){PROGRAMFLAG = 2; page = 0;}
                        else{page = 1;}
                    }
                    else if(driver_debug.IsClicked()){
                        if(eos::MessageBox("确认进入：" , 9 , "手动调试" , 10)){PROGRAMFLAG = 3; page = 0;}
                        else{page = 1;}
                    }
                    else if(auto_debug.IsClicked()){
                        if(eos::MessageBox("确认进入：" , 9 , "自动调试" , 10)){PROGRAMFLAG = 4; page = 0;}
                        else{page = 1;}
                    }

                    eos::SystemWait();
                }

            }else if(page == 2){//第二页
                
                while (page == 2)
                {
                    port.Display(1 , 11);
                    control.Display(2 , 4);
                    setting.Display(2 , 18);
                    check.Display(3 , 11);

                    SYSTEMINFO(eos::CONTROLLER->ButtonX);

                    if(page_up.IsClicked()){page --;}

                    if(port.IsClicked()){
                        if(eos::MessageBox("确认进入：" , 9 , "端口" , 12)){PROGRAMFLAG = 5; page = 0;}
                        else{page = 2;}
                    }
                    else if(control.IsClicked()){
                        if(eos::MessageBox("确认进入：" , 9 , "控制" , 12)){PROGRAMFLAG = 6; page = 0;}
                        else{page = 2;}
                    }
                    else if(setting.IsClicked()){
                        if(eos::MessageBox("确认进入：" , 9 , "设置" , 12)){PROGRAMFLAG = 7; page = 0;}
                        else{page = 2;}
                    }
                    else if(check.IsClicked()){
                        if(eos::MessageBox("确认进入：" , 9 , "自检" , 12)){PROGRAMFLAG = 8; page = 0;}
                        else{page = 2;}
                    }

                    eos::SystemWait();
                }

            }
            eos::SystemWait();
        }//程序选择结束

        //初始化
        if (PROGRAMFLAG >= 1 && PROGRAMFLAG <= 2) {//tournament,skill
            eos::ControllerPrint("校准中" , 2 , 10);
            initialize_robot();
            eos::ClearControllerScreen();
            if(!(p->isCompetitionSwitch() || p->isFieldControl())){
                eos::ControllerPrint("等待场控连接" , 2 , 6);
                waitUntil(p->isCompetitionSwitch() || p->isFieldControl());
                eos::ClearControllerScreen();
                INITIALIZE_DONE = true; break;
            }
            else{INITIALIZE_DONE = true; break;}
        }
        else if(PROGRAMFLAG >= 3 && PROGRAMFLAG <= 4){//user/auto debug
            eos::ControllerPrint("校准中" , 2 , 10);
            initialize_robot();
            eos::ClearControllerScreen();
            break;
        }
        else if(PROGRAMFLAG >= 5 && PROGRAMFLAG <= 7){//port,control,setting
            if(!eos::BRAIN->SDcard.isInserted()){
                eos::MessageBox("警告!" , 11 , "未插入SD卡" , 8);
                INITIALIZE_DONE = false;
                /* INITIALIZE_DONE = true; break; */
            }else{INITIALIZE_DONE = true; break;}
        }else{break;}
        //初始化结束
        eos::SystemWait();
    }

    //程序信息显示
    switch (PROGRAMFLAG)
    {
    case 1://tournament
        COMPETITIONINFO();
        break;
    
    case 2://skill
        COMPETITIONINFO();
        break;

    case 3://driver_debug
        INITIALIZE_DONE = true; 
        eos::ClearControllerScreen();
        while (true)
        {
            eos::ControllerPrint("yaw: " , 1 , 1);
            eos::ControllerPrint(chassis::GetInstance().get_yaw_limit() , 1 , 6);
            eos::ControllerPrint("pos:" , 2 , 1);
            eos::ControllerPrint("电机温度:" , 3 , 1);
            eos::ControllerPrint(chassis::GetInstance().get_temperature() , 3 , 15);
            eos::SystemWait();
        }
        break;

    case 4://auto_debug
    {
        eos::ClearControllerScreen();
        while (true)
        {
            eos::ControllerPrint("选择程序" , 1 , 9);
            eos::ControllerPrint("X: 技能赛 Y: 联赛" , 2 , 4);
            eos::ControllerPrint("==================" , 3 , 1);

            if(eos::CONTROLLER->ButtonX.pressing()){
                waitUntil(!eos::CONTROLLER->ButtonX.pressing());
                PROGRAMFLAG = 4;break;
            }else if(eos::CONTROLLER->ButtonY.pressing()){
                waitUntil(!eos::CONTROLLER->ButtonY.pressing());
                PROGRAMFLAG = 9;break;
            }
            eos::SystemWait();
        }

        INITIALIZE_DONE = true; 
        timer auto_debug_timer;
        eos::ClearControllerScreen();
        auto_debug_timer.clear();
        while (true)
        {
            eos::ControllerPrint("yaw:" , 1 , 1);
            eos::ControllerPrint(chassis::GetInstance().get_yaw_limit() , 1 , 7);
            eos::ControllerPrint("pos:" , 2 , 1);
            eos::ControllerPrint("当前时间:" , 3 , 14);
            eos::ControllerPrint(int(auto_debug_timer.time(sec)) , 3 , 28);
            eos::ControllerPrint("按B终止" , 3 , 1);

            cout << "\033c";
            cout <<"---------------------Terminal Output----------------------" << endl;
            cout <<"\033[32mAutonomous Debug is running......\033[0m" << endl;
            cout <<"\033[33myaw\033[0m: " << chassis::GetInstance().get_yaw_limit()
            <<"   \033[34mtemperature\033[0m: " << chassis::GetInstance().get_temperature()
            <<"   \033[31mmax temperature\033[0m: " << chassis::GetInstance().get_max_temperature()
            <<"   time: " << int(auto_debug_timer.time(sec)) << endl;

            if(int(auto_debug_timer.time(sec)) >= TIMEOUT_WRRNING){
                cout << "\033[33mWarning(elementOS): The program timed out !\033[0m" << endl;
            }
            if(chassis::GetInstance().get_temperature() >= TEMPERATURE_WRRNING){
                cout << "\033[31mError(elementOS): The motor temperature is too high !\033[0m" << endl;
            }
            if(!chassis::GetInstance().get_connection_state()){
                cout<< "\033[31mError(elementOS): The sensor or motor is disconnected !\033[0m" << endl;
            }
            if(eos::CONTROLLER->ButtonB.pressing()){
                eos::CONTROLLER->rumble("-");
                cout << "\033[33mWarning(elementOS): The program has been terminated !\033[0m" << endl;
                thread::interruptAll();
            }

            eos::SystemWait(500);
        }
        break;
    }
    case 5://port
        eos::ClearControllerScreen();

        break;
    case 6://control
        eos::ClearControllerScreen();

        break;
    case 7://setting
        eos::ClearControllerScreen();

        break;
    case 8://check
        eos::ClearControllerScreen();

        break;

    default:
        break;
    }

}