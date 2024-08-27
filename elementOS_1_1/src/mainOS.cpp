#include "mainOS.h"

int prog_flag = 0;

void eos::ELEMENTOS(){
    eos::controller_button tournament(U , "联赛");
    eos::controller_button skill(R , "技能赛");
    eos::controller_button debug(D , "调试");
    eos::controller_button check(L , "自检");
    eos::controller_button port(X , "端口");
    eos::controller_button control(Y , "控制");

    eos::controller_button page_up(L1);
    eos::controller_button page_down(L2);

    while (true)
    {
        int page = 1;

        while (page != 0)//程序选择循环，两页
        {   
            if(page == 1){//第一页
                controller_window::ClearWindow();
                while (page == 1)
                {
                    tournament.Display(1 , 11);
                    skill.Display(2 , 2);
                    debug.Display(2 , 20);
                    check.Display(3 , 11);

                    if(page_down.IsClicked()){page ++; waitUntil(!page_down.IsClicked());}
                    
                    if(tournament.IsClicked()){prog_flag = 1; page = 0; waitUntil(!tournament.IsClicked());}
                    else if(skill.IsClicked()){prog_flag = 2; page = 0; waitUntil(!skill.IsClicked());}
                    else if(debug.IsClicked()){prog_flag = 3; page = 0; waitUntil(!debug.IsClicked());}
                    else if(check.IsClicked()){prog_flag = 4; page = 0; waitUntil(!check.IsClicked());}

                    wait(5,msec);
                }
            }else if(page == 2){//第二页
                controller_window::ClearWindow();
                while (page == 2)
                {
                    port.Display(1 , 11);
                    control.Display(3 , 11);

                    if(page_up.IsClicked()){page --; waitUntil(!page_up.IsClicked());}

                    if(port.IsClicked()){prog_flag = 5; page = 0; waitUntil(!port.IsClicked());}
                    else if(control.IsClicked()){prog_flag = 6; page = 0; waitUntil(!control.IsClicked());}

                    wait(5,msec);
                }
            }


            wait(5,msec);
        }

        controller_window::ClearWindow();

        wait(5,msec);
    }
    
}
    